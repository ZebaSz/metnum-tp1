#include <gtest/gtest.h>
#include "../src/matrix.h"
#include "../src/gauss.h"

TEST(GaussTest, lower_triangle) {
    matrix<int> m(5, row<int>(5, 0));
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j <= i; ++j) {
            m[i][j] = 1;
        }
    }
    PLUMatrix<int> plu = gaussian_elimination(m);
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m[i].size(); ++j) {
            ASSERT_EQ(plu.U[i][j], i == j ? 1 : 0) << "i=" << i << ",j=" << j;
        }
    }
}

TEST(GaussTest, lower_triangle_with_gap) {
    size_t gap_row = 2;
    matrix<int> m(5, row<int>(5, 0));
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j <= i; ++j) {
            if (i != gap_row) {
                m[i][j] = 1;
            }
        }
    }
    // Input matrix:
    // [1, 0, 0, 0, 0]
    // [1, 1, 0, 0, 0]
    // [0, 0, 0, 0, 0]
    // [1, 1, 1, 1, 0]
    // [1, 1, 1, 1, 1]
    PLUMatrix<int> plu = gaussian_elimination(m);

    // Expected output matrix:
    // [1, 0, 0, 0, 0]
    // [0, 1, 0, 0, 0]
    // [0, 0, 1, 1, 0]
    // [0, 0, 0, 0, 0]
    // [0, 0, 0, 0, 1]
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m[i].size(); ++j) {
            if((i == j && i < 3) || (i == 2 && j == 3) || (i == 4 && j == 4)) {
                ASSERT_EQ(plu.U[i][j], 1) << "i=" << i << ",j=" << j;
            } else {
                ASSERT_EQ(plu.U[i][j], 0) << "i=" << i << ",j=" << j;
            }
        }
    }
    ASSERT_EQ(Matrix::dotProduct(plu.P,m), Matrix::dotProduct(plu.L, plu.U));
}

TEST(GaussTest, disordred) {
    int** arr = new int*[3];
    arr[0] = new int[3]{0,1,2};
    arr[1] = new int[3]{1,0,0};
    arr[2] = new int[3]{0,1,0};

    matrix<int> m = Matrix::fromArr(arr, 3, 3);
    PLUMatrix<int> plu = gaussian_elimination(m);

    for (int i = 0; i < 3; ++i) {
        delete[] arr[i];
    }
    arr[0] = new int[3]{1,0,0};
    arr[1] = new int[3]{0,1,2};
    arr[2] = new int[3]{0,0,-2};
    ASSERT_EQ(Matrix::fromArr(arr, 3, 3), plu.U);
    ASSERT_EQ(Matrix::dotProduct(plu.P,m), Matrix::dotProduct(plu.L, plu.U));

    for (int i = 0; i < 3; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

TEST(GaussTest, floatValues) {
    matrix<double> mx = {
        {0.41189958311278135,  0.63501185729887122, 0.65352786820559916},
        {0.063395811150194117, 0.25358324460077647, 0.96523391423341098},
        {-0.10881804865464406, 0.52734900501865967, 0.84265156452286083}
    };

    PLUMatrix<double> plu = gaussian_elimination(mx);
    ASSERT_TRUE(Matrix::isUpperTriangular(plu.U));
    ASSERT_TRUE(Matrix::isLowerTriangular(plu.L));
    ASSERT_EQ(Matrix::dotProduct(plu.P,mx), Matrix::dotProduct(plu.L, plu.U));
}
