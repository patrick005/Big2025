# process_server.py
import zmq
import cv2
import numpy as np
from bust import detect_upper_body  # 상반신 crop 로직
from frontal import is_facing_forward  # 정면 판단
import mediapipe as mp
from PIL import Image
import io

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5588")

mp_pose = mp.solutions.pose

while True:
    img_bytes = socket.recv()
    
    # 기본 OpenCV 디코딩 시도
    npimg = np.frombuffer(img_bytes, dtype=np.uint8)
    image = cv2.imdecode(npimg, cv2.IMREAD_COLOR)

    # 디코딩 실패 시 Pillow 보완 디코딩 시도 (.webp 대응)
    if image is None:
        try:
            pil_image = Image.open(io.BytesIO(img_bytes)).convert("RGB")
            image = cv2.cvtColor(np.array(pil_image), cv2.COLOR_RGB2BGR)
            print("[Info] Pillow로 이미지 디코딩 성공")
        except Exception as e:
            print(f"[Error] 이미지 디코딩 실패: {e}")
            socket.send_string("FAIL: Image decode error")
            continue
    
    cv2.imshow("Input", image)

    # 상반신 검출
    status, result = detect_upper_body(image, visualize_crop=False)
    if status != "UPPER_BODY":
        socket.send_string("FAIL: Chest Not Detected")
        continue

    debug_img = result.copy()  # 시각화용 복사 이미지

    # Mediapipe로 정면 판단
    with mp_pose.Pose(static_image_mode=True) as pose:
        res = pose.process(cv2.cvtColor(result, cv2.COLOR_BGR2RGB))
        if not res.pose_landmarks:
            socket.send_string("FAIL: Pose landmarks not found")
            continue

        # 정면 검출용 시각화 추가
        try:
            lmk = res.pose_landmarks.landmark
            image_shape = result.shape

            def to_pt(idx):
                return int(lmk[idx].x * image_shape[1]), int(lmk[idx].y * image_shape[0])

            # 선 그리기: 눈 (초록), 귀 (파랑), 어깨 (빨강)
            cv2.line(debug_img, to_pt(mp_pose.PoseLandmark.LEFT_EYE), to_pt(mp_pose.PoseLandmark.RIGHT_EYE), (0,255,0), 2)
            cv2.line(debug_img, to_pt(mp_pose.PoseLandmark.LEFT_EAR), to_pt(mp_pose.PoseLandmark.RIGHT_EAR), (255,0,0), 2)
            cv2.line(debug_img, to_pt(mp_pose.PoseLandmark.LEFT_SHOULDER), to_pt(mp_pose.PoseLandmark.RIGHT_SHOULDER), (0,0,255), 2)

            # 디버깅 이미지 시각화
            cv2.imshow("Debug - Key Lines", debug_img)
            print("[Debug] ESC 키 입력 시 다음 이미지로 진행")
            if cv2.waitKey(0) == 27:  # ESC key
                cv2.destroyAllWindows()

        except Exception as e:
            print(f"[Warning] 디버깅 선 그리기 실패: {e}")

        if not is_facing_forward(lmk, result.shape):
            socket.send_string("FAIL: Not frontal image")
            continue

    # 성공 시 이미지 응답
    _, buffer = cv2.imencode(".jpg", result)
    socket.send(buffer.tobytes())
