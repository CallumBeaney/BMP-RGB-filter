#include "helpers.h"
#include <math.h>
#include <stdio.h>

void red(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int OR = image[i][j].rgbtRed;
            int OG = image[i][j].rgbtGreen;
            int OB = image[i][j].rgbtBlue;

            float new = round((OR + OG + OB) / 3.0);

            if (new < 80) // if low
            {
                image[i][j].rgbtRed     = new;
                image[i][j].rgbtGreen   = new;
                image[i][j].rgbtBlue    = new; 
            } 
            if (new > 170) // if high
            {
                image[i][j].rgbtRed     = new;
                image[i][j].rgbtGreen   = (int) new * 0.60;
                image[i][j].rgbtBlue    = (int) new * 0.60;
            }
            else // mid-range
            {
                image[i][j].rgbtRed     = new;
                image[i][j].rgbtGreen   = (int) new * 0.30;
                image[i][j].rgbtBlue    = (int) new * 0.30;
            }
        }
    }
    return;
}

void blue(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int OR = image[i][j].rgbtRed;
            int OG = image[i][j].rgbtGreen;
            int OB = image[i][j].rgbtBlue;

            float new = round((OR + OG + OB) / 3.0);

            if (new < 80) // if low
            {
                image[i][j].rgbtRed     = new;
                image[i][j].rgbtGreen   = new;
                image[i][j].rgbtBlue    = new; 
            } 
            if (new > 170) // if high
            {
                image[i][j].rgbtRed     = (int) new * 0.60;
                image[i][j].rgbtGreen   = (int) new * 0.60;
                image[i][j].rgbtBlue    = new;
            }
            else // mid-range
            {
                image[i][j].rgbtRed     = (int) new * 0.30;
                image[i][j].rgbtGreen   = (int) new * 0.30;
                image[i][j].rgbtBlue    = new;
            }
        }
    }
    return;
}

void green(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int OR = image[i][j].rgbtRed;
            int OG = image[i][j].rgbtGreen;
            int OB = image[i][j].rgbtBlue;

            float new = round((OR + OG + OB) / 3.0);

            if (new < 80) // if low
            {
                image[i][j].rgbtRed     = new;
                image[i][j].rgbtGreen   = new;
                image[i][j].rgbtBlue    = new; 
            } 
            if (new > 170) // if high
            {
                image[i][j].rgbtRed     = (int) new * 0.60;
                image[i][j].rgbtGreen   = new;
                image[i][j].rgbtBlue    = (int) new * 0.60;
            }
            else // mid-range
            {
                image[i][j].rgbtRed     = (int) new * 0.30;
                image[i][j].rgbtGreen   = new;
                image[i][j].rgbtBlue    = (int) new * 0.30;
            }
        }
    }
    return;
}
