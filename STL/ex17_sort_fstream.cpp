//ex17_sort_fstream.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Student{
public:
    string name;
    int sub1;
    int sub2;
    int sub3;
    int sub4;
    int sub5;

    int totalScore() const {
        return sub1 + sub2 + sub3 + sub4 + sub5;
    }
    void print() const{
        cout << "이름 : " << name << endl;
        cout << "점수 : " << sub1 << " " << sub2 << " " << sub3 << " " << sub4 << " " << sub5 << endl;
        cout << "총점 : " << totalScore() << endl;
        cout << "---------------------------------" << endl;
    }
};
int main(){
    ifstream file("/home/aa/Big2025/STL/10.txt");
    vector<Student> students;

    string name;
    int s1, s2, s3, s4, s5;

    while (file >> name >> s1 >> s2 >> s3 >> s4 >> s5){
        students.push_back({name, s1, s2, s3, s4, s5});

    }
    file.close();
    for (const auto & student : students){
        cout << student.name << " ";
    }
    cout << endl;
    
    sort(students.begin(), students.end(), [](const Student &a, const Student &b){return a.totalScore() < b.totalScore();});
    for (const auto & student : students){
        student.print();
    }

return 0;
}