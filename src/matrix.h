#ifndef METNUM_TP1_MATRIX_H
#define METNUM_TP1_MATRIX_H

#include <vector>
#include <assert.h>
#include "matrix.h"
#include "math.h"

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
    assert(a.empty() || b.empty() || a[0].empty() || b[0].empty() || a[0].size() != b.size());

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

template <typename T>
T infinityNorm(const matrix<T> &matrix1) {
    assert (!matrix1.empty() && !matrix1[0].empty());
    T result = matrix1[0][0];
    for (int i = 0; i < matrix1.size(); ++i) {
        for (int j = 0; j < matrix1[i].size(); ++j) {
            if (result < matrix1[i][j]) {
                result = matrix1[i][j];
            }
        }
    }
    return result;
}

template <typename T>
T twoNorm(const matrix<T> &matrix1) {
    T result = 0;
    for (int i = 0; i < matrix1.size(); ++i) {
        for (int j = 0; j < matrix1[i].size(); ++j) {
            // Super Kahan2!!
            T c = 0.0;
            T y = pow(matrix1[i][j], 2)-c;
            T t = result + y;
            c = (t - result) - y;
            result = t;
        }
    }
    return sqrt(result);
}

template <typename T>
T singleNorm(const matrix<T> &matrix1) {
    T result = 0;
    for (int i = 0; i < matrix1.size(); ++i) {
        for (int j = 0; j < matrix1[i].size(); ++j) {
            // Super Kahan!!
            T c = 0.0;
            T y = matrix1[i][j]-c;
            T t = result + y;
            c = (t - result) - y;
            result = t;
        }
    }
    return result;
}

template <typename T>
bool isSquared(const matrix<T>& m) {
    int n = m.size();
    for (int i = 0; i < n; ++i) {
        if (m[i].size() != n)
            return false;
    }
    return true;
}

template <typename T>
bool isSymmetric(const matrix<T>& m) {
    assert(isSquared(m));

    int n = m.size();
    for (int i = 0; i < n; ++i)   {
        for (int j = 0; j < n; ++j) {
            if (m[i][j] != m[j][i]) {
                return false;
            }
        }
    }
    return true;
}


#endif //METNUM_TP1_MATRIX_H
