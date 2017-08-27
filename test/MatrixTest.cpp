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
    matrix<int> mx = toMatrix(arr, size, size);
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

    matrix<int> result = dotProduct(a, b);

    ASSERT_EQ(result, expected);

    ASSERT_EQ(dotProduct(a, identityMatrix(3)), a);
    ASSERT_EQ(dotProduct(b, identityMatrix(3)), b);
    ASSERT_EQ(dotProduct(identityMatrix(3), a), a);
    ASSERT_EQ(dotProduct(identityMatrix(3), b), b);

}