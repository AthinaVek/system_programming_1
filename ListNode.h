#ifndef LISTNODE_H
#define LISTNODE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int id;
    int counter;
    int frequency;
    int inDocs;
    struct Node *next;
}ListNode;

ListNode *appendNode(ListNode *head, int id);
ListNode *searchNode(ListNode *head, int id);
void freeList(ListNode *head);

#endif /* LISTNODE_H */

