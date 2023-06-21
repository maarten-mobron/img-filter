# Image Filtering with BMP Files

## Description
This code implements a simple image filtering program that works with BMP (Bitmap) files. It applies various filters, such as blur, edges, grayscale, and reflection, to the input image file and saves the filtered result to an output file.

## Function Explanation
1. `main()`: The main function is the entry point of the program. It handles the command-line arguments, opens the input and output files, reads the BMP file headers, allocates memory for the image, applies the specified filter to the image, and writes the modified image to the output file.

2. `getopt()`: This function is part of the `<getopt.h>` library and is used for parsing command-line arguments. It retrieves the specified filter flag from the command-line arguments.

3. Filter Functions:
   - `blur()`: This function applies a blurring effect to the image by averaging the RGB values of neighboring pixels.
   - `edges()`: This function detects edges in the image using the Sobel operator.
   - `grayscale()`: This function converts the image to grayscale by setting the RGB values of each pixel to the average of its original RGB values.
   - `reflect()`: This function reflects the image horizontally.

## Usage Explanation
To use this code, follow these steps:

1. Ensure you have the necessary libraries installed: `<getopt.h>`, `<stdio.h>`, `<stdlib.h>`, `<bmp.h>` and `<math.h>`.

2. Compile the code using a C compiler, such as GCC, with the necessary flags and include files.

3. Run the compiled executable from the command line, providing the appropriate arguments:
./filter [flag] `infile` `outfile`

- `[flag]`: Specify the filter to be applied. Use one of the following options:
  - `b`: Blur filter
  - `e`: Edges filter
  - `g`: Grayscale filter
  - `r`: Reflect filter

- `infile`: The input BMP file to be filtered.

- `outfile`: The output BMP file to store the filtered result.

4. The program will read the input file, apply the specified filter, and save the filtered image to the output file.

5. Check the output file to view the filtered image.

## Image Filters Description

Here's a brief description of each filter:

### Grayscale

The grayscale filter converts an image to grayscale by averaging the RGB values of each pixel and setting all three channels (red, green, blue) to the average value. It iterates over each pixel in the image, calculates the average value, and updates the RGB values of the pixel to the average.

### Reflect

The reflect filter horizontally reflects the image. It achieves this by swapping each pixel with its corresponding pixel on the opposite side of the image along the vertical axis. It iterates over each row of pixels in the image and swaps the pixels symmetrically from left to right.

### Blur

The blur filter applies a blurring effect to the image. It does this by taking the average of the color values of each pixel and its surrounding pixels. It creates a new buffer to store the modified image. It then iterates over each pixel in the image and computes the average color values of the pixel and its surrounding 8 pixels (3x3 kernel). The average values are then stored in the buffer. Finally, the contents of the buffer are copied back to the original image.

### Edges

The edges filter detects edges in the image using the Sobel operator. It computes the gradient of the image intensity at each pixel to highlight areas of rapid intensity change, which typically correspond to edges. It uses two 3x3 convolution matrices, one for the horizontal gradient (gx) and one for the vertical gradient (gy). It convolves the matrices with the image by multiplying the corresponding matrix elements with the color values of the surrounding pixels and summing the results. The magnitude of the gradients (gx and gy) are then calculated, and the result is stored in a buffer. The buffer is copied back to the original image after ensuring that the color values are within the valid range.

## License

You are free to use it for any purpose.
