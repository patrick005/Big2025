// #pragma once
#ifndef STACK_H
#define STACK_H

typedef struct stack {
    //int *pArr;
    void *pArr;
    int eleSize;

    int size;
    int tos;
} Stack;

void initStack(Stack *ps, int size, int eleSize);
void cleanupStack(Stack *ps);

// void push(Stack *ps, int data);
void push(Stack *ps, const void *pData/*, int eleSize*/);
// int pop(Stack *ps, int *pData);
void pop(Stack *ps, void *pData/*, int eleSize*/);


#endif