#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include </home/aa/Big2025/opencv/part2/color.hpp>
#include <opencv2/ml.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

String folderPath = "/home/aa/Big2025/opencv/data/";

int main(){
    vector<float> x_data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    vector<float> y_data;
    
    for(auto &x : x_data){
            y_data.push_back(2.f * x + 1.f);
    }

    Mat samples(x_data.size(), 1, CV_32F);
    Mat response(y_data.size(), 1, CV_32F);
    for(size_t i = 0; i < x_data.size(); ++i){
        samples.at<float>(i, 0) = x_data[i];
        response.at<float>(i, 0) = y_data[i];
    }

    Ptr<TrainData> tData = TrainData::create(samples, ROW_SAMPLE, response);
//=================================보통 여기 함수화로 묶어서 프레딕트에 박음==================================
    // 값 초기화
    Mat X = Mat(samples.rows, 2, CV_32F);
    for(int i = 0; i< samples.rows; i++){
        X.at<float>(i, 0) = samples.at<float>(i, 0);
        X.at<float>(i, 1) = 1.0f; 
    }
    // train
    Mat XtX = X.t() * X;
    Mat XtX_inv;
    invert(XtX, XtX_inv, DECOMP_SVD);
    Mat weights = XtX_inv * X.t() * response;
    cout << "기울기 weight" << weights.at<float>(0,0) << endl;
    cout << "절편 bias " << weights.at<float>(1,0) << endl;
//========================================================================================================
    // 예측
    float test_X = 15.0f;
    float predicted_y = weights.at<float>(0,0) * test_X + weights.at<float>(1,0);
    cout << "15.0f 예측된 y 값: " << predicted_y << endl;


    return 0;
}

// 