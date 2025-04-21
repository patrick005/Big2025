#include <iostream>
#include "complex.h"
#include "safeArray.h"

int main()
{
    int nums1[] = {1, 2, 3, 4, 5};
    Array<int> arr1 (nums1, 5);
    

    for (int i = 0; i < arr1.size(); ++i){
        std::cout << arr1[i] << std::endl;
    }

    double nums2[] = { 1.1, 2.2, 3.3, 4.4, 5.5};
    Array<double> arr2 (nums2, 5);

    for (int i = 0; i < arr2.size(); ++i){
        std::cout << arr2[i] << std::endl;
    }
    
    Complex nums3[] = {Complex(3.0, 4.0), Complex(3.0), Complex(), Complex(), Complex(3.0, 4.0)};
    Array<Complex> arr3(nums3, 5);

    for (int i = 0; i < arr3.size(); ++i){
        std::cout << arr3[i] << std::endl;
    }

    // SafeArray nums4[] = {SafeArray(3.0, 4.0), SafeArray(3.0), SafeArray(), SafeArray(), SafeArray(3.0, 4.0)};
    // Array<SafeArray> arr4(nums4, 5);

    // for (int i = 0; i < arr4.size(); ++i){
    //     std::cout << arr4[i] << std::endl;
    // }

    return 0;
}

/*
/cpp/array2$   g++ -c main.cpp
/cpp/array2$   g++ -o test main.o complex.o
/cpp/array2$   ./test
*/