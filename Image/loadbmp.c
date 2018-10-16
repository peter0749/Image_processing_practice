#include "loadbmp.h"

int readbmp(const char *filename, unsigned int *width, unsigned int *height, unsigned char** buffer) {
    FILE *ifp;
    char c[128];
    unsigned char* ptr;
    unsigned int img_size = 0;
    lbheader hbmp;

    ifp = fopen(filename, "rb");
    if(ifp==NULL) return -1;

    ptr = (unsigned char *)&hbmp;
    fread(ptr, sizeof(unsigned char), sizeof(lbheader), ifp);
    img_size = hbmp.width*hbmp.height*3;
    *buffer = NULL;
    *buffer = (unsigned char*)malloc(sizeof(unsigned char)*img_size);
    if (*buffer==NULL) return -2;
    fread(*buffer, sizeof(unsigned char), img_size, ifp);
    fclose(ifp);
    *width = hbmp.width;
    *height= hbmp.height;
    return img_size;
}

int writebmp(const char *filename, unsigned int width, unsigned int height, unsigned char *buffer) {
    FILE *ofp;
    lbheader hbmp;
    char c[128];
    unsigned char *ptr;
    unsigned int img_size=width*height*3;
    unsigned int bmp_size=img_size+54;
    hbmp.width = width;
    hbmp.height= height;
    hbmp.filesize = bmp_size;

    ofp = fopen(filename, "wb");
    if(ofp==NULL) return -1;

    ptr = (unsigned char *)&hbmp;
    fwrite(ptr, sizeof(unsigned char), sizeof(lbheader), ofp);
    img_size = hbmp.width*hbmp.height*3;
    fwrite(buffer, sizeof(unsigned char), img_size, ofp);
    fclose(ofp);
    return img_size;
}
