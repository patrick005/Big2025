// pose_crop.cpp
/*
g++ pose_crop.cpp -o pose_crop \
    `pkg-config --cflags --libs opencv4` \
    -std=c++11
*/
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;
using namespace cv::dnn;

const int POSE_PAIRS[14][2] = {
    {0,1}, {1,2}, {2,3},
    {3,4}, {1,5}, {5,6},
    {6,7}, {1,14}, {14,8}, {8,9},
    {9,10}, {14,11}, {11,12}, {12,13}
};

string folderPath = "/home/aa/Big2025/aaatest/";
string protoFile = folderPath + "model/pose_deploy_linevec_faster_4_stages.prototxt";
string weightsFile = folderPath + "model/pose_iter_160000.caffemodel";
int nPoints = 15;
float thresh = 0.1;

int main(int argc, char **argv) {
    if (argc < 3) {
        cerr << "USAGE: ./pose_crop <image_path> <output_result_path>" << endl;
        return -1;
    }

    string imagePath = argv[1];
    string resultPath = argv[2];

    Mat frame = imread(imagePath);
    if (frame.empty()) {
        cerr << "이미지를 불러올 수 없습니다." << endl;
        return -1;
    }

    Net net = readNetFromCaffe(protoFile, weightsFile);
    net.setPreferableBackend(DNN_BACKEND_OPENCV);
    net.setPreferableTarget(DNN_TARGET_CPU);

    int inWidth = 368, inHeight = 368;
    Mat inpBlob = blobFromImage(frame, 1.0 / 255, Size(inWidth, inHeight), Scalar(0,0,0), false, false);
    net.setInput(inpBlob);
    Mat output = net.forward();

    int H = output.size[2];
    int W = output.size[3];

    vector<Point> points(nPoints);
    for (int n = 0; n < nPoints; n++) {
        Mat probMap(H, W, CV_32F, output.ptr(0,n));
        Point maxLoc;
        double prob;
        minMaxLoc(probMap, 0, &prob, 0, &maxLoc);

        if (prob > thresh) {
            int x = int((float)frame.cols * maxLoc.x / W);
            int y = int((float)frame.rows * maxLoc.y / H);
            points[n] = Point(x, y);
        } else {
            points[n] = Point(-1, -1);
        }
        if (points[14].x > 0 && points[14].y > 0) {
        points[14].y += 20;  // chest y 위치를 아래로 20px 이동
}
    }

    // 기준: chest = 14
    Point chest = points[14];

    if (chest.x < 0 || chest.y < 0) {
        ofstream fout(resultPath);
        fout << "FAIL chest_not_detected" << endl;
        fout.close();
        return 0;
    }

    // 아래 keypoint (hip~ankle) 존재 여부 판단
    bool hasLower = false;
    for (int k : {8, 9, 10, 11, 12, 13}) {
        if (points[k].x >= 0 && points[k].y >= 0 && points[k].y > chest.y) {
            hasLower = true;
            break;
        }
    }

    if (hasLower) {
        Mat cropped = frame(Rect(0, 0, frame.cols, chest.y));
        imwrite("cropped_result.jpg", cropped);
        ofstream fout(resultPath);
        fout << "CROPPED cropped_result.jpg" << endl;
        fout.close();
    } else {
        ofstream fout(resultPath);
        fout << "UPPER torso_detected" << endl;
        fout.close();
    }

    return 0;
}
