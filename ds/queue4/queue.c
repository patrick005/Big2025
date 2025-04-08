#include "queue.h"
#include <assert.h>
#include <stdlib.h>

void initQueue(Queue *pq, int size){
    pq->pArr = malloc(sizeof(int)*size);
    assert(pq->pArr != NULL);
    pq->size = size;
    
    pq->front = pq->rear = 0;
}

void cleanupQueue(Queue *pq){
    free(pq->pArr);
}

void push(Queue *pq, int data){
    assert(pq->rear != pq->size);

    pq->pArr[pq->rear] = data;
    ++pq->rear;
}

int pop(Queue *pq){
    assert(pq->front != pq->rear);

    int index = pq->front;
    ++pq->front;
    return pq->pArr[index];

}
