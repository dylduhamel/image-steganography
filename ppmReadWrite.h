/**
 * @author Nirre Pluf {@literal pluf@wfu.edu}
 * @date Feb. 17, 2022
 * @assignment Lab 4
 * @course CSC 250
 *
 * header files for reading and writing PPM files
 **/

#ifndef PPM_READ_WRITE
#define PPM_READ_WRITE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define RGB_COMPONENT_COLOR 255


/**
 * struct to store a single RGB pixel
 */
struct Pixel {
    unsigned char red;    /* red component */
    unsigned char green;  /* green component */
    unsigned char blue;   /* blue component */
};


/**
 * struct to store a PPM image
 */
struct Image {
    int width;           /* image width (pixels) */
    int height;          /* image height (pixels) */
    struct Pixel *data;  /* list of Pixels for the image */
};


int readImage(struct Image **img, char filename[]);
int writeImage(char filename[], struct Image *img);
void changeColor(struct Image *img);
void rgbPixels(struct Image *img);

#endif


