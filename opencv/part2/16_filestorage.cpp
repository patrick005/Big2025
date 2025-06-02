#include "array.h"
#include "color.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/Big2025/opencv/data/";

int main()
{
    // data
    String name = "patrick";
    int age = 10;
    Point pt1(100, 200);
    vector<int> scores = {80, 90, 50};
    Mat mat1 = (Mat_<float>(2, 2) << 1.0f, 1.5f, 2.0f, 3.2f);
    Array array(10);

    String filename = folderPath + "mydata.yml";
    FileStorage fs;
    fs.open(filename, FileStorage::WRITE);
    fs << "name" << name;
    fs << "age" << age;
    fs << "point" << pt1;
    fs << "scores" << scores;
    fs << "data" << mat1;
    // fs << "array" << array; // 빌드 통과 못함!

    fs.release();

    return 0;
}