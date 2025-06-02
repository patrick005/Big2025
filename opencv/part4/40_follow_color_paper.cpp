// // 카메라를 켜서 frame 확보
// // 색 공간 -> hsv로 변경 clone() 해서 따로 처리(원본과 처리본 2개 출력)
// // 양방향 필터 처리
// // inrange -> 색종이 인식
// // morph 함수 -> 이진화 Mat 정리
// // 이걸 바탕으로 labeling
// // 화면에 rectangle로 표시
// // putText, ft2로 색종이 or color-paper라고 표기
// // 사각형과 폰트는 색종이를 따라다녀야함


// // #include "/home/aa/Big2025/opencv/part2/color.hpp" // 현재 코드에서는 사용되지 않으므로 주석 처리
// #include <iostream>
// #include <opencv2/opencv.hpp>
// #include <opencv2/freetype.hpp> // FreeType 사용을 위한 헤더
// #include <chrono>
// #include <thread>
// #include <vector>

// using namespace std;

// int main() {
//     // 1. 카메라를 켜서 frame 확보
//     cv::VideoCapture cap(0); // 0번 카메라 장치 열기

//     if (!cap.isOpened()) {
//         cerr << "카메라를 열 수 없습니다." << endl;
//         return -1;
//     }

//     // FreeType 객체 생성
//     cv::Ptr<cv::freetype::FreeType2> ft2 = cv::freetype::createFreeType2();
//     try {
//         ft2->loadFontData("/home/aa/Big2025/opencv/data/NanumPenScript-Regular.ttf", 0); 
//     } catch (const cv::Exception& e) {
//         // cerr << "폰트 파일을 로드할 수 없습니다: " << e.what() << endl;
//         // cerr << "폰트 경로를 확인하거나 다른 폰트 파일을 사용하세요." << cerr;
//         return -1;
//     }


//     cv::Mat frame;
//     while (true) {
//         cap >> frame; // 카메라에서 프레임 읽기
//         if (frame.empty()) {
//             cerr << "프레임을 읽을 수 없습니다." << endl;
//             break;
//         }

//         // 2. 색 공간 -> hsv로 변경 clone() 해서 따로 처리(원본과 처리본 2개 출력)
//         cv::Mat hsv_frame;
//         cv::cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);

//         cv::Mat processed_frame = hsv_frame.clone(); // 처리본 생성

//         // 3. 양방향 필터 처리 (노이즈 감소 및 엣지 보존)
//         cv::Mat bilateral_filtered_frame;
//         cv::bilateralFilter(processed_frame, bilateral_filtered_frame, 9, 75, 75);

//         // 4. inrange -> 색종이 인식 (예시: 빨간색 범위. 실제 색상 범위는 조절 필요)
//         // HSV에서 빨간색 범위는 0-10, 170-180 (Hue), 100-255 (Saturation), 100-255 (Value)
//         // 두 개의 범위로 나누어 처리해야 함
//         cv::Mat mask1, mask2, color_mask;
//         cv::inRange(bilateral_filtered_frame, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), mask1);
//         cv::inRange(bilateral_filtered_frame, cv::Scalar(170, 100, 100), cv::Scalar(180, 255, 255), mask2);
//         cv::bitwise_or(mask1, mask2, color_mask);

//         // 5. morph 함수 -> 이진화 Mat 정리 (열림/닫힘 연산을 통해 노이즈 제거 및 객체 연결)
//         cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
//         cv::Mat morph_result;
//         cv::morphologyEx(color_mask, morph_result, cv::MORPH_OPEN, kernel); // 열림 연산
//         cv::morphologyEx(morph_result, morph_result, cv::MORPH_CLOSE, kernel); // 닫힘 연산

//         // 6. 5번까지를 바탕으로 labeling
//         vector<vector<cv::Point>> contours;
//         cv::findContours(morph_result, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

//         // 7. 화면에 rectangle로 표시, 8. putText, ft2로 색종이 or color-paper라고 표기, 9. 8번 항목에 대한 사각형과 폰트는 색종이를 따라다녀야 함
//         for (const auto& contour : contours) {
//             double area = cv::contourArea(contour);
//             if (area > 500) { // 작은 노이즈 영역 제거
//                 cv::Rect bounding_rect = cv::boundingRect(contour);

//                 // 색종이 주변에 사각형 그리기
//                 cv::rectangle(frame, bounding_rect, cv::Scalar(0, 255, 0), 2); // 초록색 사각형

//                 // 텍스트 내용 및 위치
//                 string text = "색종이 (color-paper)";
//                 int font_size = 30; // 폰트 크기
//                 int baseline = 0;
//                 cv::Size text_size = ft2->getTextSize(text, font_size, 2, &baseline); // 폰트 두께 2

//                 // 텍스트 위치 계산 (사각형 중앙 상단에 표시)
//                 int text_x = bounding_rect.x + (bounding_rect.width - text_size.width) / 2;
//                 int text_y = bounding_rect.y - 10; // 사각형 상단보다 조금 위에

//                 if (text_y < text_size.height) { // 화면 상단을 넘어가지 않도록 조정
//                     text_y = text_size.height;
//                 }
//                 if (text_x < 0) { // 화면 좌측을 넘어가지 않도록 조정
//                     text_x = 0;
//                 }

//                 // 텍스트 배경 사각형 (선택 사항, 텍스트 가독성을 높임)
//                 cv::rectangle(frame, cv::Point(text_x, text_y - text_size.height),
//                               cv::Point(text_x + text_size.width, text_y + baseline),
//                               cv::Scalar(0, 0, 0), cv::FILLED); // 검정색 배경

//                 // 텍스트 그리기
//                 ft2->putText(frame, text, cv::Point(text_x, text_y), font_size,
//                              cv::Scalar(0, 255, 255), 2, cv::LINE_AA, true); // 노란색 텍스트, 두께 2
//             }
//         }

//         // 결과 화면 표시
//         cv::imshow("원본 프레임", frame);
//         cv::imshow("HSV 처리 프레임", processed_frame); // HSV 변환된 프레임
//         cv::imshow("색상 마스크", color_mask); // 색상 범위에 따른 마스크
//         cv::imshow("모폴로지 결과", morph_result); // 모폴로지 연산 결과

//         if (cv::waitKey(1) == 'q') { // 'q' 키를 누르면 종료
//             break;
//         }
//     }

//     cap.release(); // 카메라 자원 해제
//     cv::destroyAllWindows(); // 모든 창 닫기

//     return 0;
// }

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/freetype.hpp>
#include <chrono>
#include <thread>
#include <vector>

int main() {
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "카메라를 열 수 없습니다." << std::endl;
        return -1;
    }

    cv::Ptr<cv::freetype::FreeType2> ft2 = cv::freetype::createFreeType2();
    try {
        ft2->loadFontData("/home/aa/Big2025/opencv/data/NanumPenScript-Regular.ttf", 0); 
    } catch (const cv::Exception& e) {
        // std::cerr << "폰트 파일을 로드할 수 없습니다: " << e.what() << std::endl;
        // std::cerr << "폰트 경로를 확인하거나 다른 폰트 파일을 사용하세요." << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "프레임을 읽을 수 없습니다." << std::endl;
            break;
        }

        // 1. 그레이스케일 변환
        cv::Mat gray_frame;
        cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);

        // 2. 대비 향상 (CLAHE 사용)
        // 특히 저조도나 그림자가 있는 환경에서 효과적
        cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE(2.0, cv::Size(6, 6)); // ClipLimit와 TileGridSize 조절 가능
        clahe->apply(gray_frame, gray_frame);

        // 3. 가우시안 블러 (노이즈 감소) - 대비 향상 후 다시 적용하여 노이즈 영향 최소화
        cv::GaussianBlur(gray_frame, gray_frame, cv::Size(5, 5), 0);

        // 4. 이진화 (adaptiveThreshold 사용)
        cv::Mat binary_frame;
        cv::adaptiveThreshold(gray_frame, binary_frame, 255,
                              cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY_INV, 19, 5); // blockSize, C 값 조절
        // blockSize를 더 크게 (예: 21), C 값을 약간 높게 (예: 5) 설정하여 더 넓은 영역의 평균을 고려하고,
        // 경계를 더 명확히 합니다.

        // 5. 모폴로지 연산 (작은 노이즈 제거 및 연결)
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        cv::morphologyEx(binary_frame, binary_frame, cv::MORPH_OPEN, kernel, cv::Point(-1, -1), 1); // 열림 1회
        cv::morphologyEx(binary_frame, binary_frame, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), 1); // 닫힘 1회
        // 모폴로지 연산 횟수를 1회로 줄여 객체 형태 손상을 최소화.

        // 6. Canny 엣지 검출 (이진화된 이미지에서 더욱 선명한 엣지 추출)
        // 이진화 후에도 Canny를 적용하여 윤곽선을 더 명확하게 함.
        cv::Mat edges;
        cv::Canny(binary_frame, edges, 30, 150); // Canny 임계값 조절 가능

        // 7. 윤곽선(Contour) 검출 (edges에서 윤곽선 찾기)
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(edges, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

        // 8. 윤곽선 분석 및 사각형 필터링
        for (const auto& contour : contours) {
            double epsilon = 0.02 * cv::arcLength(contour, true);
            std::vector<cv::Point> approx_curve;
            cv::approxPolyDP(contour, approx_curve, epsilon, true);

            if (approx_curve.size() == 4 && cv::isContourConvex(approx_curve)) {
                double area = cv::contourArea(approx_curve);
                if (area < 2000 || area > 500000) continue; // 면적 필터링 범위 조정 (더 큰 객체 위주)

                cv::RotatedRect min_rect = cv::minAreaRect(approx_curve);
                cv::Point2f rect_points[4];
                min_rect.points(rect_points);
                for (int j = 0; j < 4; j++) {
                    cv::line(frame, rect_points[j], rect_points[(j + 1) % 4], cv::Scalar(0, 255, 255), 2);
                }

                std::string text = "사각형 (Rectangle)";
                double aspect_ratio = min_rect.size.width / min_rect.size.height;
                if (aspect_ratio > 0.8 && aspect_ratio < 1.2) {
                    text = "정사각형 (Square)";
                }

                int font_size = 25;
                int baseline = 0;
                cv::Size text_size = ft2->getTextSize(text, font_size, 2, &baseline);

                int text_x = static_cast<int>(min_rect.center.x - text_size.width / 2);
                int text_y = static_cast<int>(min_rect.center.y - min_rect.size.height / 2 - 10);

                if (text_x < 0) text_x = 0;
                if (text_y < text_size.height) text_y = text_size.height;
                if (text_x + text_size.width > frame.cols) text_x = frame.cols - text_size.width;

                cv::rectangle(frame, cv::Point(text_x, text_y - text_size.height),
                              cv::Point(text_x + text_size.width, text_y + baseline),
                              cv::Scalar(0, 0, 0), cv::FILLED);
                ft2->putText(frame, text, cv::Point(text_x, text_y), font_size,
                             cv::Scalar(0, 255, 0), 2, cv::LINE_AA, true);
            }
        }

        cv::imshow("원본 프레임 (사각형 검출)", frame);
        cv::imshow("이진화 결과 (개선됨)", binary_frame);
        cv::imshow("엣지 검출 결과 (개선됨)", edges); // 개선된 엣지 결과도 함께 출력

        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}