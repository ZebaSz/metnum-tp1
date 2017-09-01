#ifndef METNUM_TP1_CHOLESKY_H
#define METNUM_TP1_CHOLESKY_H

#include "matrix.h"

/**
 * Factorize the provided matrix if it is a S.P.D. into an lower triangular matrix.
 *
 * @pre the matrix symmetric and positive-definite
 * @tparam T
 * @param factorized lower triangular matrix aka L
 */
template <typename T>
matrix<T> cholesky_factorization(matrix<T> &mx) {
    assert(isSymmetric(mx));
    int n = mx.size();

    matrix<T> L(n, row<T>(n, 0));

    L[0][0] = sqrt(mx[0][0]);
    for (int j = 1; j < n; ++j) {
        L[j][0] = mx[j][0] / L[0][0];
    }

    for (int i = 1; i < n-1; ++i) {
        size_t sum_col_i = 0;
        for (int k = 0; k < i; ++k) {
            //Implementar Super Kahan!
            sum_col_i += pow(L[i][k], 2);
        }
        L[i][i] = sqrt(mx[i][i] - sum_col_i);

        for (int j = i+1; j < n; ++j) {
            size_t sum_cols_ij = 0;
            for (int k=0; k < i; ++k) {
                //Implementar Super Kahan!
                sum_cols_ij += L[j][k] * L[i][k];
            }

            L[j][i] = (mx[j][i] - sum_cols_ij) / L[i][i];
        }
    }
    size_t sum_Lnk = 0;
    for (int k=0; k < n-1; ++k) {
        sum_Lnk += pow(L[n-1][k],2);
    }
    L[n-1][n-1] = sqrt(mx[n-1][n-1] - sum_Lnk);
    return L;
}

#endif //METNUM_TP1_CHOLESKY_H
