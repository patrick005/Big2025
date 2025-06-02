#include </home/aa/Big2025/opencv/part2/color.hpp>
#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/Big2025/opencv/data/";

int main()
{
    // Mat img = imread(folderPath + "lenna.bmp", IMREAD_GRAYSCALE);
    VideoCapture cap(0);

    Mat img, edge;
    int low_v, high_v;
    namedWindow("img1");
    createTrackbar("lowedge", "img1", &low_v, 255);
    createTrackbar("highedge", "img1", &high_v, 255);
    // Canny(img, edge, low_v, high_v);
    // images.push_back(edge);

    // vector img show code
    while(true){
        cap >> img;
        Canny(img, edge, low_v, high_v);
        imshow("img1", edge);
        if(waitKey(1) == 27) // ESC key to exit
            break;
    }
    destroyAllWindows();
    return 0;
}