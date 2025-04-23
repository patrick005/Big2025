//ex18_execution.cpp
#include <iostream>
#include <execution> // 병렬처리. cpp 17이후 등장
#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

int main(){
    vector<int> data={1, 2, 3, 4, 5};
    double mean = accumulate(data.begin(), data.end(), 0.0) / data.size();
    double sq_sum =accumulate(data.begin(), data.end(), 0.0, [mean](double acc, int val){
        return acc + (val - mean)*(val - mean);
    });

    double variance = sq_sum / data.size();

    cout << "평균 : " << mean << endl;
    cout << "분산 : " << variance << endl;

    return 0;
}
