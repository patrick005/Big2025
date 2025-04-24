//ex8_treeSmart.cpp


#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct TreeNode{
    int value;
    vector<shared_ptr<TreeNode>> children;
    TreeNode(int val) : value(val) {}
};

void printTree(const shared_ptr<TreeNode>& node, int depth = 0){
    if(!node){
        return;
    }
    cout << string(depth*2, '\t') << node->value << endl;
    for (const auto& child : node->children){
        printTree(child, depth + 1);
    }
    
}

int main(){
    auto root = make_shared<TreeNode>(1);
    root->children.push_back(make_shared<TreeNode>(2));
    root->children.push_back(make_shared<TreeNode>(3));
    root->children.push_back(make_shared<TreeNode>(4));
    root->children[0]->children.push_back(make_shared<TreeNode>(5));
    
    printTree(root);
    return 0;
}


/*

* `auto root = make_shared<TreeNode>(1);`: 값 1을 가지는 루트 노드를 `shared_ptr`로 생성합니다. 이제 `root`는 루트 노드를 가리키는 스마트 포인터입니다.
* `root->children.push_back(make_shared<TreeNode>(2));`: 루트 노드의 자식으로 값 2를 가지는 새로운 노드를 `shared_ptr`로 생성하여 추가합니다.
* `root->children.push_back(make_shared<TreeNode>(3));`: 루트 노드의 자식으로 값 3을 가지는 새로운 노드를 `shared_ptr`로 생성하여 추가합니다.
* `root->children.push_back(make_shared<TreeNode>(4));`: 루트 노드의 자식으로 값 4를 가지는 새로운 노드를 `shared_ptr`로 생성하여 추가합니다.
* `root->children[0]->children.push_back(make_shared<TreeNode>(5));`: 루트 노드의 첫 번째 자식(값 2를 가진 노드)의 자식으로 값 5를 가지는 새로운 노드를 `shared_ptr`로 생성하여 추가합니다.
* `printTree(root);`: `printTree` 함수를 호출하여 루트 노드부터 시작하여 전체 트리의 구조와 값을 출력합니다.
* `return 0;`: 프로그램이 정상적으로 종료됩니다. `root`를 포함한 모든 `shared_ptr` 변수가 스코프를 벗어나면서 참조 카운트가 감소하고, 더 이상 참조하는 스마트 포인터가 없으면 해당 `TreeNode` 객체의 메모리가 자동으로 해제됩니다.

이 코드는 스마트 포인터(`shared_ptr`)를 사용하여 트리 구조를 안전하게 관리하고, 재귀 함수를 통해 트리 노드의 값들을 깊이에 따라 들여쓰기하여 시각적으로 표현합니다.

*/