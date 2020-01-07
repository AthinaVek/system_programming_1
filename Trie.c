#include "Trie.h"

TrieNode *newTrieNode(char c){
    TrieNode *newNode;
    newNode = malloc(sizeof(TrieNode));
    newNode->c = c;
    newNode->child = NULL;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void freeTrie(TrieNode *curNode){
    if(curNode != NULL){
        freeTrie(curNode->left);
        freeTrie(curNode->right);
        freeTrie(curNode->child);
        free(curNode);
    }
}


ListNode *searchTrie(TrieNode **head, char *word){
    int length, i=0;
    TrieNode *curNode;

    length = strlen(word);
    curNode = *head;

    while(i<length){
        if (i == length-1)
            return (curNode->pList);

        if ((curNode->c == word[i]) && (curNode->child != NULL)){
            curNode = curNode->child;
            i++;
        }
        else if ((curNode->c > word[i]) && (curNode->left != NULL))
            curNode = curNode->left;
        else if ((curNode->c < word[i]) && (curNode->right != NULL))
            curNode = curNode->right;
        else    //an den uparxei epistrefei null
            return NULL;
    }
}


void insertTrie(TrieNode **head, char *word, int id){
    int length, i=0;
    bool child=0;
    TrieNode *curNode;
    length = strlen(word);

    if (*head == NULL){
        curNode = newTrieNode(word[i]);
        *head = curNode;
        i++;
        child = 1;
    }
    curNode = *head;

    while (i <= length){
        if(i == length ){
          break;
        }
        if ( (curNode->c == word[i]) && (curNode->child != NULL) && (child==0)){
            i++;
            //printf("PROXWRAEI CHILD\n");
            curNode = curNode->child;
            if((i == length-1) && (curNode->c == word[i]))
                break;
        }
        else if ((curNode->c > word[i]) && (curNode->left != NULL) && (child==0)){
            curNode = curNode->left;
            //printf("PROXWRAEI LEFT\n");
        }
        else if ((curNode->c < word[i]) && (curNode->right != NULL) && (child==0)){
            curNode = curNode->right;
            //printf("PROXWRAEI RIGHT\n");
        }
        else  {
            //an den uparxei, ftiaxnei node kai eisagei to gramma
            if ((curNode->c > word[i]) && (curNode->left == NULL)&& (child==0)){
                curNode->left = newTrieNode(word[i]);
                curNode = curNode->left;
                child = 1;
                //printf("FTIAXNEI LEFT\n");
                i++;
            }
            else if ((curNode->c < word[i]) && (curNode->right == NULL)&& (child==0)){
                curNode->right = newTrieNode(word[i]);
                curNode = curNode->right;
                child = 1;
                //printf("FTIAXNEI RIGHT\n");
                i++;
            }
            else{
                if((curNode->c == word[i]) && (*(word+i+1)) && (child==0)){
                    curNode->child = newTrieNode(word[i+1]);
                    curNode = curNode->child;
                    //printf("NEW %c\n", curNode->c);
                    child = 1;
                    i+=2;
                    continue;
                }
                curNode->child = newTrieNode(word[i]);
                curNode = curNode->child;
                //printf("NEW %c\n", curNode->c);
                child = 1;
                //printf("CHILD curNode after %c\n\n", curNode->c);
                i++;
            }
        }
    }
    //ananewsh pList
    ListNode *postList;
    if (curNode->pList != NULL){
        postList = searchNode(curNode->pList, id);
        if (postList == NULL){      //an den uparxei node gia to id auto
            postList = appendNode(curNode->pList, id);
            //printf("%d, %d \n", postList->id, postList->counter);
        }
        else{
            curNode->pList->frequency++;
            postList->counter++;
            //printf("%d, %d \n", postList->id, postList->counter);
        }
    }
    else{     //an den uparxei list
        postList = appendNode(NULL, id);
        curNode->pList = postList;
        //printf("%d, %d \n", postList->id, postList->counter);
    }
}


void triePrint(TrieNode *curNode, char *word, int i){
    if(curNode != NULL){
        if (curNode->pList != NULL){
            word[i] = curNode->c;
            i++;
            word[i] = '\0';
            printf("%s %d\n", word, curNode->pList->inDocs);
            i--;
        }
        triePrint(curNode->left, word, i);
        triePrint(curNode->right, word, i);
        word[i] = curNode->c;
        i++;

        triePrint(curNode->child, word, i);
    }
}
