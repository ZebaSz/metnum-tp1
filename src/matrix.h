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

typedef std::size_t size_t;

namespace Matrix {

    template<typename T>
    matrix<T> fromArr(T **arr, int height, int width) {
        matrix<T> mx;
        for (int i = 0; i < height; ++i) {
            row<T> r;
            for (int j = 0; j < width; ++j) {
                r.push_back(arr[i][j]);
            }
            mx.push_back(r);
        }
        return mx;
    }

    template<typename T>
    int rows(const matrix<T> &m) {
        return m.size();
    }

    template<typename T>
    int columns(const matrix<T> &m) {
        return m[0].size();
    }

    template<typename T>
    matrix<T> dotProduct(const matrix<T> &a, const matrix<T> &b) {
        assert(!a.empty());
        assert(!b.empty());
        assert(!a[0].empty());
        assert(!b[0].empty());
        assert(a[0].size() == b.size());

        size_t rows = a.size(), columns = b[0].size();
        matrix<T> result(rows, row<T>(columns, 0));

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                for (size_t k = 0; k < b.size(); ++k) {
                    result[i][j] += a[i][k] * b[k][j];
                }
            }
        }

        return result;
    }

    template<typename T>
    matrix<T> traspose(const matrix<T> &m) {
        assert(!(m.empty() || m[0].empty()));
        matrix<T> result(m[0].size(), row<T>(m.size(), 0));

        for (size_t i = 0; i < m.size(); ++i) {
            for (size_t j = 0; j < m[i].size(); ++j) {
                result[j][i] = m[i][j];
            }
        }

        return result;
    }

    template<typename T>
    matrix<T> trasposedProduct(const matrix<T> &m) {
        assert(!(m.empty() || m[0].empty()));

        size_t rows = m.size();
        matrix<T> result(rows, row<T>(rows, 0));

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j <= i; ++j) {
                for (size_t k = 0; k < m.size(); ++k) {
                    result[i][j] += m[i][k] * m[j][k];
                }
                if (i != j) {
                    result[j][i] = result[i][j];
                }
            }
        }

        return result;
    }

    template<typename T>
    T infinityNorm(const matrix<T> &matrix1) {
        assert (!matrix1.empty() && !matrix1[0].empty());
        T result = matrix1[0][0];
        for (size_t i = 0; i < matrix1.size(); ++i) {
            for (size_t j = 0; j < matrix1[i].size(); ++j) {
                if (result < matrix1[i][j]) {
                    result = matrix1[i][j];
                }
            }
        }
        return result;
    }

    template<typename T>
    T twoNorm(const matrix<T> &matrix1) {
        T result = 0;
        for (size_t i = 0; i < matrix1.size(); ++i) {
            T c = 0.0;
            for (size_t j = 0; j < matrix1[i].size(); ++j) {
                // Super Kahan2!!
                T y = pow(matrix1[i][j], 2) - c;
                T t = result + y;
                c = (t - result) - y;
                result = t;
            }
        }
        return sqrt(result);
    }

    template<typename T>
    T singleNorm(const matrix<T> &matrix1) {
        T result = 0;
        for (size_t i = 0; i < matrix1.size(); ++i) {
            T c = 0.0;
            for (size_t j = 0; j < matrix1[i].size(); ++j) {
                // Super Kahan!!
                T y = matrix1[i][j] - c;
                T t = result + y;
                c = (t - result) - y;
                result = t;
            }
        }
        return result;
    }

    template<typename T>
    bool isSquared(const matrix<T> &m) {
        size_t n = m.size();
        for (size_t i = 0; i < n; ++i) {
            if (m[i].size() != n)
                return false;
        }
        return true;
    }

    template<typename T>
    bool isLowerTriangular(const matrix<T> &m) {
        size_t n = m.size();
        for (size_t i = 0; i < n; ++i) {
            size_t mDimension = m[i].size();
            if (n != mDimension) {
                return false;
            }
            for (size_t j = i+1; j < mDimension; ++j) {
                if (m[i][j] != 0) {
                    return false;
                }
            }
        }
        return true;
    }

    template<typename T>
    bool isUpperTriangular(const matrix<T> &m) {
        size_t n = m.size();
        for (size_t i = 0; i < n; ++i) {
            size_t mDimension = m[i].size();
            if (n != mDimension) {
                return false;
            }
            for (size_t j = 0; j < i; ++j) {
                if (m[i][j] != 0) {
                    return false;
                }
            }
        }
        return true;
    }

    template<typename T>
    bool isSymmetric(const matrix<T> &m) {
        assert(isSquared(m));

        size_t n = m.size();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < i; ++j) {
                if (m[i][j] != m[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }


    // This should solve Ax=b and return x for lower triangular squared systems
    template<typename T>
    row<T> solveLowerTriangularSquaredSystem(const matrix<T> &A, const row<T> &b){
        assert(isLowerTriangular(A));

        size_t solution_size = A.size();
        row<T> solution(solution_size, 0);
        for (size_t i = 0; i < solution_size; ++i) {
            T sumOfRowI = 0;
            T c = 0.0;
            for (size_t j = 0; j < i; ++j) {
                T y = (A[i][j] * solution[j])-c;
                T t = sumOfRowI + y;
                c = (t - sumOfRowI) - y;
                sumOfRowI = t;
            }
            solution[i] = (b[i] - sumOfRowI) / A[i][i];
        }

        return solution;
    }

    // This should solve Ax=b and return x for upper triangular squared systems
    template<typename T>
    row<T> solveUpperTriangularSquaredSystem(const matrix<T> &A, const row<T> &b){
        assert(isUpperTriangular(A));

        size_t solution_size = A.size();
        row<T> solution(solution_size, 0);
        for (int i = solution_size-1; i >= 0; --i) {
            T sumOfRowI = 0;
            T c = 0.0;
            for (int j = solution_size-1; j > i; --j) {
                T y = (A[i][j] * solution[j])-c;
                T t = sumOfRowI + y;
                c = (t - sumOfRowI) - y;
                sumOfRowI = t;
            }
            solution[i] = (b[i] - sumOfRowI) / A[i][i];
        }

        return solution;
    }

    /*
     * This should solve LUx=b and return x for LU systems
     * LUx = b
     * 1) Ly = b
     * 2) Ux = y
     */
    template<typename T>
    row<T> solveLUSystem(const matrix<T> &L, const matrix<T> &U, const row<T> &b){
        assert(isLowerTriangular(L));
        assert(isUpperTriangular(U));

        row<T> y = solveLowerTriangularSquaredSystem(L, b);
        row<T> x = solveUpperTriangularSquaredSystem(U, y);

        return x;
    }



    matrix<int> identityMatrix(int size);

}

#endif //METNUM_TP1_MATRIX_H
