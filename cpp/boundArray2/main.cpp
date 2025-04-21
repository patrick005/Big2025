#include <iostream>
#include "boundArray.h"

int main(){

    BoundArray<int> arr1(1, 11);
    for (int i = arr1.lower(); i != arr1.upper(); ++i)
    {
        arr1[i] = i;    // 값 할당
    }
    for (int i = arr1.lower(); i != arr1.upper(); ++i)
    {
        std::cout << i << " : " << arr1[i] << std::endl; // 값 출력
    }
    






    BoundArray<double> arr2(5, 11);
    for (int i = arr1.lower(); i != arr1.upper(); ++i)
    {
        arr2[i] = i; // 값 할당
    }
    for (int i = arr2.lower(); i != arr2.upper(); ++i)
    {
        std::cout << i << " : " << arr2[i] << std::endl; // 값 출력
    }



    return 0;
}
