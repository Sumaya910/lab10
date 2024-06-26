#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
	int count;
	struct Trie *children[26];
};

// Initializes a trie structure
struct Trie *createTrie()
{
	struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    if (node) {
        node->count = 0;
        for (int i = 0; i < 26; i++) {
            node->children[i] = NULL;
        }
    }
    return node;
	
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
	struct Trie *current = pTrie;
    int len = strlen(word);

    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            current->children[index] = createTrie();
        }
        current = current->children[index];
    }

    current->count++;

}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
struct Trie *current = pTrie;
    int len = strlen(word);

    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            return 0; 
        }
        current = current->children[index];
    }

    return current->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
 if (pTrie) {
        deallocateTrie(pTrie);
        free(pTrie);
    }
    return NULL;
}


// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
	 int numWords = 0;
    FILE *file = fopen(filename, "r");
    if (file) {
        char word[256];
        while (fscanf(file, "%s", word) != EOF) {
            pInWords[numWords] = strdup(word);
            numWords++;
        }
        fclose(file);
    }
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}