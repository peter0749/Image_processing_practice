#ifndef __INCLUDE_LOAD_BMP_HEADER
#define __INCLUDE_LOAD_BMP_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readbmp(const char *filename, unsigned int *width, unsigned int *height, unsigned char** buffer);
int writebmp(const char *filename, unsigned int width, unsigned int height, unsigned char *buffer);
#endif
