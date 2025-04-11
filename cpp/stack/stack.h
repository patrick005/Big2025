#ifndef STACK_H
#define STACK_H

class Stack {
    private: //implementation
        int *pArr;
        int size;
        int tos;
    
    public: //interface
        //멤버함수로 구조체 안에 들어감
        //void initStack(int size); -> 생성자로 변경(constructor)
        //void cleanupStack();      -> 소멸자로 변경
        Stack(int size);        //constructor
        ~Stack();          //destructor

        void push(int data);
        int pop(); 
};
//c의 전역함수를 cpp의 멤버함수로 변경하면서 구조체에 묶임
#endif