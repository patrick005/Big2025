import os
import time

import zmq
 # 테스팅용으로 메시지 생성에 사용

IPC_FILE_PATH = "/tmp/zmq_server"


def main():
    context = zmq.Context()
    print("ZMQ REP 서버 연결 중")
    socket = context.socket(zmq.REQ)
    # IPC 파일이 존재하지 않으면 종료
    if not os.path.exists(IPC_FILE_PATH):
        print(
            f"IPC 파일 '{IPC_FILE_PATH}'이(가) 존재하지 않습니다. 서버를 시작해주세요."
        )
        return
    socket.connect(f"ipc://{IPC_FILE_PATH}")

    request_count = 0
    folder_path = "/home/aa/Big2025/opencv/data/"
    # jpg 파일만 필터링
    image_files = [f for f in os.listdir(folder_path) if f.endswith(".jpg")]
    try:
        while True:
            with open(f"{folder_path}/{image_files[request_count]}", "rb") as f:
                message = f.read()
            print(f"전송 이미지 {image_files[request_count]}")
            socket.send(message)
            response = socket.recv_string()
            request_count += 1
            print(f"받은 응답: {request_count} {response}")
            if request_count >= len(image_files):
                print("모든 이미지 전송 완료")
                break
            time.sleep(2)
    except KeyboardInterrupt:
        print("클라이언트를 종료합니다.")
    finally:
        socket.close()
        context.term()


if __name__ == "__main__":
    main()

#프로젝트 구성으로 DB와 딥러닝 모듈이랑 여러 분산처리 수행 모듈(process)에 대한 api 통신과 zmq 통신을 사용
#2차 때 시켰던 zmq 서버와 클라이언트를 작성해서 케라스 연동을 하는 예제