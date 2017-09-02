#ifndef METNUM_TP1_UTILS_H
#define METNUM_TP1_UTILS_H

#include <string>
#include "matrix.h"
#include "ppmloader/ppmloader.h"

using namespace std;

struct RGBPixel {
    RGBPixel(unsigned int r, unsigned int g, unsigned int b) : r(r), g(g), b(b) {}

    unsigned int r;
    unsigned int g;
    unsigned int b;

};

namespace Utils {

    matrix<RGBPixel> loadImage(string filename);
    void saveGrayScaleImage(matrix<double> img, string dst);
    matrix<double> grayscalify(matrix<RGBPixel> img, double r, double g, double b);

}



#endif //METNUM_TP1_UTILS_H
