CC=gcc

CFLAGS=-ansi -pedantic -Wall

CLIBS=../util/getImageArgs.c ../util/ppmReadWrite.c

TARGET=recoverMessage

all:$(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(TARGET).c -o build/$(TARGET) $(CLIBS)
