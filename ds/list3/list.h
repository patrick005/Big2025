#ifndef LIST_H
#define LIST_H

typedef struct node{
    //int data;
    struct node *next;
} Node;

typedef struct{
    Node *ptr;
    int eleSize; // 동적할당을 위한 사이즈 확인
} List;


void initList(List *pList, int eleSize);
void cleanupList(List *pList);

void printList(const List *pList, void (*print)(const void *));

void insertFirstNode(List *pList, const void *pData);
void insertNode(List *pList, const void *prevData, const void *pData);

void deletNode(List *pList, const void *pData);
//int data -> const void *pData

#endif