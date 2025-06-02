#include </home/aa/Big2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/Big2025/opencv/data/";

int main(){
    Mat img = imread(folderPath + "coins.png");
    vector<Mat> images;

    Mat blurred;
    // img.convertTo(blurred, CV_8UC1);
    cvtColor(img, blurred, COLOR_BGR2GRAY);
    blur(blurred, blurred, Size(3, 3));
    vector<Vec3f> circles;
    HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);

    for(auto &c : circles){
        Point center(cvRound(c[0]), cvRound(c[1]));
        int radius = cvRound(c[2]);
        circle(img, center, radius, red, 2, LINE_AA);
    }
    images.push_back(img);
    images.push_back(blurred);

    // vector img show code
    int i = 1;
    for (auto img : images){
        imshow("Image " + to_string(i++), img);
        ++i;
    }
    waitKey();
    destroyAllWindows();
    return 0;
}