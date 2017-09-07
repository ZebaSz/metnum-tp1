#include <stdexcept>
#include <tuple>
#include <iostream>
#include "utils.h"

namespace Utils {

    matrix<RGBPixel> loadImage(const std::string& filename) {
        matrix<RGBPixel> result;
        uchar* data = NULL;
        int width = 0, height = 0;
        PPM_LOADER_PIXEL_TYPE pt = PPM_LOADER_PIXEL_TYPE_INVALID;

        bool ret = LoadPPMFile(&data, &width, &height, &pt, filename.c_str());
        if (!ret || width == 0|| height == 0|| pt != PPM_LOADER_PIXEL_TYPE_RGB_8B) {
            throw std::runtime_error("Failed to load the file:"+filename);
        }

        for (int i = 0; i < height; i++) {
            row<RGBPixel> r;
            for (int j = 0; j < width; ++j) {
                unsigned int red   = data[ i * width * 3 + j * 3 + 0];
                unsigned int green = data[ i * width * 3 + j * 3 + 1];
                unsigned int blue  = data[ i * width * 3 + j * 3 + 2];
                r.push_back(RGBPixel(red, green, blue));
            }
            result.push_back(r);
        }

        delete [] data;
        return result;
    }

    void saveGrayScaleImage(const matrix<double>& img, const std::string& dst) {
        size_t height = img.size(), width = img[0].size();
        int h = (int) height, w = (int) width;
        uchar* out = new uchar[height * width];

        int a = 0;
        for (size_t i = 0; i < height; i++) {
            for (size_t j = 0; j < width; j++) {
                out[a] = (uchar) img[i][j];
                a++;
            }
        }

        char comments[100];
        sprintf(comments, "%s", "Hello world");

        bool ret = SavePPMFile(dst.c_str(), out, w, h, PPM_LOADER_PIXEL_TYPE_GRAY_8B, comments);
        if (!ret) {
            throw std::runtime_error("Couldn't save Image to ppm file");
        }

    }

    matrix<double> grayscalify(const matrix<RGBPixel>& img) {
        return grayscalify(img, 0.333333333333333333333333, 0.333333333333333333333333, 0.333333333333333333333333);
    }

    matrix<double> grayscalify(const matrix<RGBPixel>& img, double r, double g, double b) {
        matrix<double> result;
        size_t height = img.size(), width = img[0].size();
        for (size_t i = 0; i < height; i++) {
            row<double> row;
            for (size_t j = 0; j < width; ++j) {
                double pixel = (r * img[i][j].r + g * img[i][j].g + b * img[i][j].b);
                row.push_back((pixel < 255) ? pixel : 255);
            }
            result.push_back(row);
        }
        return result;
    }

    void saveMatrix3dFiles(const matrix<row<double>> &m, const std::string &dst) {
        size_t height = m.size(), width = m[0].size();

        FILE *x = fopen((dst+"_x.csv").c_str(), "w");
        FILE *y = fopen((dst+"_y.csv").c_str(), "w");
        FILE *z = fopen((dst+"_z.csv").c_str(), "w");

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j != 0) {
                    fprintf(x, ",");
                    fprintf(y, ",");
                    fprintf(z, ",");
                }
                fprintf(x, "%f", m[i][j][0]);
                fprintf(y, "%f", m[i][j][1]);
                fprintf(z, "%f", m[i][j][2]);
            }
            fprintf(x, "\n");
            fprintf(y, "\n");
            fprintf(z, "\n");
        }
        fclose(x);
        fclose(y);
        fclose(z);
    }

    void saveMatrixFile(const matrix<double> &m, const std::string &dst) {
        size_t height = m.size(), width = m[0].size();

        FILE *f = fopen(dst.c_str(), "w");

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j != 0) {
                    fprintf(f, ",");
                }
                fprintf(f, "%f", m[i][j]);
            }
            fprintf(f, "\n");
        }
        fclose(f);
    }
}


