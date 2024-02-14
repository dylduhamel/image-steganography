/**
 * @author Nirre Pluf {@literal pluf@wfu.edu}
 * @date Feb. 27, 2022
 * @assignment Lab 5
 * @course CSC 250
 *
 * header files for parsing the command line arguments
 *
 * CHANGES:
 *   added processHideImageArgs
 *
 **/

#ifndef PROC_ARGS
#define PROC_ARGS

#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void printCommandUsage(char executableName[]);
int processImageArgs(int argc, char *argv[], int *bitPtr, char imageFilename[]);
int processHideImageArgs(int argc, char *argv[], int *bitPtr,
                         char textFilename[], char imageFilename[]);

#endif
