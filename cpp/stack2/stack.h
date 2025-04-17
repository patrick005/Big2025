#ifndef STACK_H
#define STACK_H

// #define STACK_SIZE 100
// extern const int STACK_SIZE; // 다른 파일에서 가져다 쓸 수 있게 파일 전역 변수로 설정: extern

class Stack {
    private: //implementation
        static const int STACK_SIZE;
        int *pArr_;
        int size_;
        int tos_;
    
        Stack(const Stack& );       // 안쓰는거 프라이빗에 봉인하기
        Stack& operator=(const Stack& ); // 치환연산 안씀

    public: 
        // Stack();
        explicit Stack(int size = STACK_SIZE);
        ~Stack();


        //Stack *operator&(){ return this; }
        //const Stack *operator&() const { return this; }
        //Stack(){}
        //Stack(const Stack& ){ /* meberwise copy*/ }
        //~Stack(){}
        //Stack& operator=(const Stack& ){ /* meberwise copy*/ return *this; }
        
        void push(int data);
        int pop(); 
        
        bool isEmpty() const;
        bool isFull() const;

        int size() const;
        int avab() const;

        
    };

#endif