#include "utils.h"
#include "SeamCarve.h"
#include <iostream>
#include <cstdint>
#include <cassert>

int main(int argc, char **argv) {
    using namespace std;
    if (argc!=4) return -1;
    // argv[1]: source, argv[2]: target, argv[3]: line number
    uint32_t imgWidth=0, imgHeight=0;
    uint8_t *buff = NULL;

    /* Read png32 image from disk */
    unsigned err = Lodepng::lodepng_decode32_file(&buff, &imgWidth, &imgHeight, argv[1]);
    assert(err==0);
    assert(buff!=NULL);

    /* Load raw image to my object */
    ImageProcess::Image *img = NULL;
    img = new ImageProcess::Image(imgWidth, imgHeight, buff);
    assert(img!=NULL);
    if (buff!=NULL) {
        free(buff), buff=NULL;
    }

    /* Call image processor */
    ImageProcess::SeamCarve *seam = NULL;
    int N = atoi(argv[3]);
    while (N-- > 0) {
        seam = new ImageProcess::SeamCarve(*img);
        assert(seam!=NULL);
        ImageProcess::Image *img2 = seam->run();
        if (seam!=NULL) {
            delete seam; seam=NULL;
        }
        if (img!=NULL) {
            delete img; img=NULL;
        }
        img = img2;
        assert(img!=NULL);
    }

    /* Output raw image from object */
    buff = img->output();
    imgWidth = img->img_W;
    imgHeight= img->img_H;
    delete img; img=NULL;

    /* Output png image to disk */
    err = Lodepng::lodepng_encode32_file(argv[2], buff, imgWidth, imgHeight);
    assert(err==0);

    if (buff!=NULL) {
        free(buff), buff=NULL;
    }

    return 0;
}
