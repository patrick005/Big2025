// // #include "color.hpp"
// #include <iostream>
// #include <opencv2/opencv.hpp>

// using namespace std;
// using namespace cv;

// String folderPath = "/home/aa/Big2025/opencv/data/";

// int main()
// {
//     // data
//     String name;
//     int age;
//     Point pt1;
//     vector<int> scores;
//     Mat mat1;

//     String filename = folderPath + "mydata.yml";
//     FileStorage fs;
//     fs.open(filename, FileStorage::READ);
//     fs["name"] >> name;
//     fs["age"] >> age;
//     fs["point"] >> pt1;
//     fs["scores"] >> scores;
//     fs["data"] >> mat1;

//     fs.release();

//     cout << "name : " << name << endl;
//     cout << "age : " << age << endl;
//     cout << "point : " << pt1 << endl;
//     cout << "scores : " << Mat(scores).t() << endl;
//     cout << "data : " << mat1 << endl;

//     return 0;
// }