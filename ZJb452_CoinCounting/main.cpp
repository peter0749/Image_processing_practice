#include "utils.h"
#include "Hough.h"
#include <iostream>
#include <cstdint>
#include <cassert>
#include <cstdio>
#include <cstring>

int main(int argc, char **argv) {
    using namespace std;
    if (argc!=7) return -1;
    // argv[1]: source, argv[2]: target
    // argv[3]: radius, argv[4]: eps
    // argv[5]: threshold, argv[6]: min_component
    double radius=atof(argv[3]);
    double eps   =atof(argv[4]);
    int    thres =atof(argv[5]);
    int    min_comp = atoi(argv[6]);
    uint32_t imgWidth=0, imgHeight=0;
    uint8_t *buff = NULL;
    char fname1[4096], fname2[4096];
    sprintf(fname1, "%s.result.png", argv[2]);
    sprintf(fname2, "%s.temp.png", argv[2]);

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
    ImageProcess::HoughCircle *hough = NULL;
    hough = new ImageProcess::HoughCircle(img,radius,eps,thres);
    assert(hough!=NULL);
    ImageProcess::Image *img2 = NULL, *img3 = NULL;
    img2 = hough->out();
    img3 = hough->HoughTempResult();
    int coin_count = hough->count(min_comp);
    cout << "Coin count: " << coin_count << endl;
    delete hough; hough=NULL;
    assert(img2!=NULL);
    assert(img3!=NULL);

    /* Output raw image from object */
    buff = img2->output();
    imgWidth = img2->img_W;
    imgHeight= img2->img_H;
    delete img2; img2=NULL;
    err = Lodepng::lodepng_encode32_file(fname1, buff, imgWidth, imgHeight);
    assert(err==0);
    if (buff!=NULL) {
        free(buff), buff=NULL;
    }

    /* Output raw image from object */
    buff = img3->output();
    imgWidth = img3->img_W;
    imgHeight= img3->img_H;
    delete img3; img3=NULL;
    err = Lodepng::lodepng_encode32_file(fname2, buff, imgWidth, imgHeight);
    assert(err==0);
    if (buff!=NULL) {
        free(buff), buff=NULL;
    }

    return 0;
}
