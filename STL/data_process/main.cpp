//main.cpp
#include "data_process.hpp"
#include <iostream>

using namespace std;

int main(){
    vector<string> words = {"apple", "ant", "banana", "bear", "cat"};
    DataProcessor processor(words);


    auto sorted = processor.sort_by_length();
    cout << "original sequence : " << endl;
    for(const auto& word : processor.data_){
        cout << word << endl;
    }
    cout << "sorted by length : " << endl;
    for(const auto& word : sorted){
        cout << word << endl;
    }

    //filtering
    cout << "Filtered by prefix : " << endl;
    auto filtered = processor.filter_by_prefix("b");
    for (const auto &word : filtered){
        cout << word << endl;
    }

    // capture mutable 사용
    int min_length = 4;
    auto count_long = [=]() mutable { //외부 데이터를 내부에서 편집할 수 있도록 mutable 사용함
        int count = 0;
        for (const auto &word : words){
            if (word.length() >= min_length){
                count++;
            }
        }
        min_length++; //->이줄이 mutable의 수혜자 
        cout << "min_length" << min_length << endl;
        return count;
    };
    cout << "words with length >= 4" << "\n" << count_long() << endl;
    cout << "After mutable change, min_length : " << min_length << endl;

    return 0;
}


/*
외부 데이터에 대한 변형이 불가하지만
mutable을 활용한 외부에서 가져온 데이터에 대한 변형 시도를 보여주는 코드 작성

*/