// A Program that determines the winner of a short Scrabble-like game.

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// value of each char in the standard pointing system in scrabble
int char_value[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
//                  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^   ^  ^  ^  ^  ^  ^  ^  ^  ^  ^
//                  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p   q  r  s  t  u  v  w  x  y  z

// prototype for function
int compute_score(string word);

int main(void)
{
    // get input string
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // tracks the score
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // print output conditional
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
    printf("\n");
}

// function for computing score
int compute_score(string word)
{
    // Keeps track of scoring
    int score = 0;

    // compute the score for each character
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (isupper(word[i]))
        {
            score += char_value[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            score += char_value[word[i] - 'a'];
        }
    }

    return score;
}
