#ifndef METNUM_TP1_MASK_H
#define METNUM_TP1_MASK_H

#include <iostream>
#include "matrix.h"

using namespace std;

namespace Mask {
    struct circle {
        circle(int x, int y, int r) : xCenter(x), yCenter(y), radius(r) {}
        int xCenter;
        int yCenter;
        int radius;
    };

    template <typename T>
    circle get_center_and_radius(const matrix<T>& mask) {
        int leftColumn = Matrix::columns(mask) - 1;
        int rightColumn = 0;
        int upperRow = Matrix::rows(mask) - 1;
        int lowerRow = 0;

        for (int i = 0; i < Matrix::rows(mask); i++) {
            for (int j = 0; j < Matrix::columns(mask); j++) {
                if (mask[i][j] > 250) {
                    if (j < leftColumn) leftColumn = j;
                    if (j > rightColumn) rightColumn = j;
                    if (i < upperRow) upperRow = i;
                    if (i > lowerRow) lowerRow = i;
            }
        }

        int radius = (rightColumn - leftColumn + 1) / 2;
        int xCenter = leftColumn + radius + 1;
        int yCenter = upperRow + radius + 1;

        return circle(xCenter, yCenter, radius);
    }

/**
 * Apply a mask to an image, returning a matrix adjusted to the mask size. The
 * elements outside de mask are filled with zeros.
 *
 * @pre The image and mask must have same dimensions.
 * @tparam matrix<T>
 * @param img the image matrix, mask the mask matrix
 */
template <typename T>
matrix<T> apply_mask(const matrix<T>& img, const matrix<T>& mask) {
    assert(Matrix::rows(img) == Matrix::rows(mask) && Matrix::columns(img) == Matrix::columns(mask));

    int leftColumn = Matrix::columns(img) - 1;
    int rightColumn = 0;
    int upperRow = Matrix::rows(img) - 1;
    int lowerRow = 0;

    for (int i = 0; i < Matrix::rows(img); i++) {
        for (int j = 0; j < Matrix::columns(img); j++) {
            if (mask[i][j] > 250) {
                if (j < leftColumn) leftColumn = j;
                if (j > rightColumn) rightColumn = j;
                if (i < upperRow) upperRow = i;
                if (i > lowerRow) lowerRow = i;
            }
        }

        int resultRows = lowerRow - upperRow + 1;
        int resultColumns = rightColumn - leftColumn + 1;
        matrix<T> result(resultRows, row<T>(resultColumns));
        for (int i = 0; i < resultRows; i++) {
            for (int j = 0; j < resultColumns; j++) {
                if (mask[upperRow + i][leftColumn + j] > 250)
                    result[i][j] = img[upperRow + i][leftColumn + j];
                else
                    result[i][j] = 0;
            }
        }

        return result;
    }
}

#endif //METNUM_TP1_MASK_H
