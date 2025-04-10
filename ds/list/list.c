#include "list.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void initList(List *pList){
    pList->ptr = malloc(sizeof(Node));
    assert(pList->ptr);
    pList->ptr->next = NULL;
}

void cleanupList(List *pList){
    Node *ptr = pList->ptr;
    while (ptr){
        Node *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
}

void printList(const List *pList){
    Node *ptr = pList->ptr->next;
    printf("[");
    while (ptr){
        printf("%d", ptr->data);
        printf((ptr->next ) ? ", " : "");
        ptr = ptr->next;
    }
    printf("]\n");
}

void insertFirstNode(List *pList, int data){
    Node *tmp = malloc(sizeof(Node));
    assert(tmp);
    tmp->data = data;
    tmp->next = pList->ptr->next;
    pList->ptr->next = tmp;
}

void insertNode(List *pList, int prevData, int data){
    Node *ptr = pList->ptr->next;
    while (ptr){
        if (ptr->data == prevData){
            break;
        }
        ptr = ptr->next;
    }
    if (ptr){
        Node *tmp = malloc(sizeof(Node));
        assert(tmp);
        tmp->data = data;
        tmp->next = ptr->next;
        ptr->next = tmp;
    }
}

void deletNode(List *pList, int data){
    Node *ptr = pList->ptr->next;
    Node *ptr2 = pList->ptr;
    while (ptr){
        if (ptr->data == data){
            break;
        }
        ptr = ptr->next;
        ptr2 = ptr2->next; // 따라감
    }
    if (ptr){
        ptr2->next = ptr->next; //앞서가던놈이 뒤로한칸 오면서 지워짐
        free(ptr); // 지워진거 할당 해제
    }
}

