ABOUT THIS PROGRAM

    This program goes through a folder of BMPs files and outputs each with a colour filter applied.
    It is being written for a WIP photography project; the colour filter is written to look dark & somewhat "lofi".

USAGE

    User-inputted command line argument: ./program-name (command-line flag) [input folder name]
        e.g. ./rgbfilter -r testimages
    
    DEBUGGING NOTES:
    1. The BMPs must be 24-bit, uncompressed BMP 4.0s with no colour profile information recorded.
    2. The headers in these files can be temperamental, even being changed by being opened in Preview and then closed without saving; to troubleshoot, open an image editor and re-export with the required settings. 
    3. The input folder must be inside the directory.

ACKNOWLEDGMENTS:

    1. Bitmap file handling adapted from a PSET I completed for the Harvard CS50 course: https://cs50.harvard.edu/x/2022/psets/4/filter/less/
    2. Learned DIRENT.H with the UNIX specification: https://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html
    3. Learned MKDIR from: https://pubs.opengroup.org/onlinepubs/009695299/functions/mkdir.html
    4. Received debugging advice on DIRENT & MKDIR from StackOverflow.

TO DO:

    - Check CTRL+F "sprintf", change to snprintf for buffer overflow contingency
    - Fix error condition for filename too long & confirm input path syntax has no potential bugs
    - Improve gradation in higher luminosity values while maintaining deep filter colour
    - Abstract greyscale conversion stage in helpers.c
    - Allow the output folder's path to be relative

Callum Beaney
12日03月2022年