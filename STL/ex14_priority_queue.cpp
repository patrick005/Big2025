//ex14_priority_queue.cpp
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Task{
public:
    string name;
    int priority;

    // other 말고 rhs 사용하기도 함 rhs, lhs, other 등등
    bool operator<(const Task& other) const{
        return priority < other.priority; // 내림차순
    }
};

int main(){
    priority_queue<Task> scheduler;

    scheduler.push({"Write report", 2}); // name, priority로 들어감
    scheduler.push({"Fix bug", 3});
    scheduler.push({"Email team", 1});

    cout << "작업 처리 순서" << endl;
    while (!scheduler.empty()){
        Task t = scheduler.top();
        scheduler.pop();
        cout << t.name << "우선순위" << t.priority << endl;
    }
    

    return 0;
}

/*기존 queue에 순서를 맞춰 넣어둠으로써 뺄때 오름차순이나 내림차순으로 출력

priority_queue는 입력 시에 힙 자료 구조를 이용하여
우선순위에 따라 내부적으로 순서를 유지하며 데이터를 저장합니다.
따라서 pop() 연산을 수행할 때마다 항상 가장 높은 우선순위의 요소가 나오게 되는 것입니다.
내부적으로 if문과 같은 조건부 비교 및 스왑 연산이 힙 구조를 유지하는 데 사용되지만,
이는 단순히 출력 시에만 순서를 맞추는 것이 아니라 데이터가 저장되는 방식 자체입니다.



*/