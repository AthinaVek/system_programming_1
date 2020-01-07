#include "Score.h"

//n = plithos leksewn eisodou
//D = plithos leksewn tou doc
//N = plithos docs
//nqi = plithos docs me to word
//avgdl = meso plithos leksewn

double Score(int n, char **map, int lineCount, char *words, int D, int N){
    double k1=1.2, b=0.75, sum=0.0;
    double avgdl, idf, x;
    int nqi;
    char *word;
    avgdl = D/N;
            
    for(int i=0; i<n; i++){    //loop gia kathe leksh
        nqi = docsWithWord(map, word, lineCount);
        idf = log((N -  nqi + 0.5)/(nqi + 0.5));
        x = ((frequency(word)*(k1+1))/(frequency(word)+(k1*(1-b+(b*(D/avgdl))))));
        sum += idf*x;
    }
    
    
//    for (int i=0; i<n; i++){
//        idf = log((N -  nqi + 0.5)/(nqi + 0.5));
//        x = ((frequency(word)*(k1+1))/(frequency(word)+(k1*(1-b+(b*(D/avgdl))))));
//        sum += idf*x;
//    }
    return sum;
}

int docsWithWord(char **map, char *word, int lineCount){
    int count=0;
    
    for (int i=0; i<lineCount; i++){
        if (strstr(map[i], word))
            count++;
    }
    return count;
}

int frequency(char *word){
    ListNode *pList;
    
    pList = searchTrie(trie, word);
    return pList->frequency;
}
