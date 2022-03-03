/**
 * This program hides a message in a PPM file using LSb (using b bits), the new image (with LSb
 * message) will be called *_hidden.ppm (old file name with ".ppm" replaced with "_hidden.ppm"),
 * If successful, the program will display the number of characters in the message and the number 
 * of pixels used (to store the message). The number of LSb usedi, message file, and PPM image 
 * file name are provided using command line arguments. If the arguments are  incorrect, the 
 * program will exit and provide an error message.
 *
 * Note:
 *   Requires getImageArgs.h (.c) and ppmReadWrite.h (.c)
 *
 * Compile:
 *   gcc -ansi -pedantic -Wall lab5.c getImageArgs.c ppmReadWrite.c
 *
 * @author Your Name Here {@literal <pluf@wfu.edu>}
 * @date Feb. 27, 2022
 * @assignment Lab 5
 * @course CSC 250
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppmReadWrite.h"
#include "getImageArgs.h"


int hideMessage(struct Image *img, int bit, char textFilename[]);  
void printBits(unsigned char x);


int main(int argc, char *argv[])
{
    struct Image *img = NULL;
    char textFilename[20];
    char orgImageFilename[20] = {'\0'};
    char newImageFilename[20] = {'\0'};
    int bit;
    int argsOk = 0;
    int fileOk = 0;

    argsOk = processHideImageArgs(argc, argv, &bit, textFilename, orgImageFilename); 
    if(!argsOk) 
        return 1;

    fileOk = readImage(&img, orgImageFilename);
    if(!fileOk)  
        return 1;

    hideMessage(img, bit, textFilename);

    /* TODO: need to set newImageFilename */ 
    fileOk = writeImage(newImageFilename, img);
    if(!fileOk) {
        if(img) free(img);  
        return 1;
    }  
    /* this print in main is OK, it is AJ certified */
    /* but NO other prints in main are allowed      */
    printf("image saved as %s \n", newImageFilename);  

    if(img) free(img);  

    return 0;
}



int hideMessage(struct Image *img, int bit, char textFilename[]) {

    return 1;
}


void printBits(unsigned char x) {
    int value = x;
    char *bits;
    int i = 0;
    bits = malloc((size_t) (sizeof(x)*8 + 1));
    for(i = 0; i < sizeof(x)*8; i++) {
        bits[sizeof(x)*8 - i - 1] = (char) ((value & 0x1) + 48);
        value = value >> 1;
    }
    bits[sizeof(x)*8] = '\0';
    printf("%x(%s)\n", x, bits);
    free(bits);
}


