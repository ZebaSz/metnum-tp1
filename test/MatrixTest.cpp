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
    matrix<int> mx = toMatrix(arr, size, size);
    ASSERT_EQ(infinityNorm(mx), 1);
    ASSERT_EQ(twoNorm(mx), 5);
    ASSERT_EQ(singleNorm(mx), 25);

}