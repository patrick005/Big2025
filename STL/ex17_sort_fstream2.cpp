//ex17_sort_fstream2.cpp --> 캡슐화 및 정보 은닉
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <sstream>
using namespace std;

class Student{
private:
    string name_;
    vector<int> scores_;

public:
    Student(const string&name, const vector<int> scores) : name_(name), scores_(scores){
    }
    int totalScore() const {
        return accumulate(scores_.begin(), scores_.end(), 0);
    }
    int averageScore() const{
        return totalScore() / scores_.size();
    }
    void print() const{
        cout << "이름 : " << name_ << endl;
        cout << "점수 : " ;
        for (const auto &v : scores_){
            cout << v << " ";
        }
        cout << "총점 : " << totalScore() << endl;
        cout << "총점 : " << averageScore() << endl;
        cout << "-----------------------------------------" << endl;
    }
};
int main(){
    ifstream file("/home/aa/Big2025/STL/10.txt");
    vector<Student> students;

    string line, name;
    vector<int> scores;
    int score;

    while (getline(file, line)){
        istringstream iss(line);
        iss >> name;
        while (iss >> score){
            scores.push_back(score);
        }
        students.emplace_back(name, scores);
        scores.clear();
    }
    file.close();

    sort(students.begin(), students.end(), [](const Student &a, const Student &b){
        return a.averageScore() < b.averageScore(); });

    //파티션 partition
    auto fail_bound = partition(students.begin(), students.end(), [](const Student& st){
        return st.averageScore() < 60;
    });
    cout << (*fail_bound).averageScore() << endl;
    vector<Student> fail_students(students.begin(), fail_bound);
    vector<Student> success_students(fail_bound, students.end());
    cout << "============합격============" << endl;
    for (const auto &student : success_students){
        student.print();
    }
    cout << "============불합격============" << endl;
    for (const auto &student : fail_students){
        student.print();
    }
return 0;
}