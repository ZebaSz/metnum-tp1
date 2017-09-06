#ifndef METNUM_TP1_GAUSS_H
#define METNUM_TP1_GAUSS_H

#include "matrix.h"

/**
 * Simplifies the provided matrix,
 * converting it into row echelon form if possible.
 *
 * @pre the matrix is in augmented form
 * @tparam T
 * @param mx the matrix
 */
template <typename T>
void gaussian_elimination(matrix<T> &mx);

template <typename T>
void subtract_rows(row<T>& a, const row<T>& b, double multiplier);

/**
 * Searches for a row with a non-zero value in a particular column,
 * and swaps it into the row of the same number if needed.
 *
 * @param m the matrix to swap rows
 * @param col the column where the non-zero value should be
 * @return whether such a row was found
 */
template <typename T>
size_t find_swap_rows(matrix<T>& m, size_t col);

template <typename T>
void gaussian_elimination(matrix<T> &mx) {
    for (size_t i = 0; i < mx.size() - 1; ++i) {
        find_swap_rows(mx, i);
        for (size_t j = i + 1; j < mx.size(); ++j) {
            mx[j][i] /= mx[i][i];
            for (size_t k = i + 1; k < mx.size(); k++) {
                mx[j][k] -= mx[j][i] * mx[i][k];
            }
        }
    }
}

template <typename T>
void subtract_rows(row<T>& a, const row<T>& b, double multiplier) {
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] -= (T)(multiplier * b[i]);
    }
}

template<typename T>
size_t find_swap_rows(matrix<T>& m, size_t col) {
    size_t max = col;
    for (size_t i = col + 1; i < m.size(); ++i) {
        if(m[i][col] > m[max][col]) {
            max = i;
        }
    }
    if(max != col) {
        std::swap(m[col], m[max]);
    }
    return max;
}

#endif //METNUM_TP1_GAUSS_H
