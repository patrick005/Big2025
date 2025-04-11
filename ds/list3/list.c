#include "list.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

void initList(List *pList, int eleSize){        //dummy
    pList->ptr = malloc(sizeof(Node) /*+ pList->eleSize*/); 
    assert(pList->ptr);
    pList->eleSize = eleSize;

    pList->ptr->next = NULL;
    // pList->ptr = createNode(-1, NULL);
}

void cleanupList(List *pList){
    Node *ptr = pList->ptr;
    while (ptr){
        Node *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
}

void printList(const List *pList, void (*print)(const void *)){
    Node *ptr = pList->ptr->next;
    printf("[");
    while (ptr){
        // printf("%d", ptr->data);
        print(ptr + 1);
        printf((ptr->next ) ? ", " : "");
        ptr = ptr->next;
    }
    printf("]\n");
}

void insertFirstNode(List *pList, const void *pData){
    Node *tmp = malloc(sizeof(Node) + pList->eleSize);
    assert(tmp);
    // tmp->data = data;
    // memcpy((unsigned char *)tmp + sizeof(Node), pData, pList->eleSize);
    memcpy(tmp + 1, pData, pList->eleSize);
    tmp->next = pList->ptr->next;
    pList->ptr->next = tmp;
    // pList->ptr->next = createNode(data, pList->ptr->next);
}

void insertNode(List *pList, const void *pPrevData, const void *pData){
    Node *ptr = pList->ptr->next;
    while (ptr){
        // if (ptr->data == prevData){
        if(memcmp(ptr + 1, pPrevData, pList->eleSize) == 0){
            break;
        }
        ptr = ptr->next;
    }
    if (ptr){
        Node *tmp = malloc(sizeof(Node) + pList->eleSize);
        assert(tmp);
        // tmp->data = data;
        memcpy(tmp + 1, pData, pList->eleSize);
        tmp->next = ptr->next;
        ptr->next = tmp;
        // ptr->next = createNode(data, ptr->next);
    }
}

void deletNode(List *pList, const void *pData){
    Node *ptr = pList->ptr->next;
    Node *ptr2 = pList->ptr;
    while (ptr){
        // if (ptr->data == data){
        if(memcmp(ptr + 1, pData, pList->eleSize) == 0){
            break;
        }
        ptr = ptr->next;
        ptr2 = ptr2->next;
    }
    if (ptr){
        ptr2->next = ptr->next;
        free(ptr);
    }
}


