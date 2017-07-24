#include "utils.h"
#include "TextureTransfer.h"
#include <iostream>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <cstdint>

int main(int argc, char **argv) {
    using namespace std;
    using namespace ImageProcess;
    // argv[1]: src, argv[2]: tex
    // argv[3]: result, argv[4]: overlap
    // argv[5]: tile size
    if (argc!=6) return -1;
    char *src = argv[1];
    char *tex = argv[2];
    char *result = argv[3];
    int overlap = atoi(argv[4]);
    int tile_size = atoi(argv[5]);

    uint32_t imgWidth=0, imgHeight=0;
    uint8_t *buff=NULL;

    unsigned err = Lodepng::lodepng_decode32_file(&buff, &imgWidth, &imgHeight, src);
    assert(err==0);
    assert(buff!=NULL);
    Image srcImg(imgWidth, imgHeight, buff);
    free(buff); buff=NULL;

    err = Lodepng::lodepng_decode32_file(&buff, &imgWidth, &imgHeight, tex);
    assert(err==0);
    assert(buff!=NULL);
    Image texImg(imgWidth, imgHeight, buff);
    free(buff); buff=NULL;

    TextureTransfer tf(srcImg, texImg, overlap, tile_size);
    Image *output = tf.run();
    
    buff = output->output();
    imgWidth = output->img_W;
    imgHeight= output->img_H;
    delete output; output=NULL;

    err = Lodepng::lodepng_encode32_file(result, buff, imgWidth, imgHeight);
    assert(err==0);

    if (buff!=NULL) {
        free(buff), buff=NULL;
    }

    return 0;
}
