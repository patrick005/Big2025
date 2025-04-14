#ifndef QUEUE_H
#define QUEUE_H

class Queue{
    private:
        int *pArr;
        int size;
        int front;
        int rear;
    
    public:
        // void initQueue(Queue *pq, int size);
        // void cleanupQueue(Queue *pq);
        Queue(int size);
        ~Queue();

        void push(int data);
        int pop();
        
    };

#endif