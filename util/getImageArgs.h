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

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>


void printCommandUsage(char executableName[]);
int processImageArgs(int argc, char *argv[], int* bitPtr, char imageFilename[]); 
int processHideImageArgs(int argc, char *argv[], int* bitPtr, char textFilename[], char imageFilename[]); 

#endif


