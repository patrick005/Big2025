#include <opencv2/opencv.hpp>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include "color.hpp"

using namespace std;
using namespace cv;

String folderPath = "/home/aa/Big2025/opencv/data/";

int main()
{
    Mat img = imread(folderPath + "lenna.bmp", IMREAD_GRAYSCALE);
    vector<Mat> images;
    images.push_back(img.clone());

    Mat M = Mat_<double>({2, 3}, {1, 0, 150, 0, 1, 100});
    // {1, 0, 150}
    // {0, 1, 100}
    images.emplace_back(Mat()); // 벡터 내부에 바로 생성.
    warpAffine(img, images[1], M, img.size()+Size(150, 100));

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