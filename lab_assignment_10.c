#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
struct TrieNode
{
    struct TrieNode *children[26];
    int count; // to store the count of occurrences
};

// Initializes a trie node
struct TrieNode *createNode()
{
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node) {
        node->count = 0;
        for (int i = 0; i < 26; ++i)
            node->children[i] = NULL;
    }
    return node;
}

// Inserts the word to the trie structure
void insert(struct TrieNode *root, char *word)
{
    struct TrieNode *current = root;
    for (int i = 0; i < strlen(word); ++i)
    {
        int index = word[i] - 'a';
        if (!current->children[index])
            current->children[index] = createNode();
        current = current->children[index];
    }
    current->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct TrieNode *root, char *word)
{
    struct TrieNode *current = root;
    for (int i = 0; i < strlen(word); ++i)
    {
        int index = word[i] - 'a';
        if (!current->children[index])
            return 0; // Word not found
        current = current->children[index];
    }
    return current->count;
}

// Deallocates the trie structure
void deallocateTrie(struct TrieNode *root)
{
    if (root)
    {
        for (int i = 0; i < 26; ++i)
            deallocateTrie(root->children[i]);
        free(root);
    }
}

// Reads the dictionary file and stores the words in the array
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return 0;
    }

    int numWords = 0;
    char word[256];
    while (fscanf(file, "%s", word) != EOF)
    {
        pInWords[numWords] = strdup(word);
        numWords++;
    }
    fclose(file);
    return numWords;
}

int main(void)
{
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct TrieNode *root = createNode();
    for (int i = 0; i < numWords; i++)
    {
        insert(root, inWords[i]);
    }
    // Parse line by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(root, pWords[i]));
    }
    deallocateTrie(root);
    return 0;
}
