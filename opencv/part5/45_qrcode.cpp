#include </home/aa/Big2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;
using namespace QRCodeDetector;

String folderPath = "/home/aa/Big2025/opencv/data/";

int main()
{
    VideoCapture cap(folderPath + "vtest.avi");

    String info;
    vector<Point> points;
    Mat img;
    while (true)
    {
        cap >> img;
        if (img.empty())
            break;
        info = qrDetector.detectAndDecode(img, points);
        if (!info.empty())
        {
            polylines(img, points, true, red, 2);
            putText(img, info, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, black);
        }
        imshow("img", img);
        if (waitKey(100) == 27)
            break;
    }
    destroyAllWindows();
    return 0;
}

// 이 코드는 OpenCV 라이브러리를 사용하여 비디오 스트림에서 QR 코드를 감지하고 디코딩하는 기능을 구현합니다.
// QR 코드가 감지되면 해당 QR 코드의 경계선을 이미지에 그려주고, QR 코드의 내용을 화면에 표시합니다.
// QR 코드 감지 및 디코딩을 위해 QRCodeDetector 클래스를 사용하며, 비디오 스트림은 vtest.avi 파일에서 가져옵니다.
// 이 코드는 OpenCV의 QR 코드 감지 및 디코딩 기능을 활용하여 실시간으로 QR 코드를 인식하고, 해당 정보를 화면에 표시하는 예제입니다.