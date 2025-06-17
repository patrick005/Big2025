import os
import time

import zmq
import random # 테스팅용으로 메시지 생성에 사용

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
    try:
        while True:
            message = [random.randint(0, 100) for _ in range(70)]
            print(f"요청 메시지 {request_count + 1} : {message}")
            socket.send_string(" ".join(map(str, message)))
            response = socket.recv_string()
            print(f"받은 응답: {response}")
            request_count += 1
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