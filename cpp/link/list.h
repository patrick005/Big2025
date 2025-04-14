#ifndef LIST_H
#define LIST_H

typedef struct node{
// class Node{
    int data;
    struct node *next;
} Node;

class List{
    private:
        Node *ptr;
        
    public:    
        // void initList(int eleSize);
        // void cleanupList();
        List();
        ~List();

        void insertFirstNode(int pData);
        void insertNode(int prevData, int data);
        void deleteNode(int data);
        
        void printList();
    };
        //int data -> const void *pData

#endif