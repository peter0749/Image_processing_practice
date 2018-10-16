#ifndef __INCLUDE_LOAD_BMP_HEADER
#define __INCLUDE_LOAD_BMP_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _lbheader{
    unsigned short identifier;      // 0x0000
    unsigned int filesize;          // 0x0002
    unsigned int reserved;          // 0x0006
    unsigned int bitmap_dataoffset; // 0x000A
    unsigned int bitmap_headersize; // 0x000E
    unsigned int width;             // 0x0012
    unsigned int height;            // 0x0016
    unsigned short planes;          // 0x001A
    unsigned short bits_perpixel;   // 0x001C
    unsigned int compression;       // 0x001E
    unsigned int bitmap_datasize;   // 0x0022
    unsigned int hresolution;       // 0x0026
    unsigned int vresolution;       // 0x002A
    unsigned int usedcolors;        // 0x002E
    unsigned int importantcolors;   // 0x0032
    unsigned int palette;           // 0x0036
} __attribute__((packed,aligned(1))) lbheader;

int readbmp(const char *filename, unsigned int *width, unsigned int *height, unsigned char** buffer);
int writebmp(const char *filename, unsigned int width, unsigned int height, unsigned char *buffer);
#endif
