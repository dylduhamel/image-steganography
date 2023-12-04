# Image Steganography in C

## Overview

This program is designed for hiding and recovering messages in PPM (Portable Pixmap) image files using the Least Significant Bit (LSB) method. It manipulates the LSBs (1, 2, or 4 bits) of the image's pixels to encode and decode secret messages.

## Components

- `hideMessage.c`: Hides a message in a PPM file.
- `recoverMessage.c`: Recovers a message from a PPM file.
- `ppmReadWrite.c` and `ppmReadWrite.h`: Utilities for reading and writing PPM files.
- `getImageArgs.c` and `getImageArgs.h`: Argument processing utilities.

## Compilation and Execution

### hideMessage.c

Hides a message in a PPM file.

#### Compilation

```
gcc -ansi -pedantic -Wall -o hide hideMessage.c getImageArgs.c ppmReadWrite.c
```

Usage

```
./hide -b [LSB bits] [message file] [original PPM file]
```

    [LSB bits]: Number of LSBs to use (1, 2, or 4).
    [message file]: Text file containing the message to hide.
    [original PPM file]: PPM image file in which to hide the message.

recoverMessage.c

Extracts a hidden message from a PPM file.
Compilation

```
gcc -ansi -pedantic -Wall -o recover recoverMessage.c getImageArgs.c ppmReadWrite.c
```

```
./recover -b [LSB bits] [PPM file with hidden message]
```

    [LSB bits]: Number of LSBs used in the hidden message (1, 2, or 4).
    [PPM file with hidden message]: PPM image file from which to recover the message.

Example

To hide a message:

```
./hide -b 2 message.txt will.ppm
```

To recover a message:

```
./recover -b 2 will_hidden.ppm
```
