// A program that calculates the approximate grade level needed to comprehend some text.

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Initialize the prototype of the functions
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{

    // Get input
    string text = get_string("Text: ");

    // initialize variables
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Compute the Coleman-Liau index
    float L = (100.0 * letters) / words;
    float S = (100.0 * sentences) / words;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Print the Grade Level
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }

    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

// Return the number of letters in a text given a user's input
int count_letters(string text)
{
    int letters = 0;

    for (int i = 0; text[i]; i++)
    {
        if (isalpha((unsigned char) text[i]))
        {
            letters++;
        }
    }

    return letters;
}

// Return the number of words in a text given the user's input
int count_words(string text)
{
    int words = 0, prev_space = 1;

    for (int i = 0; text[i]; i++)
    {
        if (!isspace(text[i]) && prev_space)
            words++;
        prev_space = isspace(text[i]);
    }
    return words;
}

// Return the number of sentences in a text given the user's input
int count_sentences(string text)
{
    int sentences = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}
