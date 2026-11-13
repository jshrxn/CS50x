// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Initialize number of buckets in hash table
const unsigned int N = 26;

// Initialize a dictionary word counter variable
unsigned int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Calculate the bucket ndex for the given word
    unsigned int index = hash(word);

    // Start at the first node in the corresponding bucket
    node *cursor = table[index];

    // Check whether the null bucket is empty
    if (cursor == NULL)
    {
        return false;
    }

    // Transverse the linked list until the word is found or the end is reached
    while (cursor != NULL)
    {
        // Compare words without considering letter case
        int cmp = strcasecmp(cursor->word, word);

        // Return true if words match
        if (cmp == 0)
        {
            return true;
        }

        // Otherwise, move to the next node in the linked list
        else
        {
            cursor = cursor->next;
        }
    }
    // Return false if the word was not found in the linked list
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Initialize the hash_value
    unsigned int hash_value = 0;

    // Process every character in the word
    while (*word)
    {
        // Multipy previous hash value by 31 and add the lowercase value of the current character
        // I chose to multiply by 31 to make character positions influence the resulting hash value
        // 31 is a commonly used multiplier in string hashing
        hash_value = (hash_value * 31) + tolower((unsigned char) *word);

        // Move to the next character
        word++;
    }

    // Ensure the hash value fits within the hash table's bucket range
    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Opens the dictionary file for reading
    FILE *source = fopen(dictionary, "r");

    // Check whether the file was successfully opened
    if (source == NULL)
    {
        printf("Could not open file\n");
        return false;
    }

    // Initialize temporary character array to store each dictionary word
    char word[LENGTH + 1];

    // Read each word from the dictionary
    while (fscanf(source, "%45s", word) == 1)
    {
        // Calculate the bucket index for the word
        unsigned int index = hash(word);

        // Allocate memory for a new node
        node *new_node = malloc(sizeof(node));

        // Handle allocation failure and release previously allocated memory
        if (new_node == NULL)
        {
            fclose(source);
            unload();
            return false;
        }

        // Copy the word into the new node
        strcpy(new_node->word, word);

        // Link the node into the hash table
        new_node->next = table[index];
        table[index] = new_node;

        // Increment the dictionary word count
        word_count++;
    }
    // Close the dictionary file
    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return the total number of words loaded into the dictionary
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through every bucket in the hash table
    for (unsigned int i = 0; i < N; i++)
    {
        // Starts at the first node in the current bucket
        node *cursor = table[i];

        // Transverse and free every node in the linked list
        while (cursor != NULL)
        {
            // Save the next node before freeing the current one
            node *tmp = cursor->next;

            // Release the current node's allocated memory
            free(cursor);

            // Move to the next node
            cursor = tmp;
        }
        // Reset the bucket to NULL after freeing its nodes
        table[i] = NULL;
    }
    // Reser the dictionary word count
    word_count = 0;

    return true;
}
