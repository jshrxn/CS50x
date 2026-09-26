// A program that implements the substitution cipher.

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Rejects if it is not exactly 2 cli args.
    if (argc != 2)
    {
        printf("Usage: %s <key>\n", argv[0]);
        return 1;
    }

    // Rejects if key is not exactly 26 characters.
    size_t len = strlen(argv[1]);

    if (len != 26)
    {
        printf("Error: Key must be exactly 26 characters.\n");
        return 1;
    }

    // Rejects if key is not alphabet.
    for (size_t i = 0; i < len; i++)
    {
        if (!isalpha((unsigned char) argv[1][i]))
        {
            printf("Error: Key must be alphabet only.\n");
            return 1;
        }
    }

    // Rejects repeating characters.
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = i + 1; j < len; j++)
        {
            if (toupper(argv[1][i]) == toupper(argv[1][j]))
            {
                printf("Error: key contains repeating characters.\n");
                return 1;
            }
        }
    }

    // Enchiper Logic
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            // ASCII: 'A'–'Z' are contiguous (65–90), so subtracting 'A'
            // maps any letter to its 0-based position in the alphabet.
            // toupper normalizes case so lowercase also lands in 0–25.
            int index = toupper(plaintext[i]) - 'A';

            // Key is positionally encoded: argv[1][index] is the
            // ciphertext for the (index+1)th letter of the alphabet.
            // Re-apply the original letter's case to the result.
            if (isupper(plaintext[i]))
                printf("%c", toupper(argv[1][index]));
            else
                printf("%c", tolower(argv[1][index]));
        }
        else
        {
            // Non-letters (spaces, digits, punctuation) pass through unchanged
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}
