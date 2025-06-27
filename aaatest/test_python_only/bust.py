# # bust.py
# import cv2
# import numpy as np

# # OpenPose MPI 모델 경로
# PROTO_FILE = "/home/aa/Big2025/aaatest/model/pose_deploy_linevec_faster_4_stages.prototxt"
# WEIGHTS_FILE = "/home/aa/Big2025/aaatest/model/pose_iter_160000.caffemodel"
# N_POINTS = 15
# THRESHOLD = 0.1

# # chest 기준 하위 keypoint ID
# LOWER_BODY_PART_IDS = [8, 9, 10, 11, 12, 13]
# CHEST_ID = 14
# HEAD_ID = 0
# LSHOULDER = 5
# RSHOULDER = 2
# LELBOW = 6
# RELBOW = 3

# def detect_upper_body(image, visualize_crop=False):
#     net = cv2.dnn.readNetFromCaffe(PROTO_FILE, WEIGHTS_FILE)
#     in_height, in_width = 368, 368
#     frame_height, frame_width = image.shape[:2]

#     blob = cv2.dnn.blobFromImage(image, 1.0 / 255, (in_width, in_height), (0, 0, 0), swapRB=False, crop=False)
#     net.setInput(blob)
#     output = net.forward()

#     H, W = output.shape[2], output.shape[3]
#     points = [None] * N_POINTS

#     for i in range(N_POINTS):
#         prob_map = output[0, i, :, :]
#         _, prob, _, point = cv2.minMaxLoc(prob_map)
#         x = int((frame_width * point[0]) / W)
#         y = int((frame_height * point[1]) / H)

#         if prob > THRESHOLD:
#             points[i] = (x, y)

#     if points[CHEST_ID] is None:
#         return "Chest Not Detected", None

#     for pid in LOWER_BODY_PART_IDS:
#         if pid < len(points) and points[pid] is not None:
#             # 상반신 crop 조건 진입 시 (하반신 포함 확인 후)
#             chest = points[CHEST_ID]
#             head = points[HEAD_ID] if points[HEAD_ID] is not None else (chest[0], chest[1] - 100)

#             # 상하 margin 확장
#             TOP_MARGIN = 60
#             BOTTOM_MARGIN = 100

#             # 좌우 범위: 팔꿈치가 검출되면 → 팔꿈치 기준으로, 아니면 어깨 간 거리 기반
#             elbows = [points[LELBOW], points[RELBOW]]
#             shoulders = [points[LSHOULDER], points[RSHOULDER]]

#             if all(e is not None for e in elbows):
#                 x_coords = [e[0] for e in elbows]
#                 x1 = min(x_coords) - 30
#                 x2 = max(x_coords) + 30
#             else:
#                 if any(s is None for s in shoulders):
#                     x1 = chest[0] - 100
#                     x2 = chest[0] + 100
#                 else:
#                     shoulder_dist = abs(shoulders[0][0] - shoulders[1][0])
#                     x1 = chest[0] - int(shoulder_dist / 2)
#                     x2 = chest[0] + int(shoulder_dist / 2)

#             # y 좌표 계산
#             y1 = head[1] - TOP_MARGIN
#             y2 = chest[1] + BOTTOM_MARGIN

#             # 클램핑
#             x1 = max(0, x1)
#             x2 = min(frame_width, x2)
#             y1 = max(0, y1)
#             y2 = min(frame_height, y2)

#             # Crop 및 시각화
#             cropped = image[y1:y2, x1:x2].copy()
#             if visualize_crop:
#                 cv2.imshow("Cropped Upper Body", cropped)
#                 print("[Info] Press ESC to exit preview.")
#                 if cv2.waitKey(0) == 27:
#                     cv2.destroyAllWindows()

#             return "Lower Body Included → Cropped", points

#     return "Upper Body", points

# bust.py
import cv2
import numpy as np

PROTO_FILE = "./model/pose_deploy_linevec_faster_4_stages.prototxt"
WEIGHTS_FILE = "./model/pose_iter_160000.caffemodel"
N_POINTS = 15
THRESHOLD = 0.1

LOWER_BODY_PART_IDS = [8, 9, 10, 11, 12, 13]
CHEST_ID = 14
HEAD_ID = 0
LSHOULDER = 5
RSHOULDER = 2
LELBOW = 6
RELBOW = 3

def detect_upper_body(image, visualize_crop=True):
    net = cv2.dnn.readNetFromCaffe(PROTO_FILE, WEIGHTS_FILE)
    in_height, in_width = 368, 368
    frame_height, frame_width = image.shape[:2]

    blob = cv2.dnn.blobFromImage(image, 1.0 / 255, (in_width, in_height), (0, 0, 0), swapRB=False, crop=False)
    net.setInput(blob)
    output = net.forward()

    H, W = output.shape[2], output.shape[3]
    points = [None] * N_POINTS

    for i in range(N_POINTS):
        prob_map = output[0, i, :, :]
        _, prob, _, point = cv2.minMaxLoc(prob_map)
        x = int((frame_width * point[0]) / W)
        y = int((frame_height * point[1]) / H)

        if prob > THRESHOLD:
            points[i] = (x, y)

    if points[CHEST_ID] is None:
        return "Chest Not Detected", None

    for pid in LOWER_BODY_PART_IDS:
        if pid < len(points) and points[pid] is not None:
            chest = points[CHEST_ID]
            head = points[HEAD_ID] if points[HEAD_ID] is not None else (chest[0], chest[1] - 100)

            TOP_MARGIN = 60
            BOTTOM_MARGIN = 100

            elbows = [points[LELBOW], points[RELBOW]]
            shoulders = [points[LSHOULDER], points[RSHOULDER]]

            if all(e is not None for e in elbows):
                x_coords = [e[0] for e in elbows]
                x1 = min(x_coords) - 30
                x2 = max(x_coords) + 30
            else:
                if any(s is None for s in shoulders):
                    x1 = chest[0] - 100
                    x2 = chest[0] + 100
                else:
                    shoulder_dist = abs(shoulders[0][0] - shoulders[1][0])
                    x1 = chest[0] - int(shoulder_dist / 2)
                    x2 = chest[0] + int(shoulder_dist / 2)

            y1 = head[1] - TOP_MARGIN
            y2 = chest[1] + BOTTOM_MARGIN

            x1 = max(0, x1)
            x2 = min(frame_width, x2)
            y1 = max(0, y1)
            y2 = min(frame_height, y2)

            cropped = image[y1:y2, x1:x2].copy()
            # --- Debugging code (now commented out) ---
            # if visualize_crop:
            #     cv2.imshow("Cropped Upper Body", cropped)
            #     print("[Info] Press ESC to exit preview.")
            #     if cv2.waitKey(0) == 27:
            #         cv2.destroyAllWindows()
            #         time.sleep(0.5)
            # --- End of debugging code ---
            
            # If the crop is successful, return the cropped image.
            print("[Status] Upper body successfully cropped.")
            return "UPPER_BODY", cropped
    
    return "Upper Body", points
