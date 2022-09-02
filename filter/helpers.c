#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE bucket[height][width];
    for(int i = 0; i < height; i++) //rows
    {
        for(int j = 0; j < width / 2; j++) //columns
        {
            bucket[i][j] = image[i][j];
            image[i][j] = image[i][width-j-1];
            image[i][width-j-1] = bucket[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE bucket[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            // corner pixels
            if(i == 0 && j == 0)
            {
                bucket[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i][j+1].rgbtBlue +
                                        image[i+1][j+1].rgbtBlue) / 4.00);
                bucket[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i][j+1].rgbtGreen +
                                         image[i+1][j+1].rgbtGreen) / 4.00);
                bucket[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i][j+1].rgbtRed +
                                       image[i+1][j+1].rgbtRed) / 4.00);
            }
            else if(i == 0 && j == (width - 1))
            {
                bucket[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i][j-1].rgbtBlue +
                                        image[i+1][j-1].rgbtBlue) / 4.00);
                bucket[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i][j-1].rgbtGreen +
                                         image[i+1][j-1].rgbtGreen) / 4.00);
                bucket[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i][j-1].rgbtRed +
                                       image[i+1][j-1].rgbtRed) / 4.00);
            }
            else if(i == (height - 1) && j == 0)
            {
                bucket[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j+1].rgbtBlue +
                                        image[i-1][j+1].rgbtBlue) / 4.00);
                bucket[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j+1].rgbtGreen +
                                         image[i-1][j+1].rgbtGreen) / 4.00);
                bucket[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i][j+1].rgbtRed +
                                       image[i-1][j+1].rgbtRed) / 4.00);
            }
            else if(i == (height - 1) && j == (width - 1))
            {
                bucket[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j-1].rgbtBlue +
                                        image[i-1][j-1].rgbtBlue) / 4.00);
                bucket[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j-1].rgbtGreen +
                                        image[i-1][j-1].rgbtGreen) / 4.00);
                bucket[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i][j-1].rgbtRed +
                                        image[i-1][j-1].rgbtRed) / 4.00);
            }
            // edge pixels
            else if(i == 0 && j > 0 && j < (width - 1))
            {
                bucket[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i][j+1].rgbtBlue +
                                        image[i][j-1].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue) / 6.00);
                bucket[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i][j+1].rgbtGreen +
                                         image[i][j-1].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen) / 6.00);
                bucket[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i][j+1].rgbtRed +
                                       image[i][j-1].rgbtRed + image[i+1][j+1].rgbtRed + image[i+1][j-1].rgbtRed) / 6.00);
            }
            else if(i == (height - 1) && j > 0 && j < (width - 1))
            {
                bucket[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j+1].rgbtBlue +
                                        image[i][j-1].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i-1][j-1].rgbtBlue) / 6.00);
                bucket[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j+1].rgbtGreen +
                                         image[i][j-1].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i-1][j-1].rgbtGreen) / 6.00);
                bucket[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i][j+1].rgbtRed +
                                       image[i][j-1].rgbtRed + image[i-1][j+1].rgbtRed + image[i-1][j-1].rgbtRed) / 6.00);
            }
            else if(j == 0 && i > 0 && i < (height - 1))
            {
                bucket[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i-1][j].rgbtBlue +
                                        image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i-1][j+1].rgbtBlue) / 6.00);
                bucket[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i-1][j].rgbtGreen +
                                         image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i-1][j+1].rgbtGreen) / 6.00);
                bucket[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i-1][j].rgbtRed +
                                       image[i][j+1].rgbtRed + image[i+1][j+1].rgbtRed + image[i-1][j+1].rgbtRed) / 6.00);
            }
            else if(j == (width - 1) && i > 0 && i < (height - 1))
            {
                bucket[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i-1][j].rgbtBlue +
                                        image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i-1][j-1].rgbtBlue) / 6.00);
                bucket[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i-1][j].rgbtGreen +
                                        image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i-1][j-1].rgbtGreen) / 6.00);
                bucket[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i-1][j].rgbtRed +
                                        image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed + image[i-1][j-1].rgbtRed) / 6.00);
            }
            // middle pixels
            else
            {
            bucket[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i-1][j].rgbtBlue +
                                    image[i][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j+1].rgbtBlue +
                                    image[i-1][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i-1][j-1].rgbtBlue) / 9.00);
            bucket[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i-1][j].rgbtGreen +
                                     image[i][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j+1].rgbtGreen +
                                     image[i-1][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i-1][j-1].rgbtGreen) / 9.00);
            bucket[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i-1][j].rgbtRed +
                                   image[i][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j+1].rgbtRed +
                                   image[i-1][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i-1][j-1].rgbtRed) / 9.00);
            }
        }
    }
    // copy blurred pixels from bucket back to image
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = bucket[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE Gx[height][width], Gy[height][width], G[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if (i <= 0 || j <= 0 || i >= (height - 1) || j >= (width - 1))
            {
                G[i][j].rgbtBlue = G[i][j].rgbtGreen = G[i][j].rgbtRed = 0;
            }
            else
            {
                Gx[i][j].rgbtBlue = (image[i][j+1].rgbtBlue * 2) - (image[i][j-1].rgbtBlue * 2) +
                                        image[i+1][j+1].rgbtBlue - image[i+1][j-1].rgbtBlue +
                                        image[i-1][j+1].rgbtBlue - image[i-1][j-1].rgbtBlue;
                Gx[i][j].rgbtGreen = (image[i][j+1].rgbtGreen * 2) - (image[i][j-1].rgbtGreen * 2) +
                                         image[i+1][j+1].rgbtGreen - image[i+1][j-1].rgbtGreen +
                                         image[i-1][j+1].rgbtGreen - image[i-1][j-1].rgbtGreen;
                Gx[i][j].rgbtRed = (image[i][j+1].rgbtRed * 2) - (image[i][j-1].rgbtRed * 2) +
                                       image[i+1][j+1].rgbtRed - image[i+1][j-1].rgbtRed +
                                       image[i-1][j+1].rgbtRed - image[i-1][j-1].rgbtRed;
                Gy[i][j].rgbtBlue = (image[i+1][j].rgbtBlue * 2) - (image[i-1][j].rgbtBlue * 2) +
                                        image[i+1][j+1].rgbtBlue - image[i-1][j+1].rgbtBlue +
                                        image[i+1][j-1].rgbtBlue - image[i-1][j-1].rgbtBlue;
                Gy[i][j].rgbtGreen = (image[i+1][j].rgbtGreen * 2) - (image[i-1][j].rgbtGreen * 2) +
                                        image[i+1][j+1].rgbtGreen - image[i-1][j+1].rgbtGreen +
                                        image[i+1][j-1].rgbtGreen - image[i-1][j-1].rgbtGreen;
                Gy[i][j].rgbtRed = (image[i+1][j].rgbtRed * 2) - (image[i-1][j].rgbtRed * 2) +
                                        image[i+1][j+1].rgbtRed - image[i-1][j+1].rgbtRed +
                                        image[i+1][j-1].rgbtRed - image[i-1][j-1].rgbtRed;

                G[i][j].rgbtBlue = round(sqrt((Gx[i][j].rgbtBlue^2) + (Gy[i][j].rgbtBlue^2)));
                G[i][j].rgbtGreen = round(sqrt((Gx[i][j].rgbtGreen^2) + (Gy[i][j].rgbtGreen^2)));
                G[i][j].rgbtRed = round(sqrt((Gx[i][j].rgbtRed^2) + (Gy[i][j].rgbtRed^2)));
            }
        }
    }
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = G[i][j];
        }
    }
    return;
}
