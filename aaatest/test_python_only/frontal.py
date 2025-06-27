# # frontal.py
# import numpy as np
# import mediapipe as mp

# def is_facing_forward(landmarks, image_shape):
#     mp_pose = mp.solutions.pose

#     def get_point(p):
#         return np.array([int(p.x * image_shape[1]), int(p.y * image_shape[0])])

#     left_eye = get_point(landmarks[mp_pose.PoseLandmark.LEFT_EYE])
#     right_eye = get_point(landmarks[mp_pose.PoseLandmark.RIGHT_EYE])
#     left_shoulder = get_point(landmarks[mp_pose.PoseLandmark.LEFT_SHOULDER])
#     right_shoulder = get_point(landmarks[mp_pose.PoseLandmark.RIGHT_SHOULDER])

#     try:
#         left_ear = get_point(landmarks[mp_pose.PoseLandmark.LEFT_EAR])
#         right_ear = get_point(landmarks[mp_pose.PoseLandmark.RIGHT_EAR])
#         ears_visible = True
#     except:
#         ears_visible = False

#     if not ears_visible:
#         print("[Ear Detection] Failed")
#         return False

#     def angle(p1, p2):
#         deg = np.degrees(np.arctan2(p2[1] - p1[1], p2[0] - p1[0]))
#         if deg < 0:
#             deg += 360
#         return deg

#     eye_angle = angle(left_eye, right_eye)
#     is_eyes_parallel = (170 <= eye_angle <= 190)

#     eye_size_l = np.linalg.norm(
#         get_point(landmarks[mp_pose.PoseLandmark.LEFT_EYE_INNER]) -
#         get_point(landmarks[mp_pose.PoseLandmark.LEFT_EYE_OUTER])
#     )
#     eye_size_r = np.linalg.norm(
#         get_point(landmarks[mp_pose.PoseLandmark.RIGHT_EYE_INNER]) -
#         get_point(landmarks[mp_pose.PoseLandmark.RIGHT_EYE_OUTER])
#     )
#     eye_size_ratio = abs(eye_size_l - eye_size_r) / max(eye_size_l, eye_size_r)
#     is_eye_size_similar = eye_size_ratio <= 0.5

#     shoulder_angle = angle(left_shoulder, right_shoulder)
#     is_shoulders_parallel = (170 <= shoulder_angle <= 190)

#     center_eye = (left_eye + right_eye) / 2
#     center_ear = (left_ear + right_ear) / 2
#     center_shoulder = (left_shoulder + right_shoulder) / 2
#     center_avg = (center_eye + center_ear + center_shoulder) / 3
#     img_center = np.array([image_shape[1] // 2, image_shape[0] // 2])

#     vertical_angle = angle(img_center, center_avg)
#     horizontal_diff = min(
#         abs(vertical_angle - 90),
#         abs(vertical_angle - 270)
#     )

#     is_horizontal_aligned = horizontal_diff <= 5

#     print(f"[Eye Angle] {eye_angle:.2f}° → {'OK' if is_eyes_parallel else 'Fail'}")
#     print(f"[Eye Size Ratio] {eye_size_ratio:.2%} → {'OK' if is_eye_size_similar else 'Fail'}")
#     print(f"[Shoulder Angle] {shoulder_angle:.2f}° → {'OK' if is_shoulders_parallel else 'Fail'}")
#     print(f"[Vertical Offset] {horizontal_diff:.2f}° → {'OK' if is_horizontal_aligned else 'Fail'}")

#     return all([
#         is_eyes_parallel,
#         is_eye_size_similar,
#         ears_visible,
#         is_shoulders_parallel,
#         is_horizontal_aligned
#     ])

# frontal.py
import numpy as np
import mediapipe as mp

def is_facing_forward(landmarks, image_shape):
    mp_pose = mp.solutions.pose

    def get_point(p):
        return np.array([int(p.x * image_shape[1]), int(p.y * image_shape[0])])

    try:
        left_eye = get_point(landmarks[mp_pose.PoseLandmark.LEFT_EYE])
        right_eye = get_point(landmarks[mp_pose.PoseLandmark.RIGHT_EYE])
        left_shoulder = get_point(landmarks[mp_pose.PoseLandmark.LEFT_SHOULDER])
        right_shoulder = get_point(landmarks[mp_pose.PoseLandmark.RIGHT_SHOULDER])
        left_ear = get_point(landmarks[mp_pose.PoseLandmark.LEFT_EAR])
        right_ear = get_point(landmarks[mp_pose.PoseLandmark.RIGHT_EAR])
    except:
        print("[Ear Detection] Failed")
        return False

    def angle(p1, p2):
        deg = np.degrees(np.arctan2(p2[1] - p1[1], p2[0] - p1[0]))
        return deg + 360 if deg < 0 else deg

    eye_angle = angle(left_eye, right_eye)
    is_eyes_parallel = (170 <= eye_angle <= 190)

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

    shoulder_angle = angle(left_shoulder, right_shoulder)
    is_shoulders_parallel = (170 <= shoulder_angle <= 190)

    center_eye = (left_eye + right_eye) / 2
    center_ear = (left_ear + right_ear) / 2
    center_shoulder = (left_shoulder + right_shoulder) / 2
    center_avg = (center_eye + center_ear + center_shoulder) / 3
    img_center = np.array([image_shape[1] // 2, image_shape[0] // 2])

    vertical_angle = angle(img_center, center_avg)
    horizontal_diff = min(abs(vertical_angle - 90), abs(vertical_angle - 270))
    is_horizontal_aligned = horizontal_diff <= 5

    print(f"[Eye Angle] {eye_angle:.2f}° → {'OK' if is_eyes_parallel else 'Fail'}")
    print(f"[Eye Size Ratio] {eye_size_ratio:.2%} → {'OK' if is_eye_size_similar else 'Fail'}")
    print(f"[Shoulder Angle] {shoulder_angle:.2f}° → {'OK' if is_shoulders_parallel else 'Fail'}")
    print(f"[Vertical Offset] {horizontal_diff:.2f}° → {'OK' if is_horizontal_aligned else 'Fail'}")

    return all([
        is_eyes_parallel,
        is_eye_size_similar,
        is_shoulders_parallel,
        is_horizontal_aligned
    ])
