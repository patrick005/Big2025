
#include "list.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


static Node *createNode(int data, Node *next){
    // Node *p = malloc(sizeof(Node));
    Node *p = new Node[sizeof(Node)];
    assert(p);
    p->data = data;
    p->next = next;

    return p;
}

// void initList(){
List::List(){
    // this->ptr = malloc(sizeof(Node));
    this->ptr = new Node[sizeof(Node)];
    assert(this->ptr);
    this->ptr->next = NULL;
    this->ptr = createNode(-1, NULL);
}

// void cleanuthis(){
List::~List(){
    Node *ptr = this->ptr;
    while (ptr){
        Node *tmp = ptr;
        ptr = ptr->next;
        // free(tmp);
        delete [] tmp;
    }
}

// void printList(const List *this){
void List::printList(){
    Node *ptr = this->ptr->next;
    printf("[");
    while (ptr){
        printf("%d", ptr->data);
        printf((ptr->next ) ? ", " : "");
        ptr = ptr->next;
    }
    printf("]\n");
}

// void insertFirstNode(List *this, int data){
void List::insertFirstNode(int pData){
    // Node *tmp = malloc(sizeof(Node));
    Node *tmp = new Node[sizeof(Node)];
    assert(tmp);
    tmp->data = pData;
    tmp->next = this->ptr->next;
    this->ptr->next = tmp;
    // this->ptr->next = createNode(data, this->ptr->next);
}

// void insertNode(List *this, int prevData, int data){
void List::insertNode(int prevData, int data){
    Node *ptr = this->ptr->next;
    while (ptr){
        if (ptr->data == prevData){
            break;
        }
        ptr = ptr->next;
    }
    if (ptr){
        // Node *tmp = malloc(sizeof(Node));
        Node *tmp = new Node[sizeof(Node)];
        assert(tmp);
        tmp->data = data;
        tmp->next = ptr->next;
        ptr->next = tmp;
        // p->next = createNode(data , p->next);
    }
}

// void deleteNode(List *this, int data){
void List::deleteNode(int data){
    Node *ptr = this->ptr->next;
    Node *ptr2 = this->ptr;
    while (ptr){
        if (ptr->data == data){
            break;
        }
        ptr = ptr->next;
        ptr2 = ptr2->next;
    }
    if (ptr){
        ptr2->next = ptr->next;
        // free(ptr);
        delete [] ptr;
    }
}