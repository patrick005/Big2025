import os
import time

import zmq

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
            message = f"요청 메시지 {request_count + 1}"
            socket.send_string(message)
            print(f"보낸 메시지: {message}")
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
