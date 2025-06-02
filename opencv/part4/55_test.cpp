#include <iostream>
#include <opencv2/opencv.hpp>

// 엣지검출 최적화

int main() {
    cv::VideoCapture cap(0); // 0번 카메라 장치 열기

    if (!cap.isOpened()) {
        std::cerr << "카메라를 열 수 없습니다." << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true) {
        cap >> frame; // 카메라에서 프레임 읽기
        if (frame.empty()) {
            std::cerr << "프레임을 읽을 수 없습니다." << std::endl;
            break;
        }

        // 그레이스케일 변환
        cv::Mat gray_frame;
        cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);

        // 가우시안 블러 (노이즈 감소)
        cv::GaussianBlur(gray_frame, gray_frame, cv::Size(5, 5), 0);

        // 엣지 검출 (Canny 사용)
        cv::Mat edges;
        cv::Canny(gray_frame, edges, 30, 150); // 낮은 임계값, 높은 임계값

        // 엣지 검출 결과 화면 표시
        cv::imshow("엣지 검출 결과", edges);

        if (cv::waitKey(1) == 'q') { // 'q' 키를 누르면 종료
            break;
        }
    }

    cap.release(); // 카메라 자원 해제
    cv::destroyAllWindows(); // 모든 창 닫기

    return 0;
}