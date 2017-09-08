#ifndef METNUM_TP1_SPARSE_MATRIX_H
#define METNUM_TP1_SPARSE_MATRIX_H

#include <map>
#include "matrix.h"

using namespace std;

class sparse_matrix {

    public:
        sparse_matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {}

        size_t getRows() const {
            return rows;
        }

        size_t getCols() const {
            return cols;
        }

        double get(size_t x, size_t y) const {
            auto x_map = matrix.find(x);
            if (x_map != matrix.end()) {
                auto y_map = x_map->second.find(y);
                return (y_map != x_map->second.end()) ? y_map->second : 0;
            } else {
                return 0;
            }
        }

        void set(size_t x, size_t y, double num) {
            auto x_map = matrix.find(x);
            if (x_map != matrix.end()) {
                x_map->second.insert(std::pair<size_t, double>(y, num));
            } else {
                map<size_t, double> ins;
                ins.insert(std::pair<size_t, double>(y, num));
                matrix.insert(std::pair<size_t, map<size_t, double>>(x, ins));
            }
        }
    private:
        size_t rows;
        size_t cols;
        map<size_t, map<size_t,double>> matrix;
};


#endif //METNUM_TP1_SPARSE_MATRIX_H
