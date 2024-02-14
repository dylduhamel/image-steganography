/**
 * This program reads a PPM image file and prints the LSb encrypted message
 *(using b bits), followed by the number of characters in the message and the
 *number of pixels used (to store the message) The number of LSb used and PPM
 *image file name is provided using command line arguments. If either argument
 *is not proveded or is incorrect, the program will exit and provide an error
 *message.
 *
 * Notes:
 *   Requires getImageArgs.h (.c) and ppmReadWrite.h (.c)
 *
 * Compile:
 *   gcc -ansi -pedantic -Wall -recoverMessage.c -o recoverMessage
 *getImageArgs.c ppmReadWrite.c
 *   ./recover -b 2 will_hidden.ppm
 *
 * @author Dylan Duhamel {@literal duhadm19@wfu.edu}
 * @date Feb. 19, 2022
 **/

#include "../util/getImageArgs.h"
#include "../util/ppmReadWrite.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int recoverMessage(struct Image *img, char bits[]);
void printCharBits(unsigned char x);

int main(int argc, char *argv[])
{
  struct Image *img; /* pointer to image repsresentation */
  char imageFilename[20];
  int bit; /* 1, 2, 4 */
  int argsOk;
  int fileOk;

  argsOk = processImageArgs(argc, argv, &bit,
                            imageFilename); /* bit as pointer because we want
                                               to change it in program */
  if (!argsOk)
    return 1;

  fileOk = readImage(&img, imageFilename);

  if (!fileOk)
    return 1;

  recoverMessage(img, argv[2]); /* where we do all of the work */

  /* Free memory */
  if (img->data)
    free(img->data);
  if (img)
    free(img);

  return 0;
}

/* function to recover the hidden message
takes a struct pointer of bits, and the args index for size of bit to search in
*/
int recoverMessage(struct Image *img, char bits[])
{
  /* star operator  (*img).width ===== img->width */
  unsigned char *color =
      (unsigned char *)
          img->data; /* pointer to the RGB color components of img */
  /* color is handle into byte arr (use it from here on out) */
  char ch = 0x0;
  char prevCh; /* prev character for loop */
  char steganString[50] = "";
  int i = 0; /* local counter */
  int j;     /* nested loop counter */
  char mask; /* size of mask */
  int shift; /* how much to shift each time*/
  int loop;  /* length of internal loop for shifting */

  /* assigns the appropriate mask, shift length, and loop length for specified
   * bite length from args */
  if (strcmp(bits, "1") == 0)
  {
    mask = 0x01;
    shift = 1;
    loop = 6;
  }
  else if (strcmp(bits, "2") == 0)
  {
    mask = 0x03;
    shift = 2;
    loop = 2;
  }
  else if (strcmp(bits, "4") == 0)
  {
    mask = 0x0f;
    shift = 4;
    loop = 0;
  }
  else
  {
    return 0;
  }

  /* processing for -b 1,2,4 */
  while (i < 3 * (img->width * img->height))
  {
    ch = 0x0;
    ch = (color[i] & mask) << shift;
    i++;
    /* shifting and masking for length needed (more when 'stealing' less bits)
     */
    for (j = 0; j < loop; j++)
    {
      ch = (ch | (color[i] & mask)) << shift;
      i++;
    }
    /* the final mask, replacing the last 'mask sized' values */
    ch = ch | (color[i] & mask);
    i++;

    /* add to string */
    strncat(steganString, &ch, 1);

    /* breaks when hits the :) identifier*/
    if (prevCh == 58 && ch == 41)
      break;
    prevCh = ch;
  }

  /* prints the appropriate information after completion */
  printf("%s", steganString);
  printf("\n%ld characters recovered from %d color components (%d pixels)\n",
         strlen(steganString), i, (i + 2) / 3);

  return 1;
}

/**
 * Helpful function that prints the bits of an unsigned char
 */
void printCharBits(unsigned char x)
{
  int value = x;
  char *bits;
  int i;
  bits = malloc((size_t)(sizeof(x) * 8 + 1));
  for (i = 0; i < sizeof(x) * 8; i++)
  {
    bits[sizeof(x) * 8 - i - 1] = (char)((value & 0x1) + 48);
    value = value >> 1;
  }
  bits[sizeof(x) * 8] = '\0';
  printf("%x(%s)\n", x, bits);
  free(bits);
}
