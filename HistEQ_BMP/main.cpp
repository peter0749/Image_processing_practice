#include "utils.h"
#include "HistEQ.h"
#include <iostream>
#include <cstdint>
#include <cassert>

int main(int argc, char **argv) {
    using namespace std;
    if (argc!=3) return -1;
    // argv[1]: source, argv[2]: target

    /* Load raw image to my object */
    ImageProcess::Image img(argv[1]);

    /* Call image processor */
    ImageProcess::HistEQ histeq(img);
    ImageProcess::Image *img2 = NULL;
    img2 = histeq.run();
    assert(img2!=NULL);

    /* Output png image to disk */
    img2->writebmp(argv[2]);
    delete img2;

    return 0;
}
