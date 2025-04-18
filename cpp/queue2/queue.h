#ifndef QUEUE_H
#define QUEUE_H
// #define QUEUE_SIZE 100 //컴파일시 타입체크를 위해 queue.cpp로 넘어감 -> 그걸 불러오기위해 extern 을써서 호출해서 여기 박제
// extern const int QUEUE_SIZE;

class Queue{
    private:
        static const int QUEUE_SIZE; // 멤버함수만 쓸수 있게 위에서 내리면서 extern이 아닌 static 멤버 변수로 변경 
        int *pArr_;
        int size_;
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