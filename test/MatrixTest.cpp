#include "gtest/gtest.h"
#include "../src/matrix.h"

TEST(MatrixTest, square_array) {
    int size = 5;
    int value = 1;
    int** arr = new int*[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            arr[i][j] = value;
        }
    }
    matrix<int> mx = Matrix::fromArr(arr, size, size);
    ASSERT_EQ(mx.size(), (size_t)size);
    for (size_t i = 0; i < mx.size(); ++i) {
        ASSERT_EQ(mx[i].size(), (size_t)size);
        for (size_t j = 0; j < mx[i].size(); ++j) {
            ASSERT_EQ(mx[i][j], value);
        }
    }

    for (int i = 0; i < size; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

TEST(MatrixTest, dotProduct) {
    matrix<int> a = {
            {2, 0, 1},
            {3, 0, 0},
            {5, 1, 1}};

    matrix<int> b = {
            {1, 0, 1},
            {1, 2, 1},
            {1, 1, 0}};

    matrix<int> expected = {{3, 1, 2},
                            {3, 0, 3},
                            {7, 3, 6}};

    matrix<int> result = Matrix::dotProduct(a, b);

    ASSERT_EQ(Matrix::dotProduct(a, b), expected);

    matrix<int> i3(Matrix::identityMatrix<int>(3));

    ASSERT_EQ(Matrix::dotProduct(a, i3), a);
    ASSERT_EQ(Matrix::dotProduct(b, i3), b);
    ASSERT_EQ(Matrix::dotProduct(i3, a), a);
    ASSERT_EQ(Matrix::dotProduct(i3, b), b);


    a = {{2, 5, 1},
         {4, 3, 1}};

    b = {{1, 0, 0},
         {0, 2, 0},
         {2, 3, 1}};

    expected = {{4, 13, 1},
                {6, 9,  1}};

    ASSERT_EQ(Matrix::dotProduct(a, b), expected);
}

TEST(MatrixTest, sum) {
    matrix<int> a = {
            {2, 0, 1},
            {3, 0, 0},
            {5, 1, 1}};

    matrix<int> b = {
            {1, 0, 1},
            {1, 2, 1},
            {1, 1, 0}};

    matrix<int> expected = {{3, 0, 2},
                            {4, 2, 1},
                            {6, 2, 1}};

    matrix<int> result = Matrix::sum(a, b);

    ASSERT_EQ(result, expected);
}

TEST(MatrixTest, norm){
    int size = 5;
    int value = 1;
    int** arr = new int*[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            arr[i][j] = value;
        }
    }
    matrix<int> mx = Matrix::fromArr(arr, size, size);
    ASSERT_EQ(Matrix::infinityNorm(mx), 1);
    ASSERT_EQ(Matrix::twoNorm(mx), 5);
    ASSERT_EQ(Matrix::singleNorm(mx), 25);
}

TEST(MatrixTest, traspose){
    int size = 5;
    int value = 1;
    int** arr = new int*[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            arr[i][j] = value;
            value++;
        }
    }
    matrix<int> mx = Matrix::fromArr(arr, size, size);
    matrix<int> trasposedMX = Matrix::traspose(mx);
    matrix<int> trasposed_trasposedMX = Matrix::traspose(trasposedMX);

    for (size_t i = 0; i < mx.size(); ++i) {
        for (size_t j = 0; j < mx[i].size(); ++j) {
            ASSERT_EQ(mx[i][j], trasposed_trasposedMX[i][j]);
        }
    }

    int sizeN = 5;
    int sizeM = 6;
    int anotherValue = 1;
    int** notSquared_arr = new int*[sizeM];
    for (int i = 0; i < sizeM; ++i) {
        notSquared_arr[i] = new int[sizeN];
        for (int j = 0; j < sizeN; ++j) {
            notSquared_arr[i][j] = anotherValue;
            anotherValue++;
        }
    }
    matrix<int> notSquared_mx = Matrix::fromArr(notSquared_arr, sizeM, sizeN);
    matrix<int> notSquared_trasposedMX = Matrix::traspose(notSquared_mx);
    matrix<int> trasposed_notSquared_trasposedMX = Matrix::traspose(notSquared_trasposedMX);

    for (size_t i = 0; i < notSquared_mx.size(); ++i) {
        for (size_t j = 0; j < notSquared_mx[i].size(); ++j) {
            ASSERT_EQ(notSquared_mx[i][j], trasposed_notSquared_trasposedMX[i][j]);
        }
    }
}

TEST(MatrixTest, isLowerTriangular) {
    int size = 5;
    int value = 1;
    int** arr = new int*[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            if (j < i+1) {
                arr[i][j] = value;
                value++;
            } else {
                arr[i][j] = 0;
            }
        }
    }
    matrix<int> A = Matrix::fromArr(arr, size, size);
    assert(Matrix::isLowerTriangular(A));
}

TEST(MatrixTest, isUpperTriangular) {
    int size = 5;
    int value = 1;
    int** arr = new int*[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            if (j >= i) {
                arr[i][j] = value;
                value++;
            } else {
                arr[i][j] = 0;
            }
        }
    }
    matrix<int> A = Matrix::fromArr(arr, size, size);
    assert(Matrix::isUpperTriangular(A));
}

TEST(MatrixTest, trasposeProduct) {
    int size = 5;
    int value = 1;
    int** arr = new int*[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            arr[i][j] = value;
            value++;
        }
    }
    matrix<int> mx = Matrix::fromArr(arr, size, size);
    ASSERT_EQ(Matrix::dotProduct(mx, Matrix::traspose(mx)), Matrix::trasposedProduct(mx));
}

TEST(MatrixTest, solveLowerTriangularSquaredSystem) {
    int size = 5;
    double value = 1;
    double** arr = new double*[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            if (j < i+1) {
                arr[i][j] = value;
                value++;
            } else {
                arr[i][j] = 0;
            }
        }
    }
    matrix<double> A = Matrix::fromArr(arr, size, size);
    row<double> b = {15,25,35,45,55};
    double expected0 = 15;
    double expected1 = (25 - (expected0*2))/3;
    double expected2 = (35 - (expected0*4) - (expected1*5))/6;
    double expected3 = (45 - (expected0*7) - (expected1*8) - (expected2*9))/10;
    double expected4 = (55 - (expected0*11) - (expected1*12) - (expected2*13) - (expected3*14))/15;

    row<double> expected = { expected0, expected1, expected2, expected3,  expected4 };
    row<double> result = Matrix::solveLowerTriangularSquaredSystem(A, b);
    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_NEAR(expected[i], result[i], 0.0000001) << "i=" << i;
    }

    matrix<int> C(Matrix::identityMatrix<int>(5));
    row<int> d = { 13, 15, 17, 18, 19};
    row<int> expected_2 = d;
    row<int> result_2 = Matrix::solveLowerTriangularSquaredSystem(C, d);
    for (size_t i = 0; i < expected_2.size(); ++i) {
        ASSERT_EQ(expected_2[i], result_2[i]) << "i=" << i;
    }
}

TEST(MatrixTest, solveUpperTriangularSquaredSystem) {
    int size = 5;
    double value = 1;
    double** arr = new double*[size];
    for (int i = size-1; i >= 0; --i) {
        arr[i] = new double[size];
        for (int j = size-1; j >= 0; --j) {
            if ( j >= i) {
                arr[i][j] = value;
                value++;
            } else {
                arr[i][j] = 0;
            }
        }
    }
    matrix<double> A = Matrix::fromArr(arr, size, size);
    row<double> b = { 55, 45, 35, 25, 15 };
    double expected0 = 15;
    double expected1 = (25 - (expected0*2))/3;
    double expected2 = (35 - (expected0*4) - (expected1*5))/6;
    double expected3 = (45 - (expected0*7) - (expected1*8) - (expected2*9))/10;
    double expected4 = (55 - (expected0*11) - (expected1*12) - (expected2*13) - (expected3*14))/15;

    row<double> expected = { expected4, expected3, expected2, expected1,  expected0 };
    row<double> result = Matrix::solveUpperTriangularSquaredSystem(A, b);
    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_NEAR(expected[i], result[i], 0.0000001) << "i=" << i;
    }

    matrix<int> C(Matrix::identityMatrix<int>(5));
    row<int> d = { 19, 18, 17, 15, 13 };
    row<int> expected_2 = d;
    row<int> result_2 = Matrix::solveUpperTriangularSquaredSystem(C, d);
    for (size_t i = 0; i < expected_2.size(); ++i) {
        ASSERT_EQ(expected_2[i], result_2[i]) << "i=" << i;
    }
}

TEST(MatrixTest, solveLUSystem){
    int size = 5;
    double value = 1;

    double** arr = new double*[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            if (j < i+1) {
                arr[i][j] = value;
                value++;
            } else {
                arr[i][j] = 0;
            }
        }
    }
    matrix<double> L = Matrix::fromArr(arr, size, size);

    double** arr2 = new double*[size];
    for (int i = size-1; i >= 0; --i) {
        arr2[i] = new double[size];
        for (int j = size-1; j >= 0; --j) {
            if ( j >= i) {
                arr2[i][j] = value;
                value++;
            } else {
                arr2[i][j] = 0;
            }
        }
    }
    matrix<double> U = Matrix::fromArr(arr2, size, size);

    row<double> b = { 100, 200, 300, 400, 500 };
    row<double> expected = { 3.34677, 0.77131, 0.00408, -0.10576, -0.77037 };

    row<double> result = Matrix::solveLUSystem(L,U,b);

    for (int k = 0; k < 5; ++k) {
        ASSERT_NEAR(expected[k], result[k], 0.1);
    }
}

TEST(MatrixTest, solveCholeskySystem){
    int size = 5;
    double value = 1;

    double** arr = new double*[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            if (j < i+1) {
                arr[i][j] = value;
                value++;
            } else {
                arr[i][j] = 0;
            }
        }
    }
    matrix<double> L = Matrix::fromArr(arr, size, size);

    row<double> b = { 1, 2, 4, 6, 105 };

    row<double> result = Matrix::solveCholeskySystem(L,b);

    matrix<double> trasposedL = Matrix::traspose(L);

    row<double> result_with_trasposed = Matrix::solveLUSystem(L,trasposedL,b);
    ASSERT_EQ(result_with_trasposed, result);
}