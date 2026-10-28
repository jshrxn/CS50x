// A program that recovers JPEGs from a memory card.

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Validates exaxtly 2 cli args
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open, read, and validate the file
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        return 1;
    }

    // Read the memory card one 512-byte block at a time
    uint8_t buffer[512];

    // Track the number of recovered JPEG's for sequential filenames.
    int img_counter = 0;

    // Store the currently open output JPEG
    FILE *img;

    // Track the open-state flag of the JPEG
    bool jpeg_open = false;

    // Process each complete 512-byte block until the input ends
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Identify a JPEG by checking its signature in the first four bytes
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // A new JPEG marks the end of the previous one
            if (jpeg_open == true)
            {
                fclose(img);
            }

            // Generate the next filename
            char filename[8];
            sprintf(filename, "%03i.jpg", img_counter);

            // Create the new output JPEG and check that it opened successfully.
            img = fopen(filename, "w");
            if (img == NULL)
            {
                return 1;
            }

            // Advance the filename counter and mark the JPEG as open.
            img_counter++;
            jpeg_open = true;
        }

        // Write the current block whenever an output JPEG is open.
        if (jpeg_open == true)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    // Close the final JPEG, which has no subsequent JPEG signature to close it
    if (jpeg_open == true)
    {
        fclose(img);
    }

    // Release the input file after processing the memory card
    fclose(card);
}
