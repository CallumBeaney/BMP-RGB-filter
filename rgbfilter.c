#include <stdio.h>
#include <stdlib.h>
//#include <stdint.h>

// For reading command line args
#include "helpers.h"
#include <getopt.h> 

// For handling folders and filenames
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h> 
#include <string.h>

const int PATH_MAX = 260;

int main(int argc, char *argv[])
{
    // First, declare filters and check command line for corresponding filter flag e.g. -r
    char *filters = "rbg";

    char filter = getopt(argc, argv, filters);
    if (filter == '?') {
        printf("\n\tInvalid filter.\n\tUsage: ./colourfilter [flag] [input folder]\n\t-r = red\n\t-b = blue\n\t-g = green\n\n");
        return 1;
    }
    if (getopt(argc, argv, filters) != -1) {
        printf("Only one filter may be used.\n");
        return 2;
    }

    // Open folder containing images to be converted specified in user's command-line input & check for errors
    char *foldername = argv[2];
    DIR *infolder = opendir(foldername);

    if (infolder == NULL) {
        //fprintf(stderr,"Unable to read folder %s\n", infolder); // use perror? TODO
        printf("Unable to read folder.\n");
        return 3;
    }
    
    // Declare variables for reading & handling input files
    struct dirent *input;
    int counter = 0;
    char name[10];

    // READDIR accesses each file in input folder 1 by 1 until end
    while((input = readdir(infolder)) != NULL) 
    {
        // Check the filepath to the file in the input folder is correct, and write it to char "path"
        char path[PATH_MAX];
        if (!strcmp(input->d_name, ".") || !strcmp(input->d_name, "..")) {
            continue;
        }
        if ((size_t)snprintf(path, sizeof path, "%s/%s", foldername, input->d_name) >= sizeof(path)) {
            printf("Filename too long: %s/%s\n", foldername, input->d_name);
            continue;
        }
        
        // Set up input image file to point to "path", assign name with an incrementing counter, and read/write to binary 
        sprintf(name, "%c_%03i.bmp", ((int) filter - 32), counter);
        FILE *imgin = fopen(path, "rb");
        FILE *imgout = fopen(name, "wb");
        
        // 1. Ensure input image file can be read, 2: Ensure output file can be made
        if (imgin == NULL) {
            printf("Could not open %s.\n", path);
            return 4;
        }
        if (imgout == NULL) {
            fclose(imgin);
            printf("Could not create images.\n");
            return 5;
        }
    
        // Declare & read bitmap-specific fileheadhers     
        BITMAPFILEHEADER bf;
        fread(&bf, sizeof(BITMAPFILEHEADER), 1, imgin);

        BITMAPINFOHEADER bi;
        fread(&bi, sizeof(BITMAPINFOHEADER), 1, imgin);

        // Ensure input image being read from folder == 24-bit UNCOMPRESSED BMP 4.0
        if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
            bi.biBitCount != 24 || bi.biCompression != 0)
        {
            fclose(imgout);
            fclose(imgin);
            printf("Unsupported file format.\n File must be an uncompressed, 24-bit BMP 4.0\n");
            return 6;
        } 

        // Get dimensions from input image
        int height = abs(bi.biHeight);
        int width = bi.biWidth;

        // 1. Allocate memory for array-struct holding input image's rgb values, 2. Check there's enough memory to do so
        RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
        if (image == NULL)
        {
            printf("Not enough memory to store image.\n");
            fclose(imgout);
            fclose(imgin);
            return 7;
        }

        // Determine padding for scanlines
        int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

        // Iterate over input file's scanlines
        for (int i = 0; i < height; i++)
        {
            // 1: Read row into pixel array, 2: Skip over padding
            fread(image[i], sizeof(RGBTRIPLE), width, imgin);
            fseek(imgin, padding, SEEK_CUR);
        }

        // FILTER IMAGE BASED ON CMD-LINE FLAG
        switch(filter)  {
            case 'r':
                red(height, width, image);  // RED
                break;
            case 'b':
                blue(height, width, image); // BLUE
                break;
            case 'g':
                green(height, width, image); // GREEN
                break;
        }

        // Write outfile's ↓
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, imgout);

        // Write outfile's ↓
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, imgout);

        // Write new pixels to outfile
        for (int i = 0; i < height; i++)
        {
            // Write row to outfile
            fwrite(image[i], sizeof(RGBTRIPLE), width, imgout);

            // Write padding at end of row
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, imgout);
            }
        }

        // Close files & free memory, increment counter for next file's filename
        fclose(imgin);
        fclose(imgout);
        free(image);
        counter++;
    }
}