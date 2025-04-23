//ex15_unordered_map.cpp
// 표준 입력을 받아서 (영어문장) -this is a apple.
// 단어별 등장 횟수를 카운트 해주는 코드
#include <iostream>
#include <sstream>      //string-stream
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

string clean_word(const string& word){
    string cleaned;
    for (char ch : word){
        if(isalpha(ch) || isdigit(ch)){ // 알파벳이나 숫자
            cleaned += tolower(ch); // 대문자를 소문자화
        }
    }
    return cleaned;
}

int main(){
    cout  << " 문장을 입력하시오 " << endl;

    string line;
    getline(cin, line);

    unordered_map<string, int> word_count; // <1> 여기서 타입 지정(단어(string)를 키로 하고 등장 횟수(int)를 값으로 저장할 맵을 생성)
    istringstream iss(line);            //입력받은 문자열 line을 공백을 기준으로 단어별로 분리할 수 있는 입력 스트림 객체 iss를 생성
    string word;

    while (iss >> word){ //입력 스트림에서 단어(word)를 하나씩 추출
        string cleaned = clean_word(word); // 위에서 만든 함수를 이용
        if(!cleaned.empty()){
            word_count[cleaned]++; // word_count[key] = value를 쓰는게 정상적이지만 <1>에서 증감을 주는걸로 처리
            // unordered_map에서 cleaned 단어를 키로 찾아 해당하는 값(횟수)을 1 증가
            // 만약 cleaned 단어가 처음 등장한 경우, 키가 새로 생성되고 값은 1로 초기화
        }
    }
    for (const auto &[key, value] : word_count){
        cout << key << " : " << value << endl;
    }
    
    return 0;
}