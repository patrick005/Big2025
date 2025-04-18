//이는 손자 파일임
// Array->safeArray->boundArray.main.cpp
#include <iostream>
#include "boundArray.h"

int main(){

    BoundArray arr1(1, 11);     //index : [1:11)
    BoundArray arr2(10);        //index : [0:10)
    BoundArray arr3;            //index : [0:100) -> 할아버지에 defaultsize 명시 되어있음

    for (int i = arr1.lower(); i != arr1.upper(); ++i){
        arr1[i] = i;
    }
    
    arr3 = arr1;
    arr3 == arr1;
    
    const BoundArray arr4 = arr1;

    for (int i = arr4.lower(); i != arr4.upper(); ++i){
        std::cout << arr4[i] << std::endl;
    }

    std::cout << "arr2 test" << std::endl;
    for (int i = arr2.lower(); i != arr2.upper(); ++i){
        std::cout << arr2[i] << std::endl;
    }
    return 0;

}