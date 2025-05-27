// 01_hellowWorld.cpp
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/Big2025/opencv/data/";

int main(){

    cout << "hello, world" << endl;

    Mat img = imread(folderPath + "lenna.bmp");

    // cout << img << endl;

    imshow("lenna", img);
    waitKey();

    return 0;
}