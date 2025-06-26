// frontal_check_with_mpi.cpp
/*
컴파일 명령어:
g++ frontal_check_with_mpi.cpp `pkg-config --cflags --libs opencv4` -o frontal_check_with_mpi

실행 예시:
./frontal_check_with_mpi <image_path>
*/

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
using namespace cv;
using namespace cv::dnn;

// =========================== 파라미터 조정 영역 =========================== //
const float THRESHOLD = 0.1;         // 키포인트 신뢰도 임계값
const float ANGLE_THRESHOLD = 6.0f;  // 수직선 각도 오차 허용값 (권장 범위: 2~10도)
const int N_POINTS = 15;             // MPI 기준 키포인트 수

const vector<pair<int, int>> POSE_PAIRS = {
    {0,1}, {1,2}, {2,3}, {3,4}, {1,5}, {5,6}, {6,7},
    {1,14}, {14,8}, {8,9}, {9,10}, {14,11}, {11,12}, {12,13}
};

// ===================== 정면 여부 판단용 수향후 eye, ear가 검출직선 보조 함수 ===================== //
float getVerticalAngle(Point2f p1, Point2f p2) {
    float angle = atan2(p2.y - p1.y, p2.x - p1.x) * 180 / CV_PI;
    if (angle < 0) angle += 360;
    return angle;
}

float angleDifference(float a1, float a2) {
    float diff = fabs(a1 - a2);
    return min(diff, 360.0f - diff);
}

bool isFrontalVerticalConsistency(
    Point2f eyeL, Point2f eyeR,
    Point2f earL, Point2f earR,
    Point2f shL, Point2f shR,
    float angle_threshold, Mat& dbg
) {
    float eye_angle = getVerticalAngle(eyeL, eyeR);
    float ear_angle = getVerticalAngle(earL, earR);
    float sh_angle = getVerticalAngle(shL, shR);

    float d1 = angleDifference(eye_angle, ear_angle);
    float d2 = angleDifference(ear_angle, sh_angle);
    float d3 = angleDifference(eye_angle, sh_angle);

    cout << "[각도차] 눈-귀: " << d1 << "°, 귀-어깨: " << d2 << "°, 눈-어깨: " << d3 << "°" << endl;

    line(dbg, eyeL, eyeR, Scalar(0,255,0), 2);  // 초록
    line(dbg, earL, earR, Scalar(255,0,0), 2);  // 파랑
    line(dbg, shL, shR, Scalar(0,0,255), 2);    // 빨강

    return (d1 <= angle_threshold) && (d2 <= angle_threshold) && (d3 <= angle_threshold);
}

// =========================== 메인 함수 =========================== //
int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "사용법: ./frontal_check_with_mpi <image_path>" << endl;
        return -1;
    }

    string image_path = argv[1];
    string protoFile = "/home/aa/Big2025/opencv/data/pose_deploy_linevec_faster_4_stages.prototxt";
    string weightsFile = "/home/aa/Big2025/opencv/data/pose_iter_160000.caffemodel";

    Mat img = imread(image_path);
    if (img.empty()) {
        cerr << "이미지 로드 실패: " << image_path << endl;
        return -1;
    }

    Net net = readNetFromCaffe(protoFile, weightsFile);
    net.setPreferableBackend(DNN_BACKEND_DEFAULT);
    net.setPreferableTarget(DNN_TARGET_CPU);

    Mat inputBlob = blobFromImage(img, 1.0/255, Size(368,368), Scalar(0,0,0), false, false);
    net.setInput(inputBlob);
    Mat output = net.forward();

    int H = output.size[2];
    int W = output.size[3];

    vector<Point2f> points(N_POINTS, Point2f(-1, -1));
    for (int n = 0; n < N_POINTS; n++) {
        Mat probMap(H, W, CV_32F, output.ptr(0,n));
        Point2f p(-1, -1);
        Point maxLoc;
        double prob;
        minMaxLoc(probMap, 0, &prob, 0, &maxLoc);
        if (prob > THRESHOLD) {
            p.x = maxLoc.x * img.cols / (float)W;
            p.y = maxLoc.y * img.rows / (float)H;
        }
        points[n] = p;
    }

    Mat debug_img = img.clone();
    for (const auto& pr : POSE_PAIRS) {
        Point2f pa = points[pr.first];
        Point2f pb = points[pr.second];
        if (pa.x > 0 && pb.x > 0)
            line(debug_img, pa, pb, Scalar(100, 255, 255), 2);
    }

    // 어깨 (2, 5), 귀 (없음), 눈 (없음) → 후처리 가능성 열어둠
    bool has_eye = false, has_ear = false, has_shoulder = false;
    Point2f eyeL, eyeR, earL, earR, shL, shR;

    // 눈 (keypoint ID 미정 — 추후 확장 필요 시 대응)
    if (false) {} // eyeL, eyeR = points[15], points[16]; → MPI 미지원

    // 귀는 따로 없으므로 생략 (or 향후 유추 예정)
    if (false) {}

    // 어깨
    if (points[2].x > 0 && points[5].x > 0) {
        shL = points[2]; shR = points[5];
        has_shoulder = true;
        line(debug_img, shL, shR, Scalar(0,0,255), 2); // 빨강
    }

    // 로그 출력
    if (!has_shoulder)
        cout << "어깨 keypoint 미검출: 수평선 생성 불가" << endl;
    else
        cout << "어깨 라인 생성 완료" << endl;

    imshow("디버깅 결과", debug_img);
    waitKey(0);
    return 0;
}

