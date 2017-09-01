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
        T sum_col_i = 0;
        for (int k = 0; k < i; ++k) {
            //Super Kahan!
            T c = 0.0;
            T y = pow(L[i][k], 2)-c;
            T t = sum_col_i + y;
            c = (t - sum_col_i) - y;
            sum_col_i = t;
        }
        T lii = mx[i][i] - sum_col_i;
        assert(lii > 0);
        L[i][i] = sqrt(lii);

        for (int j = i+1; j < n; ++j) {
            T sum_cols_ij = 0;
            for (int k=0; k < i; ++k) {
                //Super Kahan!
                T c = 0.0;
                T y = (L[j][k] * L[i][k])-c;
                T t = sum_cols_ij + y;
                c = (t - sum_cols_ij) - y;
                sum_cols_ij = t;
            }

            L[j][i] = (mx[j][i] - sum_cols_ij) / L[i][i];
        }
    }
    T sum_Lnk = 0;
    for (int k=0; k < n-1; ++k) {
        sum_Lnk += pow(L[n-1][k],2);
    }
    L[n-1][n-1] = sqrt(mx[n-1][n-1] - sum_Lnk);
    return L;
}

#endif //METNUM_TP1_CHOLESKY_H
