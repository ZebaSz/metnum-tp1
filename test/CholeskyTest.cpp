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

TEST(CholeskyTest, cannotFactorizeNonSymmetricMatrix) {
    matrix<float> m(4, row<float>(4, 0));
    m[0][0] = 1; m[0][1] = 1; m[0][2] = 1; m[0][3] = 1;
    m[1][0] = 1; m[1][1] = 2; m[1][2] = 2; m[1][3] = 2;
    m[2][0] = 2; m[2][1] = 2; m[2][2] = 3; m[2][3] = 3;
    m[3][0] = 6; m[3][1] = 2; m[3][2] = 3; m[3][3] = 4;

    ASSERT_DEATH(cholesky_factorization(m), "Assertion");
}