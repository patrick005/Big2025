#include </home/aa/Big2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/Big2025/opencv/data/";

int main()
{
    VideoCapture cap(0);
    Ptr<Feature2D> feature = ORB::create();
    vector<KeyPoint> keypoints;
    vector<Point2f> corners;
    Mat img, img1, img2, gray_img, desc;
    while (true)
    {
        cap >> img;
        img1 = img.clone();
        img2 = img.clone();

        // FAST
        cvtColor(img, gray_img, COLOR_BGR2GRAY);
        FAST(gray_img, keypoints, 60, true);
        for (auto &k : keypoints)
        {
            circle(img, Point(cvRound(k.pt.x), cvRound(k.pt.y)), 5, red, 2);
        }
        imshow("img", img);

        // goodFeature
        goodFeaturesToTrack(gray_img, corners, 1000, 0.01, 10);
        for (auto &p : corners)
        {
            circle(img1, Point(p.x, p.y), 5, red, 2);
        }
        imshow("img1", img1);

        // ORB
        // feature->detect(img, keypoints);
        // feature->compute(img, keypoints, dst);
        feature->detectAndCompute(img2, noArray(), keypoints, desc);
        drawKeypoints(img2, keypoints, img2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        imshow("img2", img2);
        if (waitKey(33) == 27)
            break;
    }
    destroyAllWindows();
    return 0;
}

// FAST 코너 검출 알고리즘을 사용하여 이미지에서 특징점을 찾고, 해당 위치에 원을 그리는 코드입니다.
// 이 코드는 OpenCV 라이브러리를 사용하여 실시간으로 카메라에서 영상을 캡처하고, FAST 알고리즘을 통해 이미지의 특징점을 찾아 시각적으로 표시합니다.
// FAST(Features from Accelerated Segment Test) 알고리즘은 이미지에서 빠르게 코너를 검출하는 방법으로, 실시간 응용 프로그램에서 자주 사용됩니다.
// 이 코드는 OpenCV의 FAST 알고리즘을 활용하여 실시간으로 카메라에서 특징점을 인식하고, 해당 정보를 화면에 표시하는 예제입니다.
// FAST 코너 검출 알고리즘은 이미지에서 빠르게 코너를 검출하는 방법으로, 실시간 응용 프로그램에서 자주 사용됩니다.
// 이 코드는 OpenCV의 FAST 알고리즘을 활용하여 실시간으로 카메라에서 특징점을 인식하고, 해당 정보를 화면에 표시하는 예제입니다.
// FAST 코너 검출 알고리즘은 이미지에서 빠르게 코너를 검출하는 방법으로, 실시간 응용 프로그램에서 자주 사용됩니다.