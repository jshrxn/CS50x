// Validates credit card numbers using Luhn's algorithm

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get input from user
    long long card_number;
    do
    {
        card_number = get_long("Number: ");
    }
    while (card_number < 0);

    // Make a copy to work with
    long long temp = card_number;

    // Variables for Luhn's algorithm
    int sum = 0;
    int count = 0;

    // Caclulate and apply Luhn's algorithm
    while (temp > 0)
    {
        int digit = temp % 10;
        temp /= 10;
        count++;

        if (count % 2 == 0)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit = (digit / 10) + (digit % 10);
            }
        }
        sum += digit;
    }

    // Validation check on Luhn's checksum
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Check for length and prefix for card type
    temp = card_number;
    while (temp >= 100)
    {
        temp /= 10;
    }
    if (count == 15 && (temp == 34 || temp == 37))
    {
        printf("AMEX\n");
    }
    else if (count == 16 && (temp >= 51 && temp <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((count == 13 || count == 16) && (temp / 10 == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
