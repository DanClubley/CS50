#include "helpers.h"
#include <stdio.h>
#include <math.h>

const int KERNEL_GX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
const int KERNEL_GY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

RGBTRIPLE box_blur(int x, int y, int height, int width, RGBTRIPLE image[height][width]);
RGBTRIPLE sobel_operator(int x, int y, int height, int width, RGBTRIPLE image[height][width]);
int sobel_value(int gx, int gy);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int rgbAverage;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rgbAverage = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0f);
            image[i][j].rgbtRed = rgbAverage;
            image[i][j].rgbtGreen = rgbAverage;
            image[i][j].rgbtBlue = rgbAverage;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE reflected[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            reflected[i][width - j - 1] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = reflected[i][j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred[height][width];

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            blurred[y][x] = box_blur(x, y, height, width, image);
        }
    }

    // Replace image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blurred[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edged[height][width];

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            edged[y][x] = sobel_operator(x, y, height, width, image);
        }
    }

    // Replace image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = edged[i][j];
        }
    }

    return;
}

RGBTRIPLE box_blur(int x, int y, int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE box_blur;

    float n = 0;
    int rgb[] = {0, 0, 0};

    for (int i = y - 1; i < y + 2; i++)
    {
        for (int j = x - 1; j < x + 2; j++)
        {
            if (i >= 0 && i < height && j >= 0 && j < width)
            {
                n++;
                rgb[0] += image[i][j].rgbtRed;
                rgb[1] += image[i][j].rgbtGreen;
                rgb[2] += image[i][j].rgbtBlue;
            }
        }
    }
    box_blur.rgbtRed = round(rgb[0] / n);
    box_blur.rgbtGreen = round(rgb[1] / n);
    box_blur.rgbtBlue = round(rgb[2] / n);

    return box_blur;
}

RGBTRIPLE sobel_operator(int x, int y, int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE sobel_operator;

    int rgb_gx[] = {0, 0, 0};
    int rgb_gy[] = {0, 0, 0};

    for (int i = y - 1, a = 0; i < y + 2; i++, a++)
    {
        for (int j = x - 1, b = 0; j < x + 2; j++, b++)
        {
            if (i >= 0 && i < height && j >= 0 && j < width)
            {
                rgb_gx[0] += image[i][j].rgbtRed * KERNEL_GX[a][b];
                rgb_gx[1] += image[i][j].rgbtGreen * KERNEL_GX[a][b];
                rgb_gx[2] += image[i][j].rgbtBlue * KERNEL_GX[a][b];

                rgb_gy[0] += image[i][j].rgbtRed * KERNEL_GY[a][b];
                rgb_gy[1] += image[i][j].rgbtGreen  * KERNEL_GY[a][b];
                rgb_gy[2] += image[i][j].rgbtBlue * KERNEL_GY[a][b];
            }
        }
    }

    sobel_operator.rgbtRed = sobel_value(rgb_gx[0], rgb_gy[0]);
    sobel_operator.rgbtGreen = sobel_value(rgb_gx[1], rgb_gy[1]);
    sobel_operator.rgbtBlue = sobel_value(rgb_gx[2], rgb_gy[2]);

    return sobel_operator;
}

int sobel_value(int gx, int gy)
{
    int sobel_value = round(pow((pow(gx, 2) + pow(gy, 2)), 0.5f));

    if (sobel_value > 255)
    {
        sobel_value = 255;
    }

    return sobel_value;
}
