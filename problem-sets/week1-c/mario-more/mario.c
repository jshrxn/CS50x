// Prints a pyramid of hashes

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int x = 0; x < height; x++)
    {
        // Left panel
        for (int s = 0; s < height - x - 1; s++)
        {
            printf(" ");
        }
        for (int h = 0; h < x + 1; h++)
        {
            printf("#");
        }

        // Gap between halves
        printf("  ");

        // Right panel
        for (int h = 0; h < x + 1; h++)
        {
            printf("#");
        }
        printf("\n");
    }
}
