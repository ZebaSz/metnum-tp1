#include <gtest/gtest.h>
#include "../src/matrix.h"
#include "../src/cholesky.h"

TEST(CholeskyTest, factorize2by2Matrix) {
    matrix<float> m(2, row<float>(2, 0));
    m[0][0] = 1; m[0][1] = 1;
    m[1][0] = 1; m[1][1] = 2;

    matrix<float> l = cholesky_factorization(m);
    ASSERT_EQ(l[0][0], 1) << "i=" << 0 << ",j=" << 0;
    ASSERT_EQ(l[0][1], 0) << "i=" << 0 << ",j=" << 1;
    ASSERT_EQ(l[1][0], 1) << "i=" << 1 << ",j=" << 0;
    ASSERT_EQ(l[1][1], 1) << "i=" << 1 << ",j=" << 1;
}

TEST(CholeskyTest, factorize3by3Matrix) {
    matrix<float> m(3, row<float>(3, 0));
    m[0][0] = 1; m[0][1] = 1; m[0][2] = 1;
    m[1][0] = 1; m[1][1] = 2; m[1][2] = 2;
    m[2][0] = 1; m[2][1] = 2; m[2][2] = 3;

    matrix<float> l = cholesky_factorization(m);
    ASSERT_EQ(l[0][0], 1) << "i=" << 0 << ",j=" << 0;
    ASSERT_EQ(l[0][1], 0) << "i=" << 0 << ",j=" << 1;
    ASSERT_EQ(l[0][2], 0) << "i=" << 0 << ",j=" << 2;
    ASSERT_EQ(l[1][0], 1) << "i=" << 1 << ",j=" << 0;
    ASSERT_EQ(l[1][1], 1) << "i=" << 1 << ",j=" << 1;
    ASSERT_EQ(l[1][2], 0) << "i=" << 1 << ",j=" << 2;
    ASSERT_EQ(l[2][0], 1) << "i=" << 2 << ",j=" << 0;
    ASSERT_EQ(l[2][1], 1) << "i=" << 2 << ",j=" << 1;
    ASSERT_EQ(l[2][2], 1) << "i=" << 2 << ",j=" << 2;
}

TEST(CholeskyTest, factorize4by4Matrix) {
    matrix<float> m(4, row<float>(4, 0));
    m[0][0] = 1; m[0][1] = 1; m[0][2] = 1; m[0][3] = 1;
    m[1][0] = 1; m[1][1] = 2; m[1][2] = 2; m[1][3] = 2;
    m[2][0] = 1; m[2][1] = 2; m[2][2] = 3; m[2][3] = 3;
    m[3][0] = 1; m[3][1] = 2; m[3][2] = 3; m[3][3] = 4;

    matrix<float> l = cholesky_factorization(m);
    ASSERT_EQ(l[0][0], 1) << "i=" << 0 << ",j=" << 0;
    ASSERT_EQ(l[0][1], 0) << "i=" << 0 << ",j=" << 1;
    ASSERT_EQ(l[0][2], 0) << "i=" << 0 << ",j=" << 2;
    ASSERT_EQ(l[0][3], 0) << "i=" << 0 << ",j=" << 3;
    ASSERT_EQ(l[1][0], 1) << "i=" << 1 << ",j=" << 0;
    ASSERT_EQ(l[1][1], 1) << "i=" << 1 << ",j=" << 1;
    ASSERT_EQ(l[1][2], 0) << "i=" << 1 << ",j=" << 2;
    ASSERT_EQ(l[1][3], 0) << "i=" << 1 << ",j=" << 3;
    ASSERT_EQ(l[2][0], 1) << "i=" << 2 << ",j=" << 0;
    ASSERT_EQ(l[2][1], 1) << "i=" << 2 << ",j=" << 1;
    ASSERT_EQ(l[2][2], 1) << "i=" << 2 << ",j=" << 2;
    ASSERT_EQ(l[2][3], 0) << "i=" << 2 << ",j=" << 3;
    ASSERT_EQ(l[3][0], 1) << "i=" << 3 << ",j=" << 0;
    ASSERT_EQ(l[3][1], 1) << "i=" << 3 << ",j=" << 1;
    ASSERT_EQ(l[3][2], 1) << "i=" << 3 << ",j=" << 2;
    ASSERT_EQ(l[3][3], 1) << "i=" << 3 << ",j=" << 3;
}

TEST(CholeskyTest, factorize5by5Matrix) {
    matrix<float> m = {
            {5.99246,   0.45174,   0.50921,   0.45632,   0.41578},
            {0.45174,   5.02065,   0.40611,   0.52172,   0.11483},
            {0.50921,   0.40611,   5.25767,   0.78430,   0.24938},
            {0.45632,   0.52172,   0.78430,   5.98219,   0.45188},
            {0.41578,   0.11483,   0.24938,   0.45188,   5.28701}
    };

    matrix<float> l_expected = {
            {2.44795,   0.00000,   0.00000,   0.00000,   0.00000},
            {0.18454,   2.23307,   0.00000,   0.00000,   0.00000},
            {0.20802,   0.16467,   2.27756,   0.00000,   0.00000},
            {0.18641,   0.21823,   0.31156,   2.40889,   0.00000},
            {0.16985,   0.03739,   0.09128,   0.15925,   2.28540}
    };

    matrix<float> l_result = cholesky_factorization(m);
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m.size(); ++j) {
            ASSERT_NEAR(l_expected[j][i], l_result[j][i], 0.00001) << "j=" << j << " ,i=" << i;
        }
    }

    matrix<float> m_result = Matrix::trasposedProduct(l_result);
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m.size(); ++j) {
            ASSERT_NEAR(m[j][i], m_result[j][i], 0.00001) << "j=" << j << " ,i=" << i;
        }
    }
}

TEST(CholeskyTest, factorizeBigMatrix) {
    matrix<float> m = {
            {7.21217, 0.25028, 0.42166, 0.22054, 0.53918, 0.38809, 0.21220},
            {0.25028, 7.99049, 0.21212, 0.46048, 0.47818, 0.85571, 0.41787},
            {0.42166, 0.21212, 7.43058, 0.40467, 0.52578, 0.63224, 0.39279},
            {0.22054, 0.46048, 0.40467, 7.82612, 0.38070, 0.74682, 0.43779},
            {0.53918, 0.47818, 0.52578, 0.38070, 7.82015, 0.72274, 0.35334},
            {0.38809, 0.85571, 0.63224, 0.74682, 0.72274, 7.23679, 0.70013},
            {0.21220, 0.41787, 0.39279, 0.43779, 0.35334, 0.70013, 7.05207}
    };

    matrix<float> l_expected = {
            {2.68555, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000},
            {0.09320, 2.82521, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000},
            {0.15701, 0.06990, 2.72049, 0.00000, 0.00000, 0.00000, 0.00000},
            {0.08212, 0.16028, 0.13989, 2.78821, 0.00000, 0.00000, 0.00000},
            {0.20077, 0.16263, 0.17750, 0.11237, 2.77656, 0.00000, 0.00000},
            {0.14451, 0.29812, 0.21640, 0.23560, 0.20902, 2.64216, 0.00000},
            {0.07901, 0.14530, 0.13609, 0.13951, 0.09869, 0.21288, 2.63281}
    };


    matrix<float> l_result = cholesky_factorization(m);
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m.size(); ++j) {
            ASSERT_NEAR(l_expected[j][i], l_result[j][i], 0.00001) << "j=" << j << " ,i=" << i;
        }
    }

    matrix<float> m_result = Matrix::trasposedProduct(l_result);
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m.size(); ++j) {
            ASSERT_NEAR(m[j][i], m_result[j][i], 0.00001) << "j=" << j << " ,i=" << i;
        }
    }

}

TEST(CholeskyTest, cannotFactorizeNonSymmetricMatrix) {
    matrix<float> m(4, row<float>(4, 0));
    m[0][0] = 1; m[0][1] = 1; m[0][2] = 1; m[0][3] = 1;
    m[1][0] = 1; m[1][1] = 2; m[1][2] = 2; m[1][3] = 2;
    m[2][0] = 2; m[2][1] = 2; m[2][2] = 3; m[2][3] = 3;
    m[3][0] = 6; m[3][1] = 2; m[3][2] = 3; m[3][3] = 4;

    ASSERT_DEATH(cholesky_factorization(m), "Assertion");
}

TEST(CholeskyTest, factorize3by3SparseMatrix) {
    sparse_matrix m(3, 3);
    m.set(0,0,1); m.set(0,1,1); m.set(0,2,1);
    m.set(1,0,1); m.set(1,1,2); m.set(1,2,2);
    m.set(2,0,1); m.set(2,1,2); m.set(2,2,3);

    sparse_matrix l = sparse_cholesky_factorization(m);
    ASSERT_EQ(l.get(0,0), 1) << "i=" << 0 << ",j=" << 0;
    ASSERT_EQ(l.get(0,1), 0) << "i=" << 0 << ",j=" << 1;
    ASSERT_EQ(l.get(0,2), 0) << "i=" << 0 << ",j=" << 2;
    ASSERT_EQ(l.get(1,0), 1) << "i=" << 1 << ",j=" << 0;
    ASSERT_EQ(l.get(1,1), 1) << "i=" << 1 << ",j=" << 1;
    ASSERT_EQ(l.get(1,2), 0) << "i=" << 1 << ",j=" << 2;
    ASSERT_EQ(l.get(2,0), 1) << "i=" << 2 << ",j=" << 0;
    ASSERT_EQ(l.get(2,1), 1) << "i=" << 2 << ",j=" << 1;
    ASSERT_EQ(l.get(2,2), 1) << "i=" << 2 << ",j=" << 2;
}

TEST(CholeskyTest, anotherFactorize3by3SparseMatrix) {
    sparse_matrix m(3, 3);
    m.set(0,0,4); m.set(0,1,12); m.set(0,2,-16);
    m.set(1,0,12); m.set(1,1,37); m.set(1,2,-43);
    m.set(2,0,-16); m.set(2,1,-43); m.set(2,2,98);

    sparse_matrix l = sparse_cholesky_factorization(m);
    ASSERT_EQ(l.get(0,0), 2) << "i=" << 0 << ",j=" << 0;
    ASSERT_EQ(l.get(0,1), 0) << "i=" << 0 << ",j=" << 1;
    ASSERT_EQ(l.get(0,2), 0) << "i=" << 0 << ",j=" << 2;
    ASSERT_EQ(l.get(1,0), 6) << "i=" << 1 << ",j=" << 0;
    ASSERT_EQ(l.get(1,1), 1) << "i=" << 1 << ",j=" << 1;
    ASSERT_EQ(l.get(1,2), 0) << "i=" << 1 << ",j=" << 2;
    ASSERT_EQ(l.get(2,0), -8) << "i=" << 2 << ",j=" << 0;
    ASSERT_EQ(l.get(2,1), 5) << "i=" << 2 << ",j=" << 1;
    ASSERT_EQ(l.get(2,2), 3) << "i=" << 2 << ",j=" << 2;
}

TEST(CholeskyTest, factorize4by4SparseMatrix) {
    sparse_matrix m(4, 4);
    m.set(0,0,1); m.set(0,1,1); m.set(0,2,1); m.set(0,3,1);
    m.set(1,0,1); m.set(1,1,2); m.set(1,2,2); m.set(1,3,2);
    m.set(2,0,1); m.set(2,1,2); m.set(2,2,3); m.set(2,3,3);
    m.set(3,0,1); m.set(3,1,2); m.set(3,2,3); m.set(3,3,4);

    sparse_matrix l = sparse_cholesky_factorization(m);
    ASSERT_EQ(l.get(0,0), 1) << "i=" << 0 << ",j=" << 0;
    ASSERT_EQ(l.get(0,1), 0) << "i=" << 0 << ",j=" << 1;
    ASSERT_EQ(l.get(0,2), 0) << "i=" << 0 << ",j=" << 2;
    ASSERT_EQ(l.get(0,3), 0) << "i=" << 0 << ",j=" << 3;
    ASSERT_EQ(l.get(1,0), 1) << "i=" << 1 << ",j=" << 0;
    ASSERT_EQ(l.get(1,1), 1) << "i=" << 1 << ",j=" << 1;
    ASSERT_EQ(l.get(1,2), 0) << "i=" << 1 << ",j=" << 2;
    ASSERT_EQ(l.get(1,3), 0) << "i=" << 1 << ",j=" << 3;
    ASSERT_EQ(l.get(2,0), 1) << "i=" << 2 << ",j=" << 0;
    ASSERT_EQ(l.get(2,1), 1) << "i=" << 2 << ",j=" << 1;
    ASSERT_EQ(l.get(2,2), 1) << "i=" << 2 << ",j=" << 2;
    ASSERT_EQ(l.get(2,3), 0) << "i=" << 2 << ",j=" << 3;
    ASSERT_EQ(l.get(3,0), 1) << "i=" << 3 << ",j=" << 0;
    ASSERT_EQ(l.get(3,1), 1) << "i=" << 3 << ",j=" << 1;
    ASSERT_EQ(l.get(3,2), 1) << "i=" << 3 << ",j=" << 2;
    ASSERT_EQ(l.get(3,3), 1) << "i=" << 3 << ",j=" << 3;
}