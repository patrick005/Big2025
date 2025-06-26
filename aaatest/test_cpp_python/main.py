import subprocess
import os

def run_pose_crop(image_path: str):
    result_path = "pose_result.txt"

    # C++ 실행
    command = ["./pose_crop", image_path, result_path]
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    if result.returncode != 0:
        print("C++ 실행 중 오류 발생:", result.stderr.decode())
        return

    if not os.path.exists(result_path):
        print("결과 파일이 생성되지 않았습니다.")
        return

    with open(result_path, "r", encoding="utf-8") as f:
        result_line = f.read().strip()

    if result_line.startswith("CROPPED"):
        print("하반신 포함됨 → 상반신으로 Crop 수행됨:", result_line.split()[1])
    elif result_line.startswith("UPPER"):
        print("상반신만 포함된 이미지입니다.")
    else:
        print("검출 실패:", result_line)

if __name__ == "__main__":
    image_path = "/home/aa/Big2025/aaatest/static/images/5.jpg"  # 테스트 이미지 경로
    run_pose_crop(image_path)
