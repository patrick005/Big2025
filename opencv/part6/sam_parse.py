# sam_parse.py
import cv2
import matplotlib.pyplot as plt
import numpy as np
import os
import argparse

from segment_anything import SamAutomaticMaskGenerator, sam_model_registry
# pip install git+https://github.com/facebookresearch/segment-anything.git

parser = argparse.ArgumentParser()
parser.add_argument(
    '--input',
    default='/home/aa/Big2025/aaatest/static/uploads/877d7b3f4d662f3ee6f3c74d58f66e91.jpg',
    help='Path to input image'
)
args = parser.parse_args()

if not os.path.exists('outputs'):
    os.makedirs('outputs')

# 마스크 시각화 함수
def show_anns(anns):
    if len(anns) == 0:
        return
    sorted_anns = sorted(anns, key=(lambda x: x['area']), reverse=True)
    ax = plt.gca()
    ax.set_autoscale_on(False)
    for ann in sorted_anns:
        m = ann['segmentation']
        img = np.ones((m.shape[0], m.shape[1], 3))
        color_mask = np.random.random((1, 3)).tolist()[0]
        for i in range(3):
            img[:, :, i] = color_mask[i]
        ax.imshow(np.dstack((img, m * 0.35)))

# 모델 로드 및 마스크 생성
data_folder = "/home/aa/Big2025/opencv/data/"
checkpoint_path = os.path.join(data_folder, "sam_vit_b.pth")

sam = sam_model_registry["vit_b"](checkpoint=checkpoint_path)
# sam.cuda()  # 필요시 GPU 사용
mask_generator = SamAutomaticMaskGenerator(sam)

# 이미지 불러오기
image_path = args.input
image_name = os.path.basename(image_path)
image = cv2.imread(image_path)
image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

# 마스크 생성
masks = mask_generator.generate(image)

# 시각화 및 저장
plt.figure(figsize=(12, 9))
plt.imshow(image)
show_anns(masks)
plt.axis('off')
plt.savefig(os.path.join('outputs', image_name), bbox_inches='tight')
plt.close()
