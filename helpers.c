#include "helpers.h"

#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avrage = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avrage;
            image[i][j].rgbtGreen = avrage;
            image[i][j].rgbtRed = avrage;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int sepiaShadeR = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaShadeG = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaShadeB = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            if (sepiaShadeR > 255)
            {
                sepiaShadeR = 255;
            }
            if (sepiaShadeG > 255)
            {
                sepiaShadeG = 255;
            }
            if (sepiaShadeB > 255)
            {
                sepiaShadeB = 255;
            }
            image[i][j].rgbtRed = sepiaShadeR;
            image[i][j].rgbtGreen = sepiaShadeG;
            image[i][j].rgbtBlue = sepiaShadeB;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE tempRowRGBP;
        for (int j = 0; j < width / 2; j++)
        {
            tempRowRGBP = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tempRowRGBP;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image1[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image1[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blurRed = 0;
            int blurGreen = 0;
            int blurBlue = 0;
            if (i == 0 && j == 0)
            {
                blurRed = image1[i][j].rgbtRed + image1[i][j + 1].rgbtRed + image1[i + 1][j].rgbtRed + image1[i + 1][j + 1].rgbtRed;
                blurGreen = image1[i][j].rgbtGreen + image1[i][j + 1].rgbtGreen + image1[i + 1][j].rgbtGreen +
                            image1[i + 1][j + 1].rgbtGreen;
                blurBlue =
                    image1[i][j].rgbtBlue + image1[i][j + 1].rgbtBlue + image1[i + 1][j].rgbtBlue + image1[i + 1][j + 1].rgbtBlue;

                blurRed = round(blurRed / 4.0);
                blurGreen = round(blurGreen / 4.0);
                blurBlue = round(blurBlue / 4.0);
            }
            else if (i == 0 && j != (width - 1) && j != 0)
            {
                blurRed = image1[i][j - 1].rgbtRed + image1[i][j].rgbtRed + image1[i][j + 1].rgbtRed + image1[i + 1][j - 1].rgbtRed + image1[i + 1][j].rgbtRed + image1[i + 1][j + 1].rgbtRed;
                blurGreen = image1[i][j - 1].rgbtGreen + image1[i][j].rgbtGreen + image1[i][j + 1].rgbtGreen + image1[i + 1][j - 1].rgbtGreen + image1[i + 1][j].rgbtGreen + image1[i + 1][j + 1].rgbtGreen;
                blurBlue = image1[i][j - 1].rgbtBlue + image1[i][j].rgbtBlue + image1[i][j + 1].rgbtBlue + image1[i + 1][j - 1].rgbtBlue + image1[i + 1][j].rgbtBlue + image1[i + 1][j + 1].rgbtBlue;

                blurRed = round(blurRed / 6.0);
                blurGreen = round(blurGreen / 6.0);
                blurBlue = round(blurBlue / 6.0);
            }
            else if (i == 0 && j == (width - 1))
            {
                blurRed = image1[i][j - 1].rgbtRed + image1[i][j].rgbtRed + image1[i + 1][j - 1].rgbtRed + image1[i + 1][j].rgbtRed;
                blurGreen = image1[i][j - 1].rgbtGreen + image1[i][j].rgbtGreen + image1[i + 1][j - 1].rgbtGreen + image1[i + 1][j].rgbtGreen;
                blurBlue = image1[i][j - 1].rgbtBlue + image1[i][j].rgbtBlue + image1[i + 1][j - 1].rgbtBlue + image1[i + 1][j].rgbtBlue;

                blurRed = round(blurRed / 4.0);
                blurGreen = round(blurGreen / 4.0);
                blurBlue = round(blurBlue / 4.0);
            }
            else if (i != 0 && i < (height - 1) && j == 0)
            {
                blurRed = image1[i - 1][j].rgbtRed + image1[i - 1][j + 1].rgbtRed + image1[i][j].rgbtRed + image1[i][j + 1].rgbtRed + image1[i + 1][j].rgbtRed + image1[i + 1][j + 1].rgbtRed;
                blurGreen = image1[i - 1][j].rgbtGreen + image1[i - 1][j + 1].rgbtGreen + image1[i][j].rgbtGreen + image1[i][j + 1].rgbtGreen + image1[i + 1][j].rgbtGreen + image1[i + 1][j + 1].rgbtGreen;
                blurBlue = image1[i - 1][j].rgbtBlue + image1[i - 1][j + 1].rgbtBlue + image1[i][j].rgbtBlue + image1[i][j + 1].rgbtBlue + image1[i + 1][j].rgbtBlue + image1[i + 1][j + 1].rgbtBlue;

                blurRed = round(blurRed / 6.0);
                blurGreen = round(blurGreen / 6.0);
                blurBlue = round(blurBlue / 6.0);
            }
            else if (i != 0 && i < (height - 1) && j == (width - 1))
            {
                blurRed = image1[i - 1][j - 1].rgbtRed + image1[i - 1][j].rgbtRed + image1[i][j - 1].rgbtRed + image1[i][j].rgbtRed + image1[i + 1][j - 1].rgbtRed + image1[i + 1][j].rgbtRed;
                blurGreen = image1[i - 1][j - 1].rgbtGreen + image1[i - 1][j].rgbtGreen + image1[i][j - 1].rgbtGreen + image1[i][j].rgbtGreen + image1[i + 1][j - 1].rgbtGreen + image1[i + 1][j].rgbtGreen;
                blurBlue = image1[i - 1][j - 1].rgbtBlue + image1[i - 1][j].rgbtBlue + image1[i][j - 1].rgbtBlue + image1[i][j].rgbtBlue + image1[i + 1][j - 1].rgbtBlue + image1[i + 1][j].rgbtBlue;

                blurRed = round(blurRed / 6.0);
                blurGreen = round(blurGreen / 6.0);
                blurBlue = round(blurBlue / 6.0);
            }
            else if (i != 0 && i < (height - 1) && j != 0 && j < (width - 1))
            {
                blurRed = image1[i - 1][j - 1].rgbtRed + image1[i - 1][j].rgbtRed + image1[i - 1][j + 1].rgbtRed + image1[i][j - 1].rgbtRed + image1[i][j].rgbtRed + image1[i][j + 1].rgbtRed + image1[i + 1][j - 1].rgbtRed + image1[i + 1][j].rgbtRed + image1[i + 1][j + 1].rgbtRed;
                blurGreen = image1[i - 1][j - 1].rgbtGreen + image1[i - 1][j].rgbtGreen + image1[i - 1][j + 1].rgbtGreen + image1[i][j - 1].rgbtGreen + image1[i][j].rgbtGreen + image1[i][j + 1].rgbtGreen + image1[i + 1][j - 1].rgbtGreen + image1[i + 1][j].rgbtGreen + image1[i + 1][j + 1].rgbtGreen;
                blurBlue = image1[i - 1][j - 1].rgbtBlue + image1[i - 1][j].rgbtBlue + image1[i - 1][j + 1].rgbtBlue + image1[i][j - 1].rgbtBlue + image1[i][j].rgbtBlue + image1[i][j + 1].rgbtBlue + image1[i + 1][j - 1].rgbtBlue + image1[i + 1][j].rgbtBlue + image1[i + 1][j + 1].rgbtBlue;

                blurRed = round(blurRed / 9.0);
                blurGreen = round(blurGreen / 9.0);
                blurBlue = round(blurBlue / 9.0);
            }
            else if (i == (height - 1) && j == 0)
            {
                blurRed = image1[i - 1][j].rgbtRed + image1[i - 1][j + 1].rgbtRed + image1[i][j].rgbtRed + image1[i][j + 1].rgbtRed;
                blurGreen = image1[i - 1][j].rgbtGreen + image1[i - 1][j + 1].rgbtGreen + image1[i][j].rgbtGreen + image1[i][j + 1].rgbtGreen;
                blurBlue = image1[i - 1][j].rgbtBlue + image1[i - 1][j + 1].rgbtBlue + image1[i][j].rgbtBlue + image1[i][j + 1].rgbtBlue;

                blurRed = round(blurRed / 4.0);
                blurGreen = round(blurGreen / 4.0);
                blurBlue = round(blurBlue / 4.0);
            }
            else if (i == (height - 1) && j != 0 && j < (width - 1))
            {
                blurRed = image1[i - 1][j - 1].rgbtRed + image1[i - 1][j].rgbtRed + image1[i - 1][j + 1].rgbtRed + image1[i][j - 1].rgbtRed + image1[i][j].rgbtRed + image1[i][j + 1].rgbtRed;
                blurGreen = image1[i - 1][j - 1].rgbtGreen + image1[i - 1][j].rgbtGreen + image1[i - 1][j + 1].rgbtGreen + image1[i][j - 1].rgbtGreen + image1[i][j].rgbtGreen + image1[i][j + 1].rgbtGreen;
                blurBlue = image1[i - 1][j - 1].rgbtBlue + image1[i - 1][j].rgbtBlue + image1[i - 1][j + 1].rgbtBlue + image1[i][j - 1].rgbtBlue + image1[i][j].rgbtBlue + image1[i][j + 1].rgbtBlue;

                blurRed = round(blurRed / 6.0);
                blurGreen = round(blurGreen / 6.0);
                blurBlue = round(blurBlue / 6.0);
            }
            else if (i == (height - 1) && j == (width - 1))
            {
                blurRed = image1[i][j].rgbtRed + image1[i][j - 1].rgbtRed + image1[i - 1][j].rgbtRed + image1[i - 1][j - 1].rgbtRed;
                blurGreen = image1[i][j].rgbtGreen + image1[i][j - 1].rgbtGreen + image1[i - 1][j].rgbtGreen + image1[i - 1][j - 1].rgbtGreen;
                blurBlue = image1[i][j].rgbtBlue + image1[i][j - 1].rgbtBlue + image1[i - 1][j].rgbtBlue + image1[i - 1][j - 1].rgbtBlue;

                blurRed = round(blurRed / 4.0);
                blurGreen = round(blurGreen / 4.0);
                blurBlue = round(blurBlue / 4.0);
            }
            else
            {
                printf("we forgot something somehow");
            }
            image[i][j].rgbtRed = blurRed;
            image[i][j].rgbtGreen = blurGreen;
            image[i][j].rgbtBlue = blurBlue;
        }
    }
    return;
}