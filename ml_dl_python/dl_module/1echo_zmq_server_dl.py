import os
import time

import zmq

IPC_FILE_PATH = "/tmp/zmq_server"


def main():
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    os.unlink(IPC_FILE_PATH) if os.path.exists(IPC_FILE_PATH) else None
    socket.bind(f"ipc://{IPC_FILE_PATH}")
    print(f"ZMQ REP 서버가 {IPC_FILE_PATH}에 바인딩되었습니다")
    try:
        while True:
            message = socket.recv_string()
            print(f"받은 메시지: {message}")
            response = f"응답: {message}"  # echo 응답 메시지
            socket.send_string(response)
            print(f"보낸 응답: {response}")
            time.sleep(0.1)
    except KeyboardInterrupt:
        print("서버를 종료합니다.")
    finally:
        socket.close()
        context.term()
        os.unlink(IPC_FILE_PATH)


if __name__ == "__main__":
    main()
