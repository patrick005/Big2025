# opencv/part7/model_server.py
# compare with opencv/part7/59_mnist_cnn.cpp
#프로젝트 구성으로 DB와 딥러닝 모듈이랑 여러 분산처리 수행 모듈(process)에 대한 api 통신과 zmq 통신을 사용
#2차 때 시켰던 zmq 서버와 클라이언트를 작성해서 케라스 연동을 하는 예제

import zmq
import os
import time
import tensorflow as tf
import cv2
import numpy as np

IPC_FILE_PATH = "/tmp/zmq_server"

def main():
    # 모델 로딩
    model = tf.keras.models.load_model(
        "/home/aa/Big2025/opencv/part7/best-cnn-model.h5"
    )
    print("모델이 성공적으로 로드되었습니다.")
    print(f"모델 구조:"); model.summary()

    # ZMQ REP 소켓 설정
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    if os.path.exists(IPC_FILE_PATH):
        os.unlink(IPC_FILE_PATH)
    socket.bind(f"ipc://{IPC_FILE_PATH}")
    print(f"ZMQ REP 서버가 {IPC_FILE_PATH}에 바인딩되었습니다.") 

    try:
        while True:
            message = socket.recv()
            print(f"이미지 수신 ({len(message)} bytes)")

            # 이미지 복원
            img_array = np.frombuffer(message, np.uint8)
            image = cv2.imdecode(img_array, cv2.IMREAD_GRAYSCALE)

            if image is None:
                print("이미지 디코딩 실패")
                socket.send_string("디코딩 실패")
                continue

            # 입력 형태 조정 및 예측
            resized = cv2.resize(image, (28, 28))
            input_tensor = resized.reshape(-1, 28, 28, 1) / 255.0
            result = model.predict(input_tensor)
            predicted = int(np.argmax(result))

            print(f"예측 결과: {predicted}")
            socket.send_string(str(predicted))

    except KeyboardInterrupt:
        print("서버를 종료합니다.")
    finally:
        socket.close()
        context.term()
        if os.path.exists(IPC_FILE_PATH):
            os.unlink(IPC_FILE_PATH)

if __name__ == "__main__":
    main()
