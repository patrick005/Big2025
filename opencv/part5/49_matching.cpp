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

    Mat book = imread(folderPath + "1690266939270.jpg");
    Mat book_gray, desc1, desc2;
    cvtColor(book, book_gray, COLOR_BGR2GRAY);

    // 변수 준비
    Ptr<Feature2D> feature = ORB::create();
    Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);
    vector<KeyPoint> keypoints1, keypoints2;
    vector<DMatch> matches;

    // book 조사
    feature->detectAndCompute(book_gray, Mat(), keypoints1, desc1);

    Mat img, img_gray, dst;
    while (true)
    {
        cap >> img;
        cvtColor(img, img_gray, COLOR_BGR2GRAY);
        feature->detectAndCompute(img_gray, Mat(), keypoints2, desc2);
        matcher->match(desc1, desc2, matches); // 매칭 수행

        sort(matches.begin(), matches.end());
        vector<DMatch> good_matches(matches.begin(), matches.begin() + 50);
        drawMatches(book, keypoints1, img, keypoints2, good_matches, dst, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

        imshow("dst", dst);
        if (waitKey(33) == 27)
            break;
    }
    destroyAllWindows();
    return 0;
}