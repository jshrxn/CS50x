// A program that applies filters to BMPs.

#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Visit every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average color
            int average = (int) round(
                (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // Update the pixel
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Visit each row
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Find the mirrored position
            int mirror = width - 1 - j;

            // Swap the pixels
            RGBTRIPLE temp;
            temp = image[i][j];
            image[i][j] = image[i][mirror];
            image[i][mirror] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the original image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Visit every pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize accumulators
            int red = 0;
            int green = 0;
            int blue = 0;
            int count = 0;

            // Examine the 3x3 neighborhood
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Skip neighbors outside the image
                    if (ni < 0 || ni >= height || nj < 0 || nj >= width)
                    {
                        continue;
                    }

                    // Accumulate original RGB values
                    red += copy[ni][nj].rgbtRed;
                    green += copy[ni][nj].rgbtGreen;
                    blue += copy[ni][nj].rgbtBlue;

                    count++;
                }
            }

            // Average the valid neighbors and update the current pixel
            image[i][j].rgbtRed = (int) round((float) red / count);
            image[i][j].rgbtGreen = (int) round((float) green / count);
            image[i][j].rgbtBlue = (int) round((float) blue / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the original image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Produce the matrices
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Visit every target pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize accumulators
            int redx = 0, greenx = 0, bluex = 0;
            int redy = 0, greeny = 0, bluey = 0;

            // Examine the 3x3 neighborhood
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Skip neighbors outside the image
                    if (ni < 0 || ni >= height || nj < 0 || nj >= width)
                    {
                        continue;
                    }

                    // Implementation of the 6 accumulators
                    redx += copy[ni][nj].rgbtRed * Gx[di + 1][dj + 1];
                    greenx += copy[ni][nj].rgbtGreen * Gx[di + 1][dj + 1];
                    bluex += copy[ni][nj].rgbtBlue * Gx[di + 1][dj + 1];
                    redy += copy[ni][nj].rgbtRed * Gy[di + 1][dj + 1];
                    greeny += copy[ni][nj].rgbtGreen * Gy[di + 1][dj + 1];
                    bluey += copy[ni][nj].rgbtBlue * Gy[di + 1][dj + 1];
                }
            }

            // Calculate the edge strength
            double R = sqrt((redx * redx) + (redy * redy));
            double G = sqrt((greenx * greenx) + (greeny * greeny));
            double B = sqrt((bluex * bluex) + (bluey * bluey));

            // Cap the values at 255
            if (R > 255)
            {
                R = 255;
            }

            if (G > 255)
            {
                G = 255;
            }

            if (B > 255)
            {
                B = 255;
            }

            // Update results to target pixel
            image[i][j].rgbtRed = round(R);
            image[i][j].rgbtGreen = round(G);
            image[i][j].rgbtBlue = round(B);
        }
    }
    return;
}
