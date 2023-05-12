// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 999999;

// Hash table
node *table[N];

unsigned int tableSize = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashedWord = hash(word);

    node *linkedList = table[hashedWord];

    while (linkedList != NULL)
    {
        if (strcasecmp(linkedList->word, word) == 0)
        {
            return true;
        }

        linkedList = linkedList->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return (tolower(word[0]) + tolower(word[1])) - 1;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    FILE *dict = fopen(dictionary, "r");
    char buffer[LENGTH + 1];

    if (dict == NULL)
    {
        return false;
    }

    while (fscanf(dict, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, buffer);
        int index = hash(buffer);
        n->next = table[index];
        table[index] = n;

        tableSize++;
    }

    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return tableSize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    for (int i = N - 1; i >= 0; i--)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

        if (cursor == NULL && i == 0)
        {
            return true;
        }
    }

    return false;
}
