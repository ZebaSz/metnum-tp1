#ifndef METNUM_TP1_MATRIX_H
#define METNUM_TP1_MATRIX_H

#include <vector>
#include <assert.h>
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

template <typename T>
matrix<T> dotProduct(const matrix<T> &a, const matrix<T> &b) {
    assert(!(a.empty() || b.empty() || a[0].empty() || b[0].empty() || a[0].size() != b.size()));

    int rows = a.size(), columns = b[0].size();
    matrix<T> result(rows, row<T>(columns, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            for (int k = 0; k < b.size(); ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return result;
}
#endif //METNUM_TP1_MATRIX_H
