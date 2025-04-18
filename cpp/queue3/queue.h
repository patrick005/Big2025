#ifndef QUEUE_H
#define QUEUE_H

#include "array.h"

class Queue{
    private:
        static const int QUEUE_SIZE; 
        // int *pArr_;
        // int size_;
        Array arr_;     //include "array.h" -> has-a 관계, 일종의 상속으로 설명하기도 함
        int front_;
        int rear_;

        //안쓸 함수 적어두기
        Queue(const Queue& ); // 복사생성자
        Queue& operator=(const Queue& ); // 치환연산자 

    public:
        explicit Queue(int size = QUEUE_SIZE);
        ~Queue();

        bool isEmpty() const;
        bool isFull() const;
        int size() const;
        int avab() const;
        
        void push(int data);
        int pop();

        
    };

#endif