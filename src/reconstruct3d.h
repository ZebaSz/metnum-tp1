#ifndef METNUM_TP1_RECONSTRUCT3D_H
#define METNUM_TP1_RECONSTRUCT3D_H


#include "matrix.h"
#include "gauss.h"
#include "calibration.h"

matrix<double> sourceOfLightMatrix(const direction &s1, const direction &s2, const direction &s3) {
    return {
            {s1.x, s2.x, s3.x},
            {s1.y, s2.y, s3.y},
            {s1.z, s2.z, s3.z}
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
 */

/**
 * Construction of the normal field, for each pixel
 * (step 5 and 6)
 *
 * @param i1, i2, i3 the matrix with the brightness on each pixel for the 3 images
 * @param s1, s2, s3 the source of light for the images
 * @return the normal field of the image
 */
matrix<row<double>> normalField(const matrix<double> &i1, const matrix<double> &i2, const matrix<double> &i3,
                                const direction &s1, const direction &s2, const direction &s3) {
    size_t height = i1.size(), width = i1[0].size();
    PLUMatrix<double> sm = gaussian_elimination(sourceOfLightMatrix(s1, s2, s3));
    matrix<row<double>> normal;

    for (size_t i = 0; i < height; i++) {
        row<row<double>> r;
        for (size_t j = 0; j < width; j++) {
            //(5)
            row<double> m = Matrix::solvePLUSystem(sm.P, sm.L, sm.U, {i1[i][j], i2[i][j], i3[i][j]});
            //(6)
            double mNorm = Matrix::twoNorm({m}); //norma de m
            m[0] /= mNorm;
            m[1] /= mNorm;
            m[2] /= mNorm;
            r.push_back(m);
        }
        normal.push_back(r);
    }
    return normal;
}


#endif //METNUM_TP1_RECONSTRUCT3D_H
