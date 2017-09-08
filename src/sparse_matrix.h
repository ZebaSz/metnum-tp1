#ifndef METNUM_TP1_SPARSE_MATRIX_H
#define METNUM_TP1_SPARSE_MATRIX_H

#include <map>
#include <algorithm>
#include "matrix.h"

using namespace std;

class sparse_matrix {

    public:
        sparse_matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
            trans = false;
        }

        size_t getRows() const {
            return (trans) ? cols : rows;
        }

        size_t getCols() const {
            return (trans) ? rows : cols;
        }

        double get(size_t x, size_t y) const {
            if (trans){
                size_t w = x; x = y; y = w;
            }
            auto x_map = matrix.find(x);
            if (x_map != matrix.end()) {
                auto y_map = x_map->second.find(y);
                return (y_map != x_map->second.end()) ? y_map->second : 0;
            } else {
                return 0;
            }
        }

        void set(size_t x, size_t y, double num) {
            if (trans){
                size_t w = x; x = y; y = w;
            }
            auto x_map = matrix.find(x);
            if (x_map != matrix.end()) {
                x_map->second.insert(std::pair<size_t, double>(y, num));
            } else {
                map<size_t, double> ins;
                ins.insert(std::pair<size_t, double>(y, num));
                matrix.insert(std::pair<size_t, map<size_t, double>>(x, ins));
            }
        }

        void transponse() {
            trans = !trans;
        }

    private:
        bool trans;
        size_t rows;
        size_t cols;
        map<size_t, map<size_t,double>> matrix;
};


#endif //METNUM_TP1_SPARSE_MATRIX_H
