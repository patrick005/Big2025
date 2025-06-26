// frontal_check.cpp
/*
g++ frontal_check.cpp `pkg-config --cflags --libs opencv4` -o frontal_check
 ./frontal_check
*/
#include <opencv2/opencv.hpp>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;
using namespace cv;

// ========================= 정면 판단 보조 함수 ========================= //

/**
 * @brief 두 점을 잇는 선의 기울기를 0~360도 범위의 절대 각도로 반환
 * @param p1 시작점
 * @param p2 끝점
 * @return 수직선 기울기 (단위: degree)
 */
float getVerticalAngle(Point2f p1, Point2f p2) {
    float angle = atan2(p2.y - p1.y, p2.x - p1.x) * 180 / CV_PI;
    if (angle < 0) angle += 360;
    return angle;
}

/**
 * @brief 두 각도 사이의 절대 차이를 계산 (360도 주기 보정 포함)
 * @param angle1 첫 번째 각도 (단위: degree)
 * @param angle2 두 번째 각도 (단위: degree)
 * @return 두 각도 간 차이 (단위: degree)
 */
float angleDifference(float angle1, float angle2) {
    float diff = abs(angle1 - angle2);
    return min(diff, 360 - diff);
}

/**
 * @brief 정면 여부 판단 함수
 * @param eyeL 왼쪽 눈 좌표
 * @param eyeR 오른쪽 눈 좌표
 * @param earL 왼쪽 귀 좌표
 * @param earR 오른쪽 귀 좌표
 * @param shoulderL 왼쪽 어깨 좌표
 * @param shoulderR 오른쪽 어깨 좌표
 * @param angle_threshold 각도 오차 허용 범위 (기본값: 5도)
 *        → 이 값이 작을수록 정면 판단 기준이 엄격해짐 (권장: 2~10도)
 * @param debug_img 디버깅용 이미지 (라인 시각화용)
 * @return 정면 여부 (true: 정면, false: 비정면)
 */
bool isFrontalByVerticalConsistency(
    Point2f eyeL, Point2f eyeR,
    Point2f earL, Point2f earR,
    Point2f shoulderL, Point2f shoulderR,
    float angle_threshold, Mat& debug_img
) {
    // 각 라인의 수직선 기울기
    float eye_angle = getVerticalAngle(eyeL, eyeR);
    float ear_angle = getVerticalAngle(earL, earR);
    float shoulder_angle = getVerticalAngle(shoulderL, shoulderR);

    // 기울기 차이 계산
    float diff_eye_ear = angleDifference(eye_angle, ear_angle);
    float diff_ear_shoulder = angleDifference(ear_angle, shoulder_angle);
    float diff_eye_shoulder = angleDifference(eye_angle, shoulder_angle);

    // 디버깅용 선 시각화 (색상: 눈-초록, 귀-파랑, 어깨-빨강)
    line(debug_img, eyeL, eyeR, Scalar(0,255,0), 2);
    line(debug_img, earL, earR, Scalar(255,0,0), 2);
    line(debug_img, shoulderL, shoulderR, Scalar(0,0,255), 2);

    // 디버깅 로그 출력
    cout << "[각도차] 눈-귀: " << diff_eye_ear 
         << "\u00b0, 귀-어깨: " << diff_ear_shoulder 
         << "\u00b0, 눈-어깨: " << diff_eye_shoulder << "\u00b0" << endl;

    // 정면 판별 기준 만족 여부 (세 가지 각도 모두 angle_threshold 이하일 경우)
    return (diff_eye_ear <= angle_threshold) &&
           (diff_ear_shoulder <= angle_threshold) &&
           (diff_eye_shoulder <= angle_threshold);
}

// ========================= 테스트 메인 코드 ========================= //

int main() {
    // 테스트 이미지 로드
    Mat img = imread("/home/aa/Big2025/aaatest/static/images/5.jpg");
    if (img.empty()) {
        cerr << "이미지 로드 실패" << endl;
        return -1;
    }

    // 임시 테스트용 좌표 (실제 사용시 keypoint 결과로 대체)
    Point2f eyeL(300, 200), eyeR(400, 200);
    Point2f earL(280, 210), earR(420, 210);
    Point2f shoulderL(260, 300), shoulderR(440, 300);

    // 디버깅용 이미지 복사
    Mat debug_img = img.clone();

    // 조정 가능한 파라미터: 각도 오차 허용 범위
    float angle_threshold = 5.0f; // 단위: degree (범위 권장: 2~10)

    // 정면 여부 판단 실행
    bool frontal = isFrontalByVerticalConsistency(
        eyeL, eyeR, earL, earR, shoulderL, shoulderR,
        angle_threshold, debug_img
    );

    cout << "정면 판별 결과: " << (frontal ? "정면" : "비정면") << endl;

    // 디버깅 이미지 출력
    imshow("검출 시각화", debug_img);
    waitKey(0);

    return 0;
}
