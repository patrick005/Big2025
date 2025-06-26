# # upload_img_check.py
# import cv2
# import mediapipe as mp
# from bust import detect_upper_body
# from frontal import is_facing_forward

# # 이미지 경로 설정
# image_path = "/home/aa/Big2025/aaatest/static/images/7.jpg"

# # 이미지 로드
# image = cv2.imread(image_path)
# if image is None:
#     print("[Error] Failed to load image.")
#     exit(1)

# # 1. 상반신 판단 + Crop (결과 시각화 포함)
# bust_status, keypoints = detect_upper_body(image, visualize_crop=True)
# print(f"[Upper Body Status] {bust_status}")

# if bust_status == "Chest Not Detected":
#     print("[Result] Chest detection failed.")
#     exit(0)

# # 2. 정면 판단
# mp_pose = mp.solutions.pose
# with mp_pose.Pose(static_image_mode=True, model_complexity=1) as pose:
#     results = pose.process(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
#     if not results.pose_landmarks:
#         print("[Result] Pose landmarks not detected.")
#         exit(1)

#     landmarks = results.pose_landmarks.landmark
#     is_frontal = is_facing_forward(landmarks, image.shape)

#     if is_frontal:
#         print("[Result] Valid: Frontal + Upper Body")
#     else:
#         print("[Result] Upper body only, not frontal")

# upload_img_check.py
import cv2
import mediapipe as mp
from .bust import detect_upper_body
from .frontal import is_facing_forward

def check_uploaded_image(image_path: str) -> str:
    # 이미지 로드
    image = cv2.imread(image_path)
    if image is None:
        print("[Error] Failed to load image.")
        return "DECODE_FAIL"

    # 1. 상반신 검출
    bust_status, keypoints = detect_upper_body(image, visualize_crop=True)  # 디버깅용 imshow 유지
    print(f"[Upper Body Status] {bust_status}")
    
    if bust_status == "Chest Not Detected":
        return "CHEST_NOT_DETECTED"

    # 2. 정면 여부 판단 (원본 이미지 사용해야 keypoint 정합성 유지됨)
    mp_pose = mp.solutions.pose
    with mp_pose.Pose(static_image_mode=True) as pose:
        results = pose.process(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
        if not results.pose_landmarks:
            return "LANDMARK_NOT_FOUND"

        landmarks = results.pose_landmarks.landmark
        is_frontal = is_facing_forward(landmarks, image.shape)

        if is_frontal:
            return "VALID"
        else:
            return "NOT_FRONTAL"