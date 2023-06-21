#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];

            // calculate average of RGB values
            BYTE average = round((pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3.0);

            // set RGB values to average
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
    int opesite;
    for (int i = 0; i < height; i++)
    {
        opesite = width - 1;
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE *pixel1 = &image[i][j];
            RGBTRIPLE *pixel2 = &image[i][opesite];
            RGBTRIPLE temp = *pixel1;
            *pixel1 = *pixel2;
            *pixel2 = temp;
            opesite--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, k, l;
    int red, green, blue;
    BYTE average_red, average_green, average_blue;
    float surrounding_pixels;

    // create a buffer to store the new image data
    RGBTRIPLE buffer[height][width];

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            // initialize the color sums and surrounding pixel count
            red = green = blue = 0;
            surrounding_pixels = 0;

            // iterate over the surrounding pixels
            for (k = -1; k <= 1; k++)
            {
                for (l = -1; l <= 1; l++)
                {
                    // compute the row and column indices of the surrounding pixel
                    int row = i + k;
                    int col = j + l;

                    // check if the surrounding pixel is within the image boundaries
                    if (row >= 0 && row < height && col >= 0 && col < width)
                    {
                        surrounding_pixels++;
                        // add the color values of the surrounding pixel to the sums
                        red += image[row][col].rgbtRed;
                        green += image[row][col].rgbtGreen;
                        blue += image[row][col].rgbtBlue;
                    }
                }
            }

            // compute the average color values
            average_red = round(red / surrounding_pixels);
            average_green = round(green / surrounding_pixels);
            average_blue = round(blue / surrounding_pixels);

            // store the new color values in the buffer
            buffer[i][j].rgbtRed = average_red;
            buffer[i][j].rgbtGreen = average_green;
            buffer[i][j].rgbtBlue = average_blue;
        }
    }

    // copy the contents of the buffer back to the original image array
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j] = buffer[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, k, l;
    int red, green, blue;
    float gx_red, gx_green, gx_blue;
    float gy_red, gy_green, gy_blue;

    int conv_matrix_gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int conv_matrix_gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // create a buffer to store the new image data
    RGBTRIPLE buffer[height][width];


    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            // initialize the color sums
            red = green = blue = 0;

            // initialize gx and gy
            gx_red = gx_green = gx_blue = 0;
            gy_red = gy_green = gy_blue = 0;

            // iterate over the surrounding pixels
            for (k = -1; k <= 1; k++)
            {

                for (l = -1; l <= 1; l++)
                {
                    // compute the row and column indices of the surrounding pixel
                    int row = i + k;
                    int col = j + l;

                    // check if the surrounding pixel is within the image boundaries
                    if (row >= 0 && row < height && col >= 0 && col < width)
                    {
                        // gx
                        gx_red += image[row][col].rgbtRed * conv_matrix_gx[k + 1][l + 1];
                        gx_green += image[row][col].rgbtGreen * conv_matrix_gx[k + 1][l + 1];
                        gx_blue += image[row][col].rgbtBlue * conv_matrix_gx[k + 1][l + 1];
                        // gy
                        gy_red += image[row][col].rgbtRed * conv_matrix_gy[k + 1][l + 1];
                        gy_green += image[row][col].rgbtGreen * conv_matrix_gy[k + 1][l + 1];
                        gy_blue +=  image[row][col].rgbtBlue * conv_matrix_gy[k + 1][l + 1];
                    }

                }
            }

            // compute the average color values
            red = round(sqrt(gx_red * gx_red + gy_red * gy_red));
            green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            blue = round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));

            // ensure that color values are within the valid range
            if (red > 255)
            {
                red = 255;
            }
            else if (red < 0)
            {
                red = 0;
            }
            if (green > 255)
            {
                green = 255;
            }
            else if (green < 0)
            {
                green = 0;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            else if (blue < 0)
            {
                blue = 0;
            }

            buffer[i][j].rgbtRed = (int)red;
            buffer[i][j].rgbtGreen = (int)green;
            buffer[i][j].rgbtBlue = (int)blue;
        }
    }

    // copy the contents of the buffer back to the original image array
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j] = buffer[i][j];
        }
    }

    return;
}
