#include "ListNode.h"

ListNode *appendNode(ListNode *head, int id){
    ListNode *newNode, *lastNode;
    
    newNode = malloc(sizeof(ListNode));
    newNode->id = id;
    newNode->counter = 1;
    newNode->frequency = 1;
    newNode->next = NULL;
    
    if (head == NULL){
       head = newNode;
       head->inDocs = 1;
    }  
    else{
        head->frequency++;
        lastNode = head;
        while (lastNode->next != NULL)
            lastNode = lastNode->next;
        lastNode->next = newNode;
        head->inDocs++;
    }
    return newNode;  
}

ListNode *searchNode(ListNode* head, int id){
    ListNode* curNode = head;
    
    while (curNode != NULL){
        if (curNode->id == id)
            return curNode;
        curNode = curNode->next;
    }
    
    return NULL;
}

void freeList(ListNode *head){
    ListNode* curNode = head;
    while (curNode != NULL){
        curNode = head->next;
        free (head);
    }
}