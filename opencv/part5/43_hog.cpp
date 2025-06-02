#include </home/aa/Big2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/Big2025/opencv/data/";

int main()
{
    VideoCapture cap(folderPath + "vtest.avi");

    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

    vector<Rect> people;
    Mat img;
    while (true)
    {
        cap >> img;
        if (img.empty())
            break;
        hog.detectMultiScale(img, people);
        for (auto &rect : people)
        {
            rectangle(img, rect, red);
        }
        imshow("img", img);
        if (waitKey(100) == 27)
            break;
    }
    destroyAllWindows();
    return 0;
}


//
// 이 코드는 OpenCV 라이브러리를 사용하여 비디오 스트림에서 사람을 감지하는 기능을 구현합니다.
// HOGDescriptor를 사용하여 사람 감지 모델을 설정하고, 비디오 프레임에서 사람을 감지하여 해당 영역에 사각형을 그립니다.
// 비디오 스트림은 vtest.avi 파일에서 가져오며, 감지된 사람의 위치를 빨간색 사각형으로 표시합니다.
// 이 코드는 OpenCV의 HOGDescriptor를 활용하여 실시간으로 사람을 인식하고, 해당 정보를 화면에 표시하는 예제입니다.