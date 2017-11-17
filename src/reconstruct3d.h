#ifndef METNUM_TP1_RECONSTRUCT3D_H
#define METNUM_TP1_RECONSTRUCT3D_H


#include "matrix.h"
#include "plu.h"
#include "cholesky.h"
#include "calibration.h"
#include "sparse_matrix.h"
#include <cmath>

struct options {
    options(bool maskOptimization) : maskOptimization(maskOptimization) {}
    bool maskOptimization;
};

struct sparseMatrixVAndValidPixels{
    sparseMatrixVAndValidPixels(sparse_matrix m, row<double> v, row<size_t> validPixels) : matrix(m), v(v), validPixels(validPixels) {}
    sparse_matrix matrix;
    row<size_t> validPixels;
    row<double> v;
};

matrix<double> sourceOfLightMatrix(const direction &s1, const direction &s2, const direction &s3) {
    return {
            {s1.x, s1.y, s1.z},
            {s2.x, s2.y, s2.z},
            {s3.x, s3.y, s3.z}
    };
}
/**
 * (5):
 * for each pixel
 *  /s1x s2x s3x \  /mx \    /I1 \
 * | s1y s2y s3y | | my | = | I2 |
 * \ s1z s2z s3z/  \ mz/    \ I3/
 *
 *
 * (6)
 * agarrar el vector de m y a cada componente la dividis por la norma m
 *
 * Construction of the normal field, for each pixel
 *
 * @param i1, i2, i3 the matrix with the brightness on each pixel for the 3 images
 * @param s1, s2, s3 the source of light for the images
 * @return the normal field of the image
 */
matrix<row<double>> normalField(const matrix<double> &i1, const matrix<double> &i2, const matrix<double> &i3,
                                const direction &s1, const direction &s2, const direction &s3, options opts) {
    size_t height = i1.size(), width = i1[0].size();
    PLUMatrix<double> sm = pluFactorization(sourceOfLightMatrix(s1, s2, s3));
    matrix<row<double>> normal;

    for (size_t i = 0; i < height; i++) {
        row<row<double>> r;
        for (size_t j = 0; j < width; j++) {
            if (opts.maskOptimization && (i1[i][j] == 0 && i2[i][j] == 0 && i3[i][j] == 0)) {
                r.push_back({0, 0, 0}); //TODO: revisen esto
            } else {
                //(5)
                row<double> m = Matrix::solvePLUSystem(sm.P, sm.L, sm.U, {i1[i][j], i2[i][j], i3[i][j]});
                //(6)
                double mNorm = Matrix::twoNorm(m);
                if(mNorm != 0) {
                    m[0] /= mNorm;
                    m[1] /= mNorm;
                    m[2] /= mNorm;
                }
                r.push_back(m);
            }
        }
        normal.push_back(r);
    }

    return normal;
}

sparseMatrixVAndValidPixels calculateM(const matrix<row<double>> &n) {
    size_t height = n.size();
    size_t width = n[0].size();
    size_t n_size = width * height;
    sparse_matrix M(2*n_size, n_size);
    size_t n_i = 0;
    size_t column_number = 0;
    vector<double> v;

    row<size_t> validPixels(0);

    // En la construccion de la M hay que salvar los bordes que no tienen posicion borde+1.
    for (size_t x = 0; x < width; x++) {
        for (size_t y = 0; y < height - 1; y++) {
            if (std::abs(n[y][x][2]) > 0.001) {
                M.set(column_number, n_i, -n[y][x][2]); //le pongo -nz
                M.set(column_number + 1, n_i, n[y][x][2]); //le pongo nz
                v.push_back(-n[y][x][1]); //le pongo -ny
                validPixels.push_back(column_number);
                n_i++;
            }
            column_number++;
        }
    }


    column_number = 0;  // arrancamos de nuevo de la columa 0, pero usamos un offset de filas

    for (size_t x = 0; x < width - 1; x++) {
        for (size_t y = 0; y < height; y++) {
            if (std::abs(n[y][x][2]) > 0.001) {
                M.set(column_number, n_i, -n[y][x][2]); //le pongo -nz
                M.set(column_number + height, n_i, n[y][x][2]); //le pongo nz
                v.push_back(-n[y][x][0]); //le pongo -nx
                n_i++;
            }
            column_number++;
        }
    }

    M.resizeHeight(n_i);

    for (size_t pixel_number = 0; pixel_number < M.getCols(); ++pixel_number) {
        auto & colI = M.column(pixel_number);
        if (colI.empty()) {
            M.removeColumn(pixel_number);
        }
    }

    return sparseMatrixVAndValidPixels(M,v,validPixels);
}

vector<double> calculateV(const matrix<row<double>> &n, const row<size_t> &rowsOfZeros) {
    size_t height = n.size(), width = n[0].size();
    auto rowsOfZerosIt = rowsOfZeros.begin();
    vector<double> v;
    for (size_t x = 0; x < width; x++) {
        for (size_t y = 0; y < height; y++) {
            if (v.size()+1 == *rowsOfZerosIt || v.size() == *rowsOfZerosIt) { // Este or es para el 0,0
                rowsOfZerosIt++;
            } else {
                v.push_back(-n[y][x][1]); //le pongo -ny
            }
        }
    }
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            if (v.size()+1 == *rowsOfZerosIt) {
                rowsOfZerosIt++;
            } else {
                v.push_back(-n[y][x][0]); //le pongo -nx

            }
        }
    }
    return v;
}

row<double> addZeros(row<double> &z, row<size_t> &rowsWithZeros) {
    row<double> result(z.size() + rowsWithZeros.size(), 0);
    auto rowsWithZerosIt = rowsWithZeros.begin();
    auto zIt = z.begin();
    for (size_t i = 0; i < result.size(); ++i) {
        if (*rowsWithZerosIt != i) {
            result[i] = *zIt;
            zIt++;
        } else {
            rowsWithZerosIt++;
        };
    }
    return result;
}

matrix<double> solutionToMatrix(row<double> &z, size_t height, size_t width) {
    matrix<double> result(height, row<double>(width));
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            result[i][j] = z[i + j * height];
        }
    }
    return result;
}

//Aqui viene lo bueno jovenes, I cho cho choleskyou
matrix<double> findDepth(const matrix<row<double>> &normalField) {
    std::cout << "Antes de calcular M" << std::endl;
    sparseMatrixVAndValidPixels mAndVectorOfRowsOfZeros = calculateM(normalField);

    //std::cout << "Despues de calcular M y antes de V" << std::endl;
    //vector<double> v = calculateV(normalField, mAndVectorOfRowsOfZeros.rowsOfZeros);

    std::cout << "Despues de calcular V y antes de calcular MtM" << std::endl;
    // Calcular Mtraspuesta*M : Step 14a
    sparse_matrix mtm = mAndVectorOfRowsOfZeros.matrix.transposedByNotTransposedProduct();

    std::cout << "Despues de calcular MtM y antes de calcular Mtv" << std::endl;
    // Calcular Mtraspuesta*V : Step 14b
    row<double> b = mAndVectorOfRowsOfZeros.matrix.transposedProductWithVector(mAndVectorOfRowsOfZeros.v);

    std::cout << "Despues de calcular Mtv" << std::endl;
    // Choleskiar Az=b : Step 15

    std::cout << "Antes de factorizar" << std::endl;
    sparse_matrix L = sparse_cholesky_factorization(mtm);

    std::cout << "Despues de factorizar y antes de resolver" << std::endl;
    row<double> z = L.solveCholeskySystem(b);

    std::cout << "Despues de choleskiar y antes de transformar vector a matriz" << std::endl;
    // z tiene forma (z11,z12,...,z1h,z21,z22,...,z2h,z31,...,zwh)
    size_t height = normalField.size();
    size_t width = normalField[0].size();
    row<double> zWithZeros = addZeros(z, mAndVectorOfRowsOfZeros.validPixels);
    matrix<double> d = solutionToMatrix(zWithZeros, height, width);

    std::cout << "Despues de transformar vector a matriz" << std::endl;
    return d;
}

#endif //METNUM_TP1_RECONSTRUCT3D_H
