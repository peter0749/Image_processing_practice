#include "utils.h"
#include "Edge.h"
#include <iostream>
#include <cstdint>
#include <cassert>
#include <cstdio>
#include <cstring>

int main(int argc, char **argv) {
    using namespace std;
    if (argc<3) return -1;
    // argv[1]: source, argv[2]: target
    // argv[3]: thres

    /* Read png32 image from disk */
    uint32_t imgWidth=0, imgHeight=0;
    int thres=0;
    uint8_t *buff = NULL;

    if (argc>3) thres=atoi(argv[3]);

    unsigned err = Lodepng::lodepng_decode32_file(&buff, &imgWidth, &imgHeight, argv[1]);
    assert(err==0);
    assert(buff!=NULL);

    /* Load raw image to my object */
    ImageProcess::Image img(imgWidth, imgHeight, buff);
    if (buff!=NULL) {
        free(buff), buff=NULL;
    }

    /* Call image processor */
    ImageProcess::Edge *edge = NULL;
    edge = new ImageProcess::Edge(img);
    assert(edge!=NULL);
    ImageProcess::Image *img2 = NULL;
    img2 = edge->run(thres);
    delete edge; edge=NULL;
    assert(img2!=NULL);

    /* Output raw image from object */
    buff = img2->output();
    imgWidth = img2->img_W;
    imgHeight= img2->img_H;
    delete img2; img2=NULL;
    err = Lodepng::lodepng_encode32_file(argv[2], buff, imgWidth, imgHeight);
    assert(err==0);
    if (buff!=NULL) {
        free(buff), buff=NULL;
    }

    return 0;
}
