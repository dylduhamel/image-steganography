/**
 * @author Nirre Pluf {@literal pluf@wfu.edu}
 * @date Feb. 17, 2022
 * @assignment Lab 4
 * @course CSC 250
 *
 * functions for reading and writing PPM files
 **/

#include "ppmReadWrite.h"


/**
 *  reads PPM image data and returns information in ia list of Image structs
 *
 *  img - pointer to a dynamic list of Image structs (data from PPM file)
 *  file_name - C-string, name of the PPM file
 *
 *  returns 1 if successful, 0 otherwise
 */
int readImage(struct Image **img, char filename[])
{
    char buffer[16];     /* buffer used to read data from file */
    FILE *filePtr;       /* PPM file pointer */
    int ch;              /* temporary character (byte) read from file */
    int rgbCompColor;    /* component color */  

    /* open PPM file for reading */
    filePtr = fopen(filename, "rb");
    if(!filePtr) {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        return 0;
    }

    /* read image format */
    if(!fgets(buffer, sizeof(buffer), filePtr)) {
        perror(filename);
        return 0;
    }

    /* check the image format */
    if(buffer[0] != 'P' || buffer[1] != '6') {
        fprintf(stderr, "Invalid image format (must be 'P6')\n");
        return 0;
    }

    /* alloc memory form image */
    (*img) = (struct Image *) malloc(sizeof(struct Image));
    if(!(*img)) {
        fprintf(stderr, "Unable to allocate memory\n");
        return 0;
    }

    /* check for comments */
    ch = getc(filePtr);
    while(ch == '#') {
        while(getc(filePtr) != '\n')
            ;
        ch = getc(filePtr);
    }

    ungetc(ch, filePtr);
    /* read image size information */
    if(fscanf(filePtr, "%d %d", &((*img)->width), &((*img)->height)) != 2) {
        fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
        return 0;
    }

    /* read rgb component */
    if(fscanf(filePtr, "%d", &rgbCompColor) != 1) {
        fprintf(stderr, "Invalid rgb component (error loading '%s')\n",
                filename);
        return 0;
    }

    /* check rgb component depth */
    if(rgbCompColor != RGB_COMPONENT_COLOR) {
        fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
        return 0;
    }

    while(fgetc(filePtr) != '\n')
        ;
    /* memory allocation for pixel data */
    (*img)->data = (struct Pixel *) malloc((*img)->width * (*img)->height * sizeof(struct Pixel));

    if(!img) {
        fprintf(stderr, "Unable to allocate memory\n");
        return 0;
    }

    /* read pixel data from file */
    if(fread((*img)->data, 3 * (*img)->width, (*img)->height, filePtr) != (*img)->height) {
        fprintf(stderr, "Error loading image '%s'\n", filename);
        return 0;
    }

    fclose(filePtr);
    return 1;
}


/**
 *  write PPM image data to a file (destructive)
 *
 *  file_name - C-string, name of the PPM file
 *  img - pointer to a list of Image structs (data for PPM image)
 *
 *  returns 1 is successful, 0 otherwise
 */
int writeImage(char filename[], struct Image *img)
{
    FILE *filePtr;  /* pointer to the PPM file */

    /* open file for output */
    filePtr = fopen(filename, "wb");
    if(!filePtr) {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        return 0;
    }

    /* write the header file image format */
    fprintf(filePtr, "P6\n");

    /* comments */
    fprintf(filePtr, "# try http://goo.gl/rxnHB1 shhhhhhhhhh it's a secret \n");

    /* image size */
    fprintf(filePtr, "%d %d\n", img->width, img->height);

    /* rgb component depth */
    fprintf(filePtr, "%d\n", RGB_COMPONENT_COLOR);

    /* pixel data */
    fwrite(img->data, 3 * img->width, img->height, filePtr);
    fclose(filePtr);

    return 1;
}


/**
 * folloing functions are not needed, just changing-up the pixels for phum
 */

void changeColor(struct Image *img)
{
    int i;
    if(img) {
        for(i = 0; i < img->width * img->height; i++) {
            img->data[i].red = RGB_COMPONENT_COLOR - img->data[i].red;
            img->data[i].green = RGB_COMPONENT_COLOR - img->data[i].green;
            img->data[i].blue = RGB_COMPONENT_COLOR - img->data[i].blue;
        }
    }
}


void rgbPixels(struct Image *img)
{
    int i;
    int n;
    if(img) {
        for(i = 0; i < img->width * img->height; i++) {
            img->data[i].red = img->data[i].green = img->data[i].blue = 0x0;
            n = i%3;
            if(n == 0)
                img->data[i].red = 0xff;
            else if(n == 1)
                img->data[i].green = 0xff;
            else
                img->data[i].blue = 0xff;
        }
    }
}


