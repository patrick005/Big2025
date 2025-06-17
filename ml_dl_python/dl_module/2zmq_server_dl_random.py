import zmq
import os
import time
import tensorflow as tf
from tensorflow.keras.preprocessing.sequence import pad_sequences

IPC_FILE_PATH = "/tmp/zmq_server"

def main():

    # model 로드
    model = tf.keras.models.load_model(
        "/home/aa/Big2025/ml_dl_python/dl_module/best-bi-lstm-model.keras"
    )
    print("모델이 성공적으로 로드되었습니다.")
    if not model:
        print("모델 로드에 실패했습니다. 서버를 종료합니다.")
        return
    print(f"모델 구조: {model.summary()}")
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    os.unlink(IPC_FILE_PATH) if os.path.exists(IPC_FILE_PATH) else None
    socket.bind(f"ipc://{IPC_FILE_PATH}")
    print(f"ZMQ REP 서버가 {IPC_FILE_PATH}에 바인딩되었습니다.") 

    try:
        while True:
            message = socket.recv_string()
            message = [int(x) for x in message.split() if x.isdigit()]
            val_seq = pad_sequences([message], maxlen=100)
            print(f"수신된 메시지: {message}")
            prediction = model.predict(val_seq)
            print(f"예측 결과: {prediction}")
            socket.send_string(f"예측 결과: {prediction}")
            time.sleep(0.1)
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