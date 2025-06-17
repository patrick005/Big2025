// opencv/part7/59_mnist_cnn.cpp
// compare with opencv/part7/model_server.py
#include <iostream>
#include <opencv2/opencv.hpp>
#include <zmq.hpp>
#include <vector>
#include <string>
#include <unistd.h> // for sleep()

using namespace std;
using namespace cv;
using namespace zmq;

void on_mouse(int event, int x, int y, int flags, void* userdata);

int main() {
    context_t context(1);
    socket_t requester(context, socket_type::req);
    const char* ipc_file_path = "/tmp/zmq_server";
    requester.connect("ipc://" + string(ipc_file_path));
    cout << "클라이언트가 ipc 소켓에 연결되었습니다: " << ipc_file_path << endl;

    // 그리기용 캔버스 생성
    Mat img = Mat::zeros(400, 400, CV_8UC1);
    imshow("그림판", img);
    setMouseCallback("그림판", on_mouse, &img);

    while (true) {
        int key = waitKey(30);
        if (key == 27) break; // ESC 누르면 종료

        else if (key == ' ') {
            // PNG로 인코딩
            vector<uchar> buf;
            imencode(".png", img, buf);

            // 전송
            message_t msg(buf.data(), buf.size());
            requester.send(msg, send_flags::none);

            // 응답 수신
            message_t reply_msg;
            auto reply_result = requester.recv(reply_msg, recv_flags::none);
            if (reply_result && reply_result.value() > 0) {
                cout << "서버 예측 결과: " << reply_msg.to_string() << endl;
            } else {
                cerr << "서버 응답 실패" << endl;
            }
            img = Mat::zeros(img.size(), CV_8UC1);
            imshow("그림판", img);
        }else if(key == 's') {
            // 현재 이미지를 저장
            imwrite("drawing.png", img);
            cout << "그림을 drawing.png로 저장했습니다." << endl;
        }
    }

    return 0;
}

void on_mouse(int event, int x, int y, int flags, void* userdata) {
    Mat& img = *(Mat*)userdata;
    static Point ptPrev(-1, -1);
    static bool drawing = false;

    if (event == EVENT_LBUTTONDOWN) {
        ptPrev = Point(x, y);
        drawing = true;
    } else if (event == EVENT_LBUTTONUP) {
        drawing = false;
    } else if (event == EVENT_MOUSEMOVE && drawing) {
        line(img, ptPrev, Point(x, y), Scalar(255), 30, LINE_AA);
        ptPrev = Point(x, y);
        imshow("그림판", img);
    }
}
