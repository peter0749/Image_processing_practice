#include "utils.h"
#include "Scale.h"
#include <iostream>
#include <cstdint>

int main(int argc, char **argv) {
    using namespace std;
    if (argc!=6) return -1;
    // argv[1]: source, argv[2]: target
    // argv[3]: ratioX, argv[4]: ratioY
    // argv[5]: mode(0: bilinear/ 1: nearest)
    uint32_t imgWidth=0, imgHeight=0;
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
    ImageProcess::Scale *scale = NULL;
    scale = new ImageProcess::Scale(atof(argv[3]), atof(argv[4]), atoi(argv[5]), &img);
    assert(scale!=NULL);
    ImageProcess::Image *img2 = NULL;
    img2 = scale->run();
    assert(img2!=NULL);
    delete scale; scale=NULL; // scale can only be used once.

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
