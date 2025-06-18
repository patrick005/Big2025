// 60_google_vision.cpp
// Google Vision API를 사용하여 이미지 분석을 수행하는 코드입니다.
#include "opencv2/opencv.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using namespace cv;
using namespace cv::dnn;
using namespace std;

String folderPath = "/home/aa/Big2025/opencv/part7/";

int main(){
    // 이미지 파일 목록
    vector<String> files;
    files.push_back("beagle.jpg");
    files.push_back("cup.jpg");
    files.push_back("pineapple.jpg");
    files.push_back("scooter.jpg");
    files.push_back("space_shuttle.jpg");

    vector<Mat> imgs;
    for (auto &f : files)
        imgs.push_back(imread(folderPath + f));

    // 모델 로드
    Net net = readNet(
        "/home/aa/Big2025/opencv/part7/bvlc_googlenet.caffemodel",
        "/home/aa/Big2025/opencv/part7/deploy.prototxt");

    ifstream fp(folderPath + "classification_classes_ILSVRC2012.txt");

    // 클래스 정보 로드
    vector<String> classNames;
    String name;
    while(!fp.eof()){
        getline(fp, name);
        if(name.length())
            classNames.push_back(name);
    }

    for(auto &img : imgs){
        Mat inputBlob = blobFromImage(img, 1, Size(224, 224), Scalar(104, 117, 123)); // 적합화: BGR -> RGB, 평균값 제거
        net.setInput(inputBlob, "data"); // 입력 레이어 설정
        Mat prob = net.forward("prob"); // 실제 연산라인

        double maxVal;
        Point maxLoc;
        // 결과에서 가장 높은 확률을 가진 클래스 찾기
        minMaxLoc(prob, NULL, &maxVal, NULL, &maxLoc); // 최소값 null처리
        String str = format("%s (%4.21f%%)", classNames[maxLoc.x].c_str(), maxVal * 100);
        putText(img, str, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 255, 0), 2);
        imshow("img", img);
        if (waitKey(0) == 27) { // ESC 키로 종료
            break;
        }

    }

    return 0;
}