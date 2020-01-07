#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trie.h"


int main(int argc, char** argv) {
    int i, lineCount=0, j, K=10, pos; 
    size_t lineLength, size;
    char c, **map, *word, **sWords, *searchWords, *w;
    FILE *fp;
    bool isDoc=0, isK=0; 
    TrieNode *trie=NULL;
    
    for (int m=1; m<argc-1; m++){
        if ((strcmp(argv[m],"-i")==0) && (strcmp(argv[m+1],"-k")!=0)){
            isDoc = 1;
            pos = m+1;
        }
        else if ((strcmp(argv[m],"-k") == 0) && (strcmp(argv[m],"-i")!=0))
            K = atoi(argv[m+1]);
    }
    
    if (isDoc == 0){
        printf("ERROR: NO DOCUMENT\n");
        return 0;
    }
    
    fp = fopen(argv[pos], "r");
    if (fp){
        while ((c = fgetc(fp)) != EOF){
            if (c == '\n')
                lineCount++;
        }
        
        map = malloc(lineCount*sizeof(char*));
        rewind(fp);

        for (i=0; i<lineCount; i++){     //vazw kathe grammh sto map
            getline(&map[i], &lineLength, fp);
            //printf("%s", map[i]);
//            if (strncmp(map[i], '\n', 2) == 0)
//                continue;
//            if (atoi(map[i]) != i){
//                printf("ERROR\n");
//                
//                return 0;
//            }

        }
        
        rewind(fp); 
        char *word, *id, **temp;
        temp = malloc(lineCount*sizeof(char*));    //dhmiourgia antigrafou pinaka
        for (i=0; i<lineCount; i++)
            temp[i] = malloc(strlen(map[i])*sizeof(char));
        
        for (i=0; i<lineCount; i++){ 
            memcpy(temp[i], map[i], strlen(map[i])*sizeof(char));  //antigrafh pinaka
            word = strtok(temp[i], " \n ");    //petaw to id
            word = strtok(NULL, " \n ");    
            
            while (word != NULL){    //spasimo se lekseis kai insert sto trie
                //printf ("_____\n%s\n", word); 
                insertTrie(&trie, word, i);
                word = strtok(NULL, " '\n'");
            }
        }

        searchWords = NULL;
        printf("GIVE COMMAND: ");
        getline(&searchWords, &size, stdin);   //eisagwgh leksewn anazhthshs
        
        while (strncmp(searchWords,"/exit",5) != 0){
            j=0;
            w = strtok(searchWords, " \n\t");    
            sWords = malloc(11*sizeof(char*));
            while (w != NULL){
                sWords[j] = malloc(strlen(w)*sizeof(char));
                sWords[j] = w;
                w = strtok(NULL, " \n");
                j++;
            }

            if (strncmp(sWords[0],"/tf",3) == 0){    
                ListNode *pL1;
                pL1 = searchTrie(&trie, sWords[2]);
                if(pL1){
                    ListNode *pL2;
                    pL2 = searchNode(pL1, atoi(sWords[1]));
                    if (pL2)
                        printf("%d %s %d\n", pL2->id, sWords[2], pL2->counter);
                    else
                        printf("The word doesn't exist in the doc.\n");
                }
                else
                    printf("The word doesn't exist.\n");
            }
            else if (strncmp(sWords[0],"/df",3) == 0){  
                if(j == 1){
                    char str[30];
                    int l=0;
                    triePrint(trie, str, l);
                }
                else{
                    ListNode *p;
                    p = searchTrie(&trie, sWords[1]);
                    if (p != NULL)
                        printf("%s %d\n", sWords[1], p->inDocs);
                    else
                        printf("The word doesn't exist.\n");
                }
            }
            searchWords = NULL;
            printf("GIVE COMMAND: ");
            getline(&searchWords, &size, stdin);   //eisagwgh leksewn anazhthshs
        }
        
        for (i=0; i<lineCount; i++){
            free (map[i]);
            free (temp[i]);
        }
        free (map);
        free (temp);
        
        for (i=0; i<j-1; i++){
            free (sWords[i]);
        }
        free (sWords);
        
        free(trie);
    }
    return 0;
}

