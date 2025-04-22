//ex3_longest.cpp
// 입력받은 문자열의 내용중 가장 긴 단어의 문자수 출력 및 짧은 단어는 반복문 탈출로 설정한 0 고정;;
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main(){
    cout << "문장을 넣으시오! " << endl;
    string word;
    vector<int> sizes;
    vector<string> sentence;
    while (word != "0"){
        cin >> word;
        sizes.push_back(word.size());
        sentence.push_back(word);
    }
    sort(sizes.begin(), sizes.end()); //정렬
    
    cout << " 가장 짧은 길이는 : " << sizes[0] << endl;
    cout << " 가장 긴 길이는 : " << sizes[sizes.size() - 1] << endl;

    for (auto v : sentence){
        cout << v << " ";
    }
    cout << endl;


    return 0;
}