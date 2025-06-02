#include </home/aa/kuBig2025/opencv/part2/color.hpp>
#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/kuBig2025/opencv/data/";

int main()
{
    Mat img = imread(folderPath + "hawkes.bmp", IMREAD_GRAYSCALE);
    namedWindow("img");
    Mat img2 = img + 100; // bright
    Mat img3 = 2.f * img; // contrast 대조
    Mat img4 = img + (img - 128) * 1.f;

    double min, max;
    minMaxLoc(img, &min, &max);

    Mat img5 = (img - min) * 255 / (max - min); // stretching

    Mat img6;
    equalizeHist(img, img6); // 히스토 평활화!

    imshow("img", img);
    imshow("img2", img2);
    imshow("img3", img3);
    imshow("img4", img4);
    imshow("img5", img5);
    imshow("img6", img6);
    waitKey();
    destroyAllWindows();
    return 0;
}