# import cv2
# import mediapipe as mp
# import numpy as np
# import os

# # 1. 상반신 검출
# def detect_upper_body(image):
#     mp_pose = mp.solutions.pose
#     with mp_pose.Pose(static_image_mode=True) as pose:
#         results = pose.process(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
#         if not results.pose_landmarks:
#             return "다시 상반신 이미지를 업로드하세요", None

#         landmarks = results.pose_landmarks.landmark
#         left_shoulder = landmarks[mp_pose.PoseLandmark.LEFT_SHOULDER]
#         right_shoulder = landmarks[mp_pose.PoseLandmark.RIGHT_SHOULDER]
#         left_hip = landmarks[mp_pose.PoseLandmark.LEFT_HIP]
#         right_hip = landmarks[mp_pose.PoseLandmark.RIGHT_HIP]

#         # 비율 계산
#         shoulder_y = (left_shoulder.y + right_shoulder.y) / 2
#         hip_y = (left_hip.y + right_hip.y) / 2

#         if hip_y - shoulder_y > 0.4:
#             return "상반신", image
#         else:
#             return "다시 상반신 이미지를 업로드하세요", None

# # 2. 정면 검출
# def is_facing_forward(landmarks, image_shape):
#     def get_point(p):
#         return np.array([int(p.x * image_shape[1]), int(p.y * image_shape[0])])

#     left_eye = get_point(landmarks[mp.solutions.pose.PoseLandmark.LEFT_EYE])
#     right_eye = get_point(landmarks[mp.solutions.pose.PoseLandmark.RIGHT_EYE])
#     left_shoulder = get_point(landmarks[mp.solutions.pose.PoseLandmark.LEFT_SHOULDER])
#     right_shoulder = get_point(landmarks[mp.solutions.pose.PoseLandmark.RIGHT_SHOULDER])
#     left_ear = get_point(landmarks[mp.solutions.pose.PoseLandmark.LEFT_EAR])
#     right_ear = get_point(landmarks[mp.solutions.pose.PoseLandmark.RIGHT_EAR])

#     def angle(p1, p2):
#         return np.degrees(np.arctan2(p2[1] - p1[1], p2[0] - p1[0]))

#     angles = {
#         "eye": angle(left_eye, right_eye),
#         "shoulder": angle(left_shoulder, right_shoulder),
#         "ear": angle(left_ear, right_ear),
#     }

#     values = list(angles.values())
#     if max(values) - min(values) < 10:
#         return True
#     else:
#         return False

# # 3. 분석 함수
# def analyze_image_from_path(image_path):
#     if not os.path.exists(image_path):
#         print("이미지 경로가 잘못되었습니다.")
#         return

#     image = cv2.imread(image_path)
#     status, upper_img = detect_upper_body(image)
#     print("상반신 판단 결과:", status)

#     if status != "상반신":
#         return

#     mp_pose = mp.solutions.pose
#     with mp_pose.Pose(static_image_mode=True) as pose:
#         results = pose.process(cv2.cvtColor(upper_img, cv2.COLOR_BGR2RGB))
#         if not results.pose_landmarks:
#             print("다시 상반신 이미지를 업로드하세요")
#             return

#         # 시각화
#         annotated_image = upper_img.copy()
#         mp_drawing = mp.solutions.drawing_utils
#         mp_drawing.draw_landmarks(
#             annotated_image, results.pose_landmarks, mp_pose.POSE_CONNECTIONS
#         )

#         if is_facing_forward(results.pose_landmarks.landmark, upper_img.shape):
#             print("정면 상반신 이미지입니다.")
#         else:
#             print("상반신은 맞지만, 정면이 아닙니다.")

#         cv2.imshow("분석 결과", annotated_image)
#         cv2.waitKey(0)
#         cv2.destroyAllWindows()

# if __name__ == "__main__":
#     image_absolute_path = "/home/aa/Big2025/aaatest/instance/testsample/kids.png"  # 테스트 이미지 경로
#     analyze_image_from_path(image_absolute_path)

import cv2
import mediapipe as mp
import numpy as np
import matplotlib.pyplot as plt
import os


# 1. 상반신 검출
def detect_upper_body(image):
    mp_pose = mp.solutions.pose
    with mp_pose.Pose(static_image_mode=True) as pose:
        results = pose.process(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
        if not results.pose_landmarks:
            return "다시 상반신 이미지를 업로드하세요", None

        landmarks = results.pose_landmarks.landmark
        left_shoulder = landmarks[mp_pose.PoseLandmark.LEFT_SHOULDER]
        right_shoulder = landmarks[mp_pose.PoseLandmark.RIGHT_SHOULDER]
        left_hip = landmarks[mp_pose.PoseLandmark.LEFT_HIP]
        right_hip = landmarks[mp_pose.PoseLandmark.RIGHT_HIP]

        shoulder_y = (left_shoulder.y + right_shoulder.y) / 2
        hip_y = (left_hip.y + right_hip.y) / 2
        print(f"shoulder_y: {shoulder_y:.3f}, hip_y: {hip_y:.3f}, diff: {hip_y - shoulder_y:.3f}")


        if hip_y - shoulder_y > 0.2:  # 상반신 기준: 어깨와 엉덩이 사이의 Y 좌표 차이가 0.2 이상 -> 수정해서 체크
            return "상반신", image
        else:
            return "다시 상반신 이미지를 업로드하세요", None

# 2. 정면 검출
def is_facing_forward(landmarks, image_shape):
    import mediapipe as mp
    import numpy as np

    mp_pose = mp.solutions.pose

    def get_point(p):
        return np.array([int(p.x * image_shape[1]), int(p.y * image_shape[0])])

    # 좌표 추출
    left_eye = get_point(landmarks[mp_pose.PoseLandmark.LEFT_EYE])
    right_eye = get_point(landmarks[mp_pose.PoseLandmark.RIGHT_EYE])
    left_shoulder = get_point(landmarks[mp_pose.PoseLandmark.LEFT_SHOULDER])
    right_shoulder = get_point(landmarks[mp_pose.PoseLandmark.RIGHT_SHOULDER])

    try:
        left_ear = get_point(landmarks[mp_pose.PoseLandmark.LEFT_EAR])
        right_ear = get_point(landmarks[mp_pose.PoseLandmark.RIGHT_EAR])
        ears_visible = True
    except:
        ears_visible = False

    if not ears_visible:
        print("▶ 귀 검출 여부: X (정면 조건 불충족)")
        return False

    # 각도 계산 함수 (0~360도 범위 보정)
    def angle(p1, p2):
        deg = np.degrees(np.arctan2(p2[1] - p1[1], p2[0] - p1[0]))
        if deg < 0:
            deg += 360
        return deg

    # (1) 눈 수평 기울기: 180 ±10도 허용
    eye_angle = angle(left_eye, right_eye)
    is_eyes_parallel = (170 <= eye_angle <= 190)

    # (2) 눈 크기 비율: 5% 이내 허용
    eye_size_l = np.linalg.norm(
        get_point(landmarks[mp_pose.PoseLandmark.LEFT_EYE_INNER]) -
        get_point(landmarks[mp_pose.PoseLandmark.LEFT_EYE_OUTER])
    )
    eye_size_r = np.linalg.norm(
        get_point(landmarks[mp_pose.PoseLandmark.RIGHT_EYE_INNER]) -
        get_point(landmarks[mp_pose.PoseLandmark.RIGHT_EYE_OUTER])
    )
    eye_size_ratio = abs(eye_size_l - eye_size_r) / max(eye_size_l, eye_size_r)
    is_eye_size_similar = eye_size_ratio <= 0.5

    # (3) 어깨 수평 기울기: 180 ±10도 허용
    shoulder_angle = angle(left_shoulder, right_shoulder)
    is_shoulders_parallel = (170 <= shoulder_angle <= 190)

    # (4) 중심점 수직선 기울기: 90 ±5도 허용
    center_eye = (left_eye + right_eye) / 2
    center_ear = (left_ear + right_ear) / 2
    center_shoulder = (left_shoulder + right_shoulder) / 2
    center_avg = (center_eye + center_ear + center_shoulder) / 3
    img_center = np.array([image_shape[1] // 2, image_shape[0] // 2])

    vertical_angle = angle(img_center, center_avg)  # ← 인물 중심이 위/아래로 얼마나 치우쳤는지
    horizontal_diff = min(
        abs(vertical_angle - 90),     # 수평 오른쪽 기준
        abs(vertical_angle - 270)    # 수평 왼쪽 기준
    )

    is_horizontal_aligned = horizontal_diff <= 5
    # 조건별 디버깅 출력
    print(f"▶ 눈 각도: {eye_angle:.2f}° → {'O' if is_eyes_parallel else 'X'}")
    print(f"▶ 눈 크기 차이 비율: {eye_size_ratio:.2%} → {'O' if is_eye_size_similar else 'X'}")
    print(f"▶ 귀 검출 여부: {'O' if ears_visible else 'X'}")
    print(f"▶ 어깨 각도: {shoulder_angle:.2f}° → {'O' if is_shoulders_parallel else 'X'}")
    print(f"▶ 중심 수평 기울기 오차: {horizontal_diff:.2f}° → {'O' if is_horizontal_aligned else 'X'}")

    return all([
        is_eyes_parallel,
        is_eye_size_similar,
        ears_visible,
        is_shoulders_parallel,
        # is_vertical_aligned
        is_horizontal_aligned  
    ])


# 3. 분석 함수
def analyze_image_from_path(image_path):
    if not os.path.exists(image_path):
        print("이미지 경로가 잘못되었습니다.")
        return

    image = cv2.imread(image_path)
    status, upper_img = detect_upper_body(image)
    print("상반신 판단 결과:", status)

    if status != "상반신":
        return

    mp_pose = mp.solutions.pose
    with mp_pose.Pose(static_image_mode=True) as pose:
        results = pose.process(cv2.cvtColor(upper_img, cv2.COLOR_BGR2RGB))
        if not results.pose_landmarks:
            print("다시 상반신 이미지를 업로드하세요")
            return

        # 시각화 준비
        annotated_image = upper_img.copy()
        mp_drawing = mp.solutions.drawing_utils
        mp_drawing.draw_landmarks(
            annotated_image, results.pose_landmarks, mp_pose.POSE_CONNECTIONS
        )

        # 평행성 확인용 선 그리기
        def get_point(p):
            return np.array([int(p.x * upper_img.shape[1]), int(p.y * upper_img.shape[0])])

        landmarks = results.pose_landmarks.landmark
        pts = {
            "eye": (
                get_point(landmarks[mp_pose.PoseLandmark.LEFT_EYE]),
                get_point(landmarks[mp_pose.PoseLandmark.RIGHT_EYE]),
            ),
            "shoulder": (
                get_point(landmarks[mp_pose.PoseLandmark.LEFT_SHOULDER]),
                get_point(landmarks[mp_pose.PoseLandmark.RIGHT_SHOULDER]),
            ),
            "ear": (
                get_point(landmarks[mp_pose.PoseLandmark.LEFT_EAR]),
                get_point(landmarks[mp_pose.PoseLandmark.RIGHT_EAR]),
            ),
        }

        cv2.line(annotated_image, *pts["eye"], (0, 255, 0), 2)       # 초록
        cv2.line(annotated_image, *pts["shoulder"], (255, 0, 0), 2)  # 파랑
        cv2.line(annotated_image, *pts["ear"], (0, 0, 255), 2)       # 빨강

        # 결과 판단
        if is_facing_forward(landmarks, upper_img.shape):
            print("정면 상반신 이미지입니다.")
        else:
            print("상반신은 맞지만, 정면이 아닙니다.")

        # RGB 변환 후 matplotlib 시각화
        annotated_rgb = cv2.cvtColor(annotated_image, cv2.COLOR_BGR2RGB)
        plt.imshow(annotated_rgb)
        plt.title("정면 판단 선 시각화")
        plt.axis("off")
        plt.show()

if __name__ == "__main__":
    # image_absolute_path = "/home/aa/Big2025/aaatest/instance/testsample/kids.png"  # ← 실제 이미지 경로로 바꿔주세요
    image_absolute_path = "/home/aa/Big2025/aaatest/static/images/7.jpg"
    analyze_image_from_path(image_absolute_path)
