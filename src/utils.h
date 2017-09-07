#ifndef METNUM_TP1_UTILS_H
#define METNUM_TP1_UTILS_H

#include <string>
#include "matrix.h"
#include "ppmloader/ppmloader.h"

struct RGBPixel {
    RGBPixel(unsigned int r, unsigned int g, unsigned int b) : r(r), g(g), b(b) {}

    unsigned int r;
    unsigned int g;
    unsigned int b;

};

namespace Utils {

    matrix<RGBPixel> loadImage(const std::string& filename);
    void saveGrayScaleImage(const matrix<double>& img, const std::string& dst);
    matrix<double> grayscalify(const matrix<RGBPixel>& img);
    matrix<double> grayscalify(const matrix<RGBPixel>& img, double r, double g, double b);
    void saveMatrix3dFiles(const matrix<row<double>>& img, const std::string& dst);

}



#endif //METNUM_TP1_UTILS_H
