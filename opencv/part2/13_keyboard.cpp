#include "color.hpp"
#include <iostream>
// #include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/Big2025/opencv/data/";

int main()
{
    Mat img = imread(folderPath + "lenna.bmp");
    namedWindow("img");
    auto i = getTickCount();
    int keycode;
    while (true)
    {
        keycode = waitKey(10);
        cout << "keycode: " << keycode << endl;
        cout << "i: " << i << endl;
        cout << "fps: " << getTickFrequency() / (getTickCount() - i) << endl;

        if (keycode == 'v' || keycode == 'V')
        {
            img = ~img;
        }
        if (keycode == 'a' || keycode == 'A')
        {
            img = img + 10;
        }
        if (keycode == 'd' || keycode == 'D')
        {
            img = img - 10;
        }
        imshow("img", img);
        if (keycode == 27)
            break;
        i = getTickCount();
    }
    destroyAllWindows();
    return 0;
}