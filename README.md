ABOUT THIS PROGRAM

    This program goes through a folder of BMPs files and outputs each with a colour filter applied.
    It is being written for a WIP photography project; the colour filter is written to look dark & somewhat "lofi".

USAGE

    User-inputted command line argument: ./program-name (command-line flag) [input folder name]
        e.g. ./rgbfilter -r testimages
    
    DEBUGGING NOTES:
    1. The BMPs must be 24-bit, uncompressed BMP 4.0s with no colour profile information recorded.
    2. The headers in these files can be temperamental, even being changed by being opened in Preview and then closed without saving; to troubleshoot, open an image editor and re-export with the required settings. 
    
        DEBUG FILE HEADERS:
        printf("%s\n", input->d_name);
        printf("%X v bf.bfType 0x4d42 \n %i v bfOffBits 54\n %i v bi.biSize 40\n %i v bi.biBitCount 24\n %i v bi.biCompression 0\n\n", bf.bfType, bf.bfOffBits, bi.biSize, bi.biBitCount, bi.biCompression);

    3. The input folder must be inside the directory.


ACKNOWLEDGMENTS:

    1. Bitmap file handling adapted from a PSET I completed for the Harvard CS50 course: https://cs50.harvard.edu/x/2022/psets/4/filter/less/
    2. Learned DIRENT.H with the UNIX specification: https://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html
    3. Learned MKDIR from: https://pubs.opengroup.org/onlinepubs/009695299/functions/mkdir.html
    4. Received debugging advice on DIRENT & MKDIR from StackOverflow.

TO DO:

    - Improve gradation in higher luminosity values while maintaining deep filter colour
    - Abstract greyscale conversion stage in helpers.c 
    - Optional 4th argv to allow relative output folder path
    - RE: instances of "sprintf" - change to snprintf for buffer overflow contingency


Callum Beaney
23日03月2022年
