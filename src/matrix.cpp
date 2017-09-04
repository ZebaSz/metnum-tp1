#include "matrix.h"

namespace Matrix {
    matrix<int> identityMatrix(int size) {
        matrix<int> mx;
        for (int i = 0; i < size; ++i) {
            row<int> r;
            for (int j = 0; j < size; ++j) {
                r.push_back((i == j) ? 1 : 0);
            }
            mx.push_back(r);
        }
        return mx;
    }
}