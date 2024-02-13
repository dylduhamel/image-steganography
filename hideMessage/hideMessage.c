/**
 * This program hides a message in a PPM file using LSb (using b bits), the new
 *image (with LSb message) will be called *_hidden.ppm (old file name with
 *".ppm" replaced with "_hidden.ppm"), If successful, the program will display
 *the number of characters in the message and the number of pixels used (to
 *store the message). The number of LSb usedi, message file, and PPM image file
 *name are provided using command line arguments. If the arguments are
 *incorrect, the program will exit and provide an error message.
 *
 * Notes:
 *   Requires getImageArgs.h (.c) and ppmReadWrite.h (.c)
 *
 * Compile:
 *   gcc -ansi -pedantic -Wall hideMessage.c -o hideMessage getImageArgs.c
 *ppmReadWrite.c
 *   ./hide -b 2 message.txt will.ppm
 *
 * @author Dylan Duhamel {@literal duhadm19@wfu.edu}
 * @date Feb. 27, 2022
 **/

#include "../util/getImageArgs.h"
#include "../util/ppmReadWrite.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hideMessageInImage (struct Image *img, int bit, char textFilename[]);
void printBits (unsigned char x);

int
main (int argc, char *argv[])
{
  struct Image *img = NULL;
  char textFilename[40];
  char orgImageFilename[40] = { '\0' };
  char newImageFilename[40] = { '\0' }; /* what we produce hidden image */
  int bit;
  int argsOk = 0;
  int fileOk = 0;

  argsOk = processHideImageArgs (
      argc, argv, &bit, textFilename,
      orgImageFilename); /* text file name is message text*/
  if (!argsOk)
    return 1;

  fileOk = readImage (&img, orgImageFilename);
  if (!fileOk)
    return 1;

  hideMessageInImage (img, bit, textFilename);

  /* concatonate _hidden.ppm to the name of the orgImageFilename */
  strcpy (newImageFilename, orgImageFilename);
  newImageFilename[strlen (newImageFilename) - 4] = '\0';
  strcat (newImageFilename, "_hidden.ppm");

  fileOk = writeImage (newImageFilename, img);
  if (!fileOk)
  {
    if (img)
      free (img);
    return 1;
  }

  printf ("image saved as %s \n", newImageFilename);

  /* Free memory */
  if (img->data)
    free (img->data);
  if (img)
    free (img);

  return 0;
}

/*  function to hide the message in -b 1, 2, 4
    takes Image struct, bit specyfier, and the name of file where message is
   stores returns an integer 1 is no issues edits the LSB's on each RGB value
   to hide char
 */
int
hideMessageInImage (struct Image *img, int bit, char textFilename[])
{
  unsigned char *color = (unsigned char *)img->data;
  FILE *filePtr = fopen (textFilename,
                         "rie"); /* File pointer to text that will be hidden */
  unsigned char ch;
  int i = 0;         /* index */
  int charIndex = 2; /* begins at 2 because we add :) at the end (2 char) */

  if (filePtr == 0)
  {
    printf ("file can't be opened \n");
    return 0;
  }

  /* getting the initial char of text to hide*/
  ch = fgetc (filePtr);

  /* 1 bit LSB */
  if (bit == 1)
  {
    /* loop through entire file and process */
    while (ch < 127 && i < img->width * img->height)
    {
      color[i] = (color[i] & 0xFE) | ((ch & 0x80) >> 7);
      i++;
      color[i] = (color[i] & 0xFE) | ((ch & 0x40) >> 6);
      i++;
      color[i] = (color[i] & 0xFE) | ((ch & 0x2C) >> 5);
      i++;
      color[i] = (color[i] & 0xFE) | ((ch & 0x10) >> 4);
      i++;
      color[i] = (color[i] & 0xFE) | ((ch & 0x08) >> 3);
      i++;
      color[i] = (color[i] & 0xFE) | ((ch & 0x04) >> 2);
      i++;
      color[i] = (color[i] & 0xFE) | ((ch & 0x02) >> 1);
      i++;
      color[i] = (color[i] & 0xFE) | (ch & 0x01);
      i++;
      ch = fgetc (filePtr);
      charIndex++;
    }
    ch = ':';
    color[i] = (color[i] & 0xFE) | ((ch & 0x80) >> 7);
    i++;
    color[i] = (color[i] & 0xFE) | ((ch & 0x40) >> 6);
    i++;
    color[i] = (color[i] & 0xFE) | ((ch & 0x2C) >> 5);
    i++;
    color[i] = (color[i] & 0xFE) | ((ch & 0x10) >> 4);
    i++;
    color[i] = (color[i] & 0xFE) | ((ch & 0x08) >> 3);
    i++;
    color[i] = (color[i] & 0xFE) | ((ch & 0x04) >> 2);
    i++;
    color[i] = (color[i] & 0xFE) | ((ch & 0x02) >> 1);
    i++;
    color[i] = (color[i] & 0xFE) | (ch & 0x01);
    i++;
    ch = ')';
    color[i] = (color[i] & 0xFE) | ((ch & 0x80) >> 7);
    i++;
    color[i] = (color[i] & 0xFE) | ((ch & 0x40) >> 6);
    i++;
    color[i] = (color[i] & 0xFE) | ((ch & 0x2C) >> 5);
    i++;
    color[i] = (color[i] & 0xFE) | ((ch & 0x10) >> 4);
    i++;
    color[i] = (color[i] & 0xFE) | ((ch & 0x08) >> 3);
    i++;
    color[i] = (color[i] & 0xFE) | ((ch & 0x04) >> 2);
    i++;
    color[i] = (color[i] & 0xFE) | ((ch & 0x02) >> 1);
    i++;
    color[i] = (color[i] & 0xFE) | (ch & 0x01);
    i++;

    /* 2 bit LSB */
  }
  else if (bit == 2)
  {
    /* loop through entire file and process */
    while (ch < 127 && i < img->width * img->height)
    {
      color[i] = (color[i] & 0xFC) | ((ch & 0xC0) >> 6);
      i++;
      color[i] = (color[i] & 0xFC) | ((ch & 0x30) >> 4);
      i++;
      color[i] = (color[i] & 0xFC) | ((ch & 0x0C) >> 2);
      i++;
      color[i] = (color[i] & 0xFC) | (ch & 0x03);
      i++;
      ch = fgetc (filePtr);
      charIndex++;
    }
    /* adding the :) to the end */
    ch = ':';
    color[i] = (color[i] & 0xFC) | ((ch & 0xC0) >> 6);
    i++;
    color[i] = (color[i] & 0xFC) | ((ch & 0x30) >> 4);
    i++;
    color[i] = (color[i] & 0xFC) | ((ch & 0x0C) >> 2);
    i++;
    color[i] = (color[i] & 0xFC) | (ch & 0x03);
    i++;
    ch = ')';
    color[i] = (color[i] & 0xFC) | ((ch & 0xC0) >> 6);
    i++;
    color[i] = (color[i] & 0xFC) | ((ch & 0x30) >> 4);
    i++;
    color[i] = (color[i] & 0xFC) | ((ch & 0x0C) >> 2);
    i++;
    color[i] = (color[i] & 0xFC) | (ch & 0x03);
    i++;

    /* 4 bit LSB */
  }
  else if (bit == 4)
  {
    /* loop through entire file and process */
    while (ch < 127 && i < img->width * img->height)
    {
      color[i] = (color[i] & 0xf0) | ((ch & 0xf0) >> 4);
      i++;
      color[i] = (color[i] & 0xf0) | (ch & 0x0f);
      i++;
      ch = fgetc (filePtr);
      charIndex++;
    }
    /* adding the :) to the end */
    ch = ':';
    color[i] = (color[i] & 0xf0) | ((ch & 0xf0) >> 4);
    i++;
    color[i] = (color[i] & 0xf0) | (ch & 0x0f);
    i++;
    ch = ')';
    color[i] = (color[i] & 0xf0) | ((ch & 0xf0) >> 4);
    i++;
    color[i] = (color[i] & 0xf0) | (ch & 0x0f);
    i++;
  }

  printf ("hid %d characters in %d color components (%d pixels)\n", charIndex,
          i, (i + 2) / 3);

  fclose (filePtr);
  return 1;
}

/* prints bit info for char input */
void
printBits (unsigned char x)
{
  int value = x;
  char *bits;
  int i = 0;
  bits = malloc ((size_t)(sizeof (x) * 8 + 1));
  for (i = 0; i < sizeof (x) * 8; i++)
  {
    bits[sizeof (x) * 8 - i - 1] = (char)((value & 0x1) + 48);
    value = value >> 1;
  }
  bits[sizeof (x) * 8] = '\0';
  printf ("%x(%s)\n", x, bits);
  free (bits);
}
