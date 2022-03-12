#include <stdio.h>
#include <stdlib.h>

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
    // Declare filters, check command-line arguments
    char *filters = "rbg";
    
    char filter = getopt(argc, argv, filters);
    if (filter == '?'){
        fprintf(stderr, "\n\tInvalid filter.\n\tUsage: ./colourfilter [flag] [input folder]\n\t-r = red\n\t-b = blue\n\t-g = green\n\n");
        return 1;
    }
    if (getopt(argc, argv, filters) != -1){
        fprintf(stderr, "Only one filter may be used.\n");
        return 2;
    }

    // Open input folder, check CLA
    char *foldername = argv[2];

    DIR *infolder = opendir(foldername);
    if (infolder == NULL) {
        fprintf(stderr,"Unable to read folder '%s'\n", foldername); // use perror? TODO
        return 3;
    }

    // Set up output folder
    char outfoldername[10];
    sprintf(outfoldername, "OUTPUT_%c", (filter - 32));
    mkdir(outfoldername, S_IRWXU);

        // TODO: Check CTRL+F "sprintf", change to snprintf for buffer overflow contingency
 
    // input = input file; outpath = output file's filepath
    struct dirent *input;
    char outpath[PATH_MAX];

    // Readdir loop accesses input folder file by file
    while((input = readdir(infolder)) != NULL) 
    {
        // 1: Check input filepath is correct, 2: write to char "path", 3: read from input image using path
        char path[PATH_MAX];
        if (!strcmp(input->d_name, ".") || !strcmp(input->d_name, "..")) {
            continue;
        }
        if ((size_t)snprintf(path, sizeof path, "%s/%s", foldername, input->d_name) >= sizeof(path)) {
            fprintf(stderr, "Filename too long: %s/%s\n", foldername, input->d_name); 
            continue;
        }
        FILE *imgin = fopen(path, "rb");

        // 1: Create output filename, 2: Open output image to write
        char outputname[strlen(input->d_name) + 2];
        sprintf(outputname, "%c_%s", ((int) filter - 32), input->d_name);

        if ((size_t)snprintf(outpath, sizeof outpath, "%s/%s", outfoldername, outputname) >= sizeof(outpath)) {
            fprintf(stderr, "Filename too long: %s/%s\n", outfoldername, outputname);
            continue;
        }
        FILE *imgout = fopen(outpath, "wb");


        // Check input can be read & have sufficient memory to open output
        if (imgin == NULL){
            fprintf(stderr, "Could not open %s.\n", path);
            return 4;
            }
        if (imgout == NULL){
            fclose(imgin);
            fprintf(stderr, "Could not create images.\n");
            return 5;
        }
    
        // 1. Declare & read bitmap-specific fileheadhers, 2. Ensure input image's header data corresponds    
        BITMAPFILEHEADER bf;
        fread(&bf, sizeof(BITMAPFILEHEADER), 1, imgin);

        BITMAPINFOHEADER bi;
        fread(&bi, sizeof(BITMAPINFOHEADER), 1, imgin);

        if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
            bi.biBitCount != 24 || bi.biCompression != 0)
        {
            fclose(imgout);
            fclose(imgin);
            fprintf(stderr, "Unsupported file format.\n File must be an uncompressed, 24-bit BMP 4.0\n");
            return 6;
        } 

        // Get dimensions of image input per input image's buffer
        int height = abs(bi.biHeight);
        int width = bi.biWidth;

        // 1. Allocate memory for array-struct holding input image's rgb values, 2. Check there's enough memory to do so
        RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
        if (image == NULL)
        {
            fprintf(stderr, "Not enough memory to store image.\n");
            fclose(imgout);
            fclose(imgin);
            return 7;
        }

        // 1. Determine padding for scanlines, 2: Iterate over input file's scanlines
        int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;
        for (int i = 0; i < height; i++)
        {
            // 1: Read row into pixel array, 2: Skip over padding
            fread(image[i], sizeof(RGBTRIPLE), width, imgin);
            fseek(imgin, padding, SEEK_CUR);
        }

        // Filter image based on flag in CLAs
        switch(filter)  {
            case 'r':   red(height, width, image);      break;
            case 'b':   blue(height, width, image);     break;
            case 'g':   green(height, width, image);    break;
        }

        // 1. Write header files to outfile, 2. Write edited image to outfile
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, imgout);
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, imgout);
        
        for (int i = 0; i < height; i++)
        {
            // 1. Write row, 2. Write padding at end of row
            fwrite(image[i], sizeof(RGBTRIPLE), width, imgout);

            for (int k = 0; k < padding; k++){
                fputc(0x00, imgout);
            }
        }

        fclose(imgin);
        fclose(imgout);
        free(image);
    }
}