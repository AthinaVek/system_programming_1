objects = minisearch.o Trie.o ListNode.o

all: $(objects)
	gcc -g $(objects) -o minisearch -lm

minisearch.o: minisearch.c
	gcc -g -c -lm -Wall minisearch.c

Trie.o: Trie.c
	gcc -g -c -lm -Wall Trie.c

ListNode.o: ListNode.c
	gcc -g -c -lm -Wall ListNode.c

clean:
	rm -f $(objects) minisearch
