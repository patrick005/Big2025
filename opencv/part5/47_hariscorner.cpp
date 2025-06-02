#include <opencv2/opencv.hpp>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include </home/aa/Big2025/opencv/part2/color.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/Big2025/opencv/data/";

int main()
{
    Mat img = imread(folderPath + "building.jpg", IMREAD_GRAYSCALE);
    vector<Mat> images;
    images.push_back(img);
    Mat harris, harris_norm;
    cornerHarris(img, harris, 3, 3, 0.04);
    cout << harris.type() << endl;
    normalize(harris, harris_norm, 0, 255, NORM_MINMAX, CV_8U);
    images.push_back(harris_norm);
    for(int j = 1; j< harris.rows - 1; ++j){
        for(int i = 1; i < harris.cols - 1; ++i){
            if(harris_norm.at<uchar>(j, i) > 120){
                circle(img, Point(i, j), 5, white, 2);
            }
        }   
    }

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

// 꼭짓점 검출을 위한 Harris 코너 검출 알고리즘을 사용하여 이미지에서 특징점을 찾고, 해당 위치에 원을 그리는 코드입니다.
// 이 코드는 OpenCV 라이브러리를 사용하여 이미지를 처리하고, Harris 코너 검출을 통해 이미지의 특징점을 찾아 시각적으로 표시합니다.