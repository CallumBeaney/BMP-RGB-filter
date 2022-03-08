ABOUT THIS PROGRAM

    This program is being written as part of a work-in-progress photography project, where different batches of images are to be processed with a custom RGB colour filter.
    For the project in question, the colour filter has been written for high-contrast images, particularly those shot at night with a flash.

OUTLINE

    1. User inputs command line arguments: ./program-name (command-line flag) [input folder name] *
    2. The program checks the command line arguments, and then opens the input folder and tries to read a file in the folder. **
    3. It checks that the file can be accessed, opens it, changes its colour values according to the (flag) argument, and saves it.
    4. It does (3) to each following file until there are no files left to be processed inside the folder.

    *  The input folder must be inside the directory.
    ** All input images must be of type _24-bit UNCOMPRESSED BMP 4.0_ with no colour profile information (for now).

ACKNOWLEDGMENTS:

    1. Bitmap file handling adapted from a PSET I completed for the Harvard CS50 course: https://cs50.harvard.edu/x/2022/psets/4/filter/less/
    2. Learned DIRENT.H with the UNIX specification: https://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html
    3. Learned MKDIR from: https://www.delftstack.com/howto/c/mkdir-in-c/
    4. Received debugging advice on DIRENT & MKDIR from StackOverflow.

TO DO:

    - Force consistent fileread order for "while((input = readdir(infolder)) != NULL)" at line 48
    - Implement output folder creation and path set based on additional command line argument
    - Apply fprintf/perror as appropriate to error checks
    - Tailor filter functions to final project images

