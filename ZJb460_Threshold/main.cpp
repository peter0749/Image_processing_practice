#include "utils.h"
#include "Threshold.h"
#include <iostream>
#include <cstdint>
#include <cassert>

int main(int argc, char **argv) {
    using namespace std;
    if (argc!=4) return -1;
    // argv[1]: source, argv[2]: target
    // argv[3]: threshold (<0: auto)
    uint32_t imgWidth=0, imgHeight=0;
    int threshold = atoi(argv[3]);
    uint8_t *buff = NULL;

    /* Read png32 image from disk */
    unsigned err = Lodepng::lodepng_decode32_file(&buff, &imgWidth, &imgHeight, argv[1]);
    assert(err==0);
    assert(buff!=NULL);

    /* Load raw image to my object */
    ImageProcess::Image img(imgWidth, imgHeight, buff);
    if (buff!=NULL) {
        free(buff), buff=NULL;
    }

    /* Call image processor */
    ImageProcess::Threshold thres(img);
    ImageProcess::Image *img2 = NULL;
    if (threshold<0)
        img2 = thres.run();
    else
        img2 = thres.run(threshold);
    assert(img2!=NULL);

    /* Output raw image from object */
    buff = img2->output();
    imgWidth = img2->img_W;
    imgHeight= img2->img_H;
    delete img2; img2=NULL;

    /* Output png image to disk */
    err = Lodepng::lodepng_encode32_file(argv[2], buff, imgWidth, imgHeight);
    assert(err==0);

    if (buff!=NULL) {
        free(buff), buff=NULL;
    }

    return 0;
}
