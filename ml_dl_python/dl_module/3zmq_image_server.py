import zmq
import os
import time
import cv2
import numpy as np

IPC_FILE_PATH = "/tmp/zmq_server"

def main():
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    os.unlink(IPC_FILE_PATH) if os.path.exists(IPC_FILE_PATH) else None
    socket.bind(f"ipc://{IPC_FILE_PATH}")
    print(f"ZMQ REP 서버가 {IPC_FILE_PATH}에 바인딩되었습니다")

    try:
        while True:
            # 이미지 수신
            message = socket.recv()
            image = cv2.imdecode(np.frombuffer(message, np.uint8), cv2.IMREAD_COLOR)
            cv2.imshow("Received Image", image)

            socket.send_string(f"이미지 수신 완료")
            cv2.waitKey(1)
    except KeyboardInterrupt:
        print("서버를 종료합니다.")
    finally:
        socket.close()
        context.term()
        os.unlink(IPC_FILE_PATH)

if __name__ == "__main__":
    main()

#프로젝트 구성으로 DB와 딥러닝 모듈이랑 여러 분산처리 수행 모듈(process)에 대한 api 통신과 zmq 통신을 사용
#2차 때 시켰던 zmq 서버와 클라이언트를 작성해서 케라스 연동을 하는 예제