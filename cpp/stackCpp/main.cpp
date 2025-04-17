// ./cpp/stackCpp/main.cpp
#include <iostream>
#include "stack.h"

int main(){
    Stack s1(10), s2(100);
    
    s1.push(100);
    s1.push(200);
    s1.push(300);

    std::cout << "s1 1st pop() : " << s1.pop() << std::endl;
    std::cout << "s1 2nd pop() : " << s1.pop() << std::endl;
    std::cout << "s1 3rd pop() : " << s1.pop() << std::endl;
    
    s2.push(110);
    s2.push(220);
    s2.push(330);
    
    std::cout << "s2 1st pop() : " << s2.pop() << std::endl;
    std::cout << "s2 2nd pop() : " << s2.pop() << std::endl;
    std::cout << "s2 3rd pop() : " << s2.pop() << std::endl;
    
    // s1.~Stack();
    // s2.~Stack();
    return 0;
}
