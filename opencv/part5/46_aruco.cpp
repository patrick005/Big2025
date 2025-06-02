#include "opencv2/aruco.hpp"
#include </home/aa/Big2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;
String folderPath = "/home/aa/Big2025/opencv/data/";

int main()
{
    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);
    VideoCapture cap(0);

    vector<int> markerIds;
    vector<Vec3d> rvecs, tvecs;
    vector<vector<Point2f>> markerCorners;
    Mat cameraMatrix = (Mat_<double>(3,3) << 1000, 0, 640, 0, 1000, 360, 0, 0, 1);
    Mat disCoeffs = (Mat_<double>(5,1) << 0, 0, 0, 0, 0);



    Mat img;
    while (true)
    {
        cap >> img;
        if (img.empty())
            break;
        aruco::detectMarkers(img, dictionary, markerCorners, markerIds);

        aruco::drawDetectedMarkers(img, markerCorners, markerIds);

        aruco::estimatePoseSingleMarkers(markerCorners, 0.05, cameraMatrix, disCoeffs, rvecs, tvecs);
        
        for (int i = 0; i < markerIds.size(); i++)
        {
            cout << rvecs[i][0] <<  rvecs[i][1] << rvecs[i][2] <<endl;
            cout << tvecs[i][0] <<  tvecs[i][1] << tvecs[i][2] <<endl;
            cv::drawFrameAxes(img, cameraMatrix, disCoeffs, rvecs[i], tvecs[i], 0.1);
        }
        // cv::drawFrameAxes(img, cameraMatrix, disCoeffs, rvecs[0], tvecs[0], 0.1, 2);
        // cv::drawFrameAxes(img, cameraMatrix, disCoeffs, rvecs[1], tvecs[1], 0.1, 2);
        // cv::drawFrameAxes(img, cameraMatrix, disCoeffs, rvecs[2], tvecs[2], 0.1, 2);

        imshow("img", img);
        if (waitKey(100) == 27)
            break;
    }
    destroyAllWindows();
    return 0;
}


// 이 코드는 OpenCV 라이브러리를 사용하여 카메라로부터 입력된 이미지에서 ArUco 마커를 감지하고, 해당 마커의 위치와 방향을 추정하는 기능을 구현합니다.
// ArUco 마커는 컴퓨터 비전에서 객체 인식 및 추적에 사용되는 2D 바코드입니다.
// 이 코드는 ArUco 라이브러리를 사용하여 마커를 감지하고, 각 마커의 회전 벡터와 이동 벡터를 추정합니다.
// 또한, 추정된 회전 벡터와 이동 벡터를 사용하여 이미지에 3D 좌표계를 그려줍니다.
// 이 코드는 OpenCV의 ArUco 모듈을 활용하여 실시간으로 ArUco 마커를 인식하고, 해당 마커의 위치와 방향을 추정하는 예제입니다.