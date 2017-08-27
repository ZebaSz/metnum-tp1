#ifndef METNUM_TP1_MATRIX_H
#define METNUM_TP1_MATRIX_H

#include <vector>
#include "matrix.h"

template <typename T>
using row = std::vector<T>;

template <typename T>
using matrix = std::vector< row<T> >;

template <typename T>
matrix<T> toMatrix(T** arr, int height, int width) {
    matrix<T> mx;
    for(int i = 0; i < height; ++i) {
        row<T> r;
        for (int j = 0; j < width; ++j) {
            r.push_back(arr[i][j]);
        }
        mx.push_back(r);
    }
    return mx;
}

#endif //METNUM_TP1_MATRIX_H
