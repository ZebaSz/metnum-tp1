#ifndef METNUM_TP1_MASK_H
#define METNUM_TP1_MASK_H

#include <iostream>
#include "matrix.h"

using namespace std;

struct center_and_radius {
    center_and_radius(int x, int y, int r) : xCenter(x), yCenter(y), radius(r) {}
    int xCenter;
    int yCenter;
    int radius;
};

template <typename T>
center_and_radius get_center_and_radius(matrix<T> &mask) {
    int leftColumn = columns(img) - 1;
    int rightColumn = 0;
    int upperRow = rows(img) - 1;
    int lowerRow = 0;

    for (int i = 0; i < filas(img); i++) {
        for (int j = 0; j < columnas(img); j++) {
            if (mask[i][j] > 250) {
                if (j < leftColumn) leftColumn = j;
                if (j > rightColumn) rightColumn = j;
                if (i < upperRow) upperRow = i;
                if (i > lowerRow) lowerRow = i;
            }
        }
    }

    int radius = (rightColumn - leftColumn + 1) / 2;
    int xCenter = leftColumn + radius + 1;
    int yCenter = upperRow + radius + 1;

    return center_and_radius(xCenter, yCenter, radius);
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
matrix<T> apply_mask(matrix<T> &img, matrix<T> &mask) {
    assert(rows(img) == rows(mask) || columns(img) == columns(mask));

    int leftColumn = columns(img) - 1;
    int rightColumn = 0;
    int upperRow = rows(img) - 1;
    int lowerRow = 0;

    for (int i = 0; i < filas(img); i++) {
        for (int j = 0; j < columnas(img); j++) {
            if (mask[i][j] > 250) {
                if (j < leftColumn) leftColumn = j;
                if (j > rightColumn) rightColumn = j;
                if (i < upperRow) upperRow = i;
                if (i > lowerRow) lowerRow = i;
            }
        }
    }

    cout << "U: " << upperRow << " Lo: " << lowerRow << "Le: " << leftColumn << "R: " << rightColumn;

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

#endif //METNUM_TP1_MASK_H
