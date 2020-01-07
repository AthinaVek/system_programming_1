#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ListNode.h"
#include "Trie.h"

double Score(char **map, int lineCount, char  *words, int D, int N);
int docsWithWord(char **map, char *word, int lineCount);
int frequency(char *word);

#endif /* SCORE_H */

