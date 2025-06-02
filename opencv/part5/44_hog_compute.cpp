#include </home/aa/Big2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/Big2025/opencv/data/";

int main()
{
    Mat img = imread(folderPath + "starfish.jpg", IMREAD_GRAYSCALE);
    vector<Mat> images;
    images.push_back(img);
    Size winSize(64, 128);

    HOGDescriptor hog(
        winSize,
        Size(16, 16),
        Size(8, 8),
        Size(8, 8),
        9);
    cout
        << "WinSize: " << hog.winSize << endl;

    vector<float> descriptors;
    if ((img.cols - hog.winSize.width) % hog.blockStride.width || (img.rows - hog.winSize.height) % hog.blockStride.height)
    {
        resize(img, img, Size(img.cols / hog.blockStride.width * hog.blockStride.width + hog.winSize.width, img.rows / hog.blockStride.height * hog.blockStride.height + hog.winSize.height));
    }
    cout << img.cols % hog.winSize.width << img.rows % hog.winSize.height;
    cout << img.cols << img.rows;
    cout << hog.blockStride.width;
    cout << hog.blockStride.height;

    hog.compute(img, descriptors);

    cout << "Hog 깊이" << descriptors.size() << endl;
    // SVM 학습 -> svm

    // hog.setSVMDetector(descriptors_svm);
    // vector<Rect> starfishes;
    // hog.detectMultiScale(img, starfishes);
    // cout << starfishes.size() << endl;

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

// 이 코드는 OpenCV 라이브러리를 사용하여 이미지에서 HOG(히스토그램 오리엔티드 그래디언트) 특징을 계산하는 예제입니다.
// HOG는 객체 인식 및 이미지 분류에 사용되는 특징 추출 방법입니다.
// 이 코드는 주어진 이미지에서 HOG 특징을 계산하고, 해당 특징의 크기를 출력합니다.
// HOGDescriptor 클래스를 사용하여 HOG 특징을 계산하며, winSize, blockSize, blockStride, cellSize 등의 파라미터를 설정합니다.
// 또한, 이미지의 크기를 HOG 특징 계산에 맞게 조정합니다.