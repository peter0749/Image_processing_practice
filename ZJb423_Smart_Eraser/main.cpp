#include "utils.h"
#include "Eraser.h"
#include <iostream>
#include <cstring>
#include <cassert>

int main(int argc, char **argv) {
    using namespace std;
    if (argc!=7) return -1;
    // argv[1]: source png32; argv[2]: target png32
    // argv[3]: x; argv[4]: y; argv[5]: mode; argv[6]: diff
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
    ImageProcess::Eraser eraser(&img, atoi(argv[5]), atoi(argv[3]), atoi(argv[4]), atof(argv[6]));
    eraser.run();

    /* Output raw image from object */
    buff = img.output();

    /* Output png image to disk */
    err = Lodepng::lodepng_encode32_file(argv[2], buff, imgWidth, imgHeight);
    assert(err==0);

    if (buff!=NULL) {
        free(buff), buff=NULL;
    }
    return 0;
}
