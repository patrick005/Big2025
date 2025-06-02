#include </home/aa/Big2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/Big2025/opencv/data/";

int main()
{
    Mat img = imread(folderPath + "kids.png");
    vector<Mat> images;
    images.push_back(img);
    images.emplace_back(img.clone());

    CascadeClassifier classifier(folderPath + "haarcascade_frontalface_default.xml");

    vector<Rect> faces;
    classifier.detectMultiScale(img, faces);

    for (auto &rect : faces)
    {
        rectangle(img, rect, red, 2);
    }
    // vector img show 코드
    int i = 1;
    for (auto img : images)
    {
        imshow("img" + to_string(i), img);
        ++i;
    }

    waitKey();
    destroyAllWindows();
    return 0;
}

// 이 코드는 OpenCV 라이브러리를 사용하여 이미지에서 얼굴을 감지하는 기능을 구현합니다.
// Haar Cascade 분류기를 사용하여 얼굴을 감지하고, 감지된 얼굴 영역에 빨간색 사각형을 그립니다.
// 이미지 파일은 kids.png이며, haarcascade_frontalface_default.xml 파일을 사용하여 얼굴 감지 모델을 로드합니다.
// 이 코드는 OpenCV의 Haar Cascade 분류기를 활용하여 이미지에서 얼굴을 인식하고, 해당 정보를 시각적으로 표시하는 예제입니다.
// Haar Cascade 분류기는 OpenCV에서 제공하는 사전 학습된 얼굴 감지 모델로, 이미지에서 얼굴을 빠르게 감지할 수 있습니다.