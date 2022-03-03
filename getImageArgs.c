/**
 * @author Nirre Pluf {@literal pluf@wfu.edu}
 * @date Feb. 27, 2022
 * @assignment Lab 5
 * @course CSC 250
 *
 * CHANGES:
 *   added processHideImageArgs
 *
 * source files for parsing the command line arguments
 **/   

#include "getImageArgs.h"

/**
 *  function processes the command line arguments using getopt()
 *  for use with hiding message
 *
 *  function returns 1 if the arguments are "correct", 0 otherwise
 *
 *  argc - number of command line arguments
 *  argv - list of command line arguments (list of C-strings)
 *  bitPtr - pointer to integer, number of LSB bits (1, 2, or 4)
 *  textFilename - pointer to the filename that contains the text to hide 
 *  imageFilename - pointer to the filename that will be encrypted or decrypted 
 */
int processHideImageArgs(int argc, char *argv[], int* bitPtr, char textFilename[], char imageFilename[]) {
    int opt;
    int gotBit = 0;

    while ((opt = getopt(argc, argv, "b:")) != -1) {
        switch (opt) {
        case 'b':
            *bitPtr = atoi(optarg);
            gotBit = *bitPtr == 1 || *bitPtr == 2 || *bitPtr == 4;
            break;
        default: 
            printCommandUsage(argv[0]);
            return 0;
        }
    }

    if(!gotBit || (optind + 1) >= argc){
        printCommandUsage(argv[0]);
        return 0;
    }

    strcpy(textFilename, argv[optind]);
    strcpy(imageFilename, argv[optind + 1]);

    /* printf("b: %d, txt_f: [%s], img_f: [%s] \n", *bitPtr, textFilename, imageFilename); */  

    return 1;
}


/**
 *  function processes the command line arguments using getopt()
 *  for use recovering message
 *
 *  function returns 1 if the arguments are "correct", 0 otherwise
 *
 *  argc - number of command line arguments
 *  argv - list of command line arguments (list of C-strings)
 *  bitPtr - pointer to integer, number of LSB bits (1, 2, or 4)
 *  imageFilename - pointer to the filename that will be encrypted or decrypted 
 */
int processImageArgs(int argc, char *argv[], int* bitPtr, char imageFilename[]) {
    int opt;
    int gotBit = 0;

    while ((opt = getopt(argc, argv, "b:")) != -1) {
        switch (opt) {
        case 'b':
            *bitPtr = atoi(optarg);
            gotBit = *bitPtr == 1 || *bitPtr == 2 || *bitPtr == 4;
            break;
        default: 
            printCommandUsage(argv[0]);
            return 0;
        }
    }

    /* printf("b: %d, img_f: [%s] \n", *bitPtr, imageFileName); */  

    if(!gotBit || optind >= argc){
        printCommandUsage(argv[0]);
        return 0;
    }

    strcpy(imageFilename, argv[optind]);

    return 1;
}


/**
 *  function to print a useful help message
 */
void printCommandUsage(char executableName[]) {
    fprintf(stderr, "Usage: %s -b bit textFilename ppmImageFilename \n", executableName);
    fprintf(stderr, " -b number of bits per color component to decode (1, 2, or 4)\n");
}


