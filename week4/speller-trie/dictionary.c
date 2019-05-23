// Dziugas Mikalkenas
// 23 May 2019
// Problem Set 4

// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

// Declares count_words function
void count_words(node *trie, int *count);
void unload_words(node *trie);

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
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

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        node *trav = root;

        for (int i = 0; word[i] != '\0'; i++)
        {
            unsigned int index = 0;
            unsigned int *tmp = &index;

            if (word[i] == '\'')
            {
                *tmp = 26;
            }
            else
            {
                *tmp = tolower(word[i]) - 'a';
            }

            // Create new_node if null
            if (trav->children[index] == NULL)
            {
                // Initialize new_node
                node *new_node = malloc(sizeof(node));
                if (new_node == NULL)
                {
                    return false;
                }

                // Set new_node values
                new_node->is_word = false;
                for (int j = 0; j < N; j++)
                {
                    new_node->children[j] = NULL;
                }

                trav->children[index] = new_node;
                trav = new_node;
            }
            else
            {
                trav = trav->children[index];
            }
        }
        trav->is_word = true;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int sum = 0;
    count_words(root, &sum);
    return sum;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int length = strlen(word);
    node *trav = root;

    for (int i = 0; i < length; i++)
    {
        unsigned int index = 0;
        unsigned int *tmp = &index;

        if (word[i] == '\'')
        {
            *tmp = 26;
        }
        else
        {
            *tmp = tolower(word[i]) - 'a';
        }

        if (trav->children[index] != NULL)
        {
            if (i == length - 1)
            {
                return trav->children[index]->is_word ? true : false;
            }
            else
            {
                trav = trav->children[index];
            }
        }
        else
        {
            return false;
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    unload_words(root);
    free(root);
    return true;
}

// Counts words in trie
void count_words(node *trie, int *sum)
{
    int i = 0;
    while (i < N)
    {
        // Check if not null
        if (trie->children[i] != NULL)
        {
            // Check if word ends
            if (trie->children[i]->is_word)
            {
                *sum += 1;
                count_words(trie->children[i], sum);
            }
            else
            {
                count_words(trie->children[i], sum);
            }
        }
        i++;
    }
}

// Unloads trie
void unload_words(node *trie)
{
    int i = 0;
    while (i < N)
    {
        if (trie->children[i] != NULL)
        {
            unload_words(trie->children[i]);
            free(trie->children[i]);
        }
        i++;
    }
}
