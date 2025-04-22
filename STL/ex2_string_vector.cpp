// ex2_string_vector.cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;
// using std::cout; // 엄격히 쓰는 방법
// using std::endl; // 엄격히 쓰는 방법


int main(){
    vector<string> sv;
    string name;

    cout << "이름을 5개 입력 하시오! " << endl;

    for (int i = 0; i < 5; i++){
        cout << i + 1 << " >> ";
        getline(cin, name); //scanf
        sv.push_back(name); // scanned data saving on stack
    }
    name = sv.at(0);
    for (int i = 0; i < sv.size(); i++){
        if (name < sv[i]){ // string에 비교연산자 -> overriding이 되어있기에 가능 -> 철자순으로 비교를 함
            name = sv[i];
        }
    }
    cout << "사전에서 가장 뒤에 나오는 이름은 " << name << endl;



    return 0;
}











