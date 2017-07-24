#include "utils.h"
#include "LinearGradient.h"
#include <iostream>
#include <cstdint>
#include <cassert>

int main(int argc, char **argv) {
    using namespace std;
    if (argc!=13) return -1;
    // argv[1]: file, 
    // ow: W H TYPE R1 G1 B1 A1 R2 G2 B2 A2
    uint32_t imgWidth=atoi(argv[2]), imgHeight=atoi(argv[3]);
    uint8_t *buff = NULL;

    /* Call image processor */
    int mode = atoi(argv[4]);
    ImageProcess::Pix left(atoi(argv[5]),atoi(argv[6]),atoi(argv[7]),atoi(argv[8]));
    ImageProcess::Pix right(atoi(argv[9]),atoi(argv[10]),atoi(argv[11]),atoi(argv[12]));
    ImageProcess::LinearGradient line(imgWidth, imgHeight, left, right, mode);
    ImageProcess::Image *img = NULL;
    img = line.run();
    assert(img!=NULL);

    /* Output raw image from object */
    buff = img->output();
    imgWidth = img->img_W;
    imgHeight= img->img_H;
    delete img; img=NULL;

    /* Output png image to disk */
    unsigned long err = Lodepng::lodepng_encode32_file(argv[1], buff, imgWidth, imgHeight);
    assert(err==0);

    if (buff!=NULL) {
        free(buff), buff=NULL;
    }

    return 0;
}
