//ex7_map.cpp
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(){
    map<string, string> dic={{"power", "힘"}, {"money", "힘"}};

    dic.insert(make_pair("love", "사랑"));
    dic["cherry"] = "체리";

    dic.erase("money");

    cout << "저장된 단어 개수" << dic.size() << endl;
    string eng;
    while (true){
        cout << "찾고 싶은 단어>> ";
        getline(cin, eng);
        if (eng == "exit"){
            break;
        }
        if (dic.find(eng) == dic.end()){
            cout << "없음" << endl;
        }else{
            cout << dic[eng] << endl;
        }
    }

    for(const auto& [eng, kor] : dic){
        std::cout << "영어 : " << eng << " | 한글 : " << kor << endl;
    }

    cout << "종료합니다" << endl;
    return 0;
}