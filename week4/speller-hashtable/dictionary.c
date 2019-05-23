// Dziugas Mikalkenas
// 20 May 2019
// Problem Set 4

// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Cannot allocate any memory to a node\n");
            unload();
            return false;
        }

        // copy buffer to new_node->word
        strcpy(new_node->word, word);
        // insert hashtable[index] value to new_node->next
        new_node->next = hashtable[hash(new_node->word)];
        // insert new_node address to hashtable[index]
        hashtable[hash(new_node->word)] = new_node;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int size = 0;

    // itterates trough hashtable
    for (int i = 0; i < N; i++)
    {
        // counts every item which does not point to null
        node *hash_cursor = hashtable[i];
        while (hash_cursor != NULL)
        {
            size += 1;
            hash_cursor = hash_cursor->next;
        }
        free(hash_cursor);
    }
    return size;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *trav = hashtable[hash(word)];
    while (trav != NULL)
    {
        if (strcasecmp(word, trav->word) == 0)
        {
            return true;
        }
        trav = trav->next;
    }
    free(trav);
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *hash_cursor = hashtable[i];
        while (hash_cursor != NULL)
        {
            node *temp = hash_cursor;
            hash_cursor = hash_cursor->next;
            free(temp);
        }
        free(hash_cursor);

        if (i == N - 1)
        {
            return true;
        }
    }
    return false;
}
