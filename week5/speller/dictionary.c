// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

long words_in_dict;

void free_node(node *n);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get length of string
    int len = strlen(word);

    // Set lower case word
    char word_lower[len];
    for (int i = 0; i <= strlen(word); i++)
    {
        word_lower[i] = tolower(word[i]);
    }

    // Initial node to check
    node *t = table[hash(word_lower)];

    // While a node exists, check if word is node
    while (t != NULL)
    {
        if (strcmp(t->word, word_lower) == 0)
        {
            return true;
        }
        else
        {
            t = t->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Get first letter of word and return as numerical value 0-25
    if (toupper(word[0]) >= 65 && toupper(word[0]) <= 90)
    {
        return toupper(word[0]) - 65;
    }
    else
    {
        printf("Hash function:- first letter of %s is not alphabetical\n", word);
        return 0;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open file and check opened
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Load function:- Could not open dictionary\n");
        return false;
    }

    // Reset words in dictionary counter
    words_in_dict = 0;

    // node *n;
    int index = 0;

    // Allocate memory for initial node positions
    for (int i = 0; i < N; i++)
    {
        table[i] = (node *) malloc(sizeof(node));
        strcpy(table[i]->word, "");
        table[i]->next = NULL;
    }

    // For each word in file
    char word[LENGTH + 1] = {""};
    while (fscanf(file, "%s", word) == 1)
    {
        // Open each file until EOF
        if (strcmp(word, "EOF") == 0)
        {
            break;
        }

        // Set initial hash table node for word
        node *t = table[hash(word)];

        // Go to end of linked list to store word, check if word already exists
        while (t != NULL && t->next != NULL)
        {
            if (strcmp(word, t->word) == 0)
            {
                break;
            }
            t = t->next;
        }

        // If word exists go to next word
        if (strcmp(word, t->word) == 0)
        {
            continue;
        }

        // Allocate memory for word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Load function:- Malloc error initializing node\n");
            return false;
        }

        // Copy word into linked list
        strcpy(n->word, word);
        n->next = NULL;

        words_in_dict++;
        t->next = n;
    }

    fclose(file);
    return true;

    /*
    // Open file and check opened
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Load function:- Could not open dictionary\n");
        return false;
    }

    // Reset words in dictionary counter
    words_in_dict = 0;

    // node *n;
    int index = 0;

    // Allocate memory for initial node positions
    for (int i = 0; i < N; i++)
    {
        table[i] = (node *) malloc(sizeof(node));
        strcpy(table[i]->word, "");
        table[i]->next = NULL;
    }

    // For each word in file
    char word[LENGTH + 1] = {""};
    while (fscanf(file, "%s", word) == 1)
    {
        // Open each file until EOF
        if (strcmp(word, "EOF") == 0)
        {
            break;
        }

        // Set initial hash table node for word
        node *t = table[hash(word)];

        // Go to end of linked list to store word, check if word already exists
        while (t != NULL && t->next != NULL)
        {
            if (strcmp(word, t->word) == 0)
            {
                break;
            }
            t = t->next;
        }

        // If word exists go to next word
        if (strcmp(word, t->word) == 0)
        {
            continue;
        }

        // Allocate memory for word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Load function:- Malloc error initializing node\n");
            return false;
        }

        // Copy word into linked list
        strcpy(n->word, word);
        n->next = NULL;

        words_in_dict++;
        t->next = n;
    }

    fclose(file);
    return true;
    */
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words_in_dict;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        free_node(table[i]);
    }

    return true;
}

void free_node(node *n)
{
    // Handle base case
    if (n == NULL)
    {
        return;
    }

    // free linked nodes
    free_node(n->next);

    // Free child
    free(n);
}
