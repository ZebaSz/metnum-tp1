#ifndef METNUM_TP1_SPARSE_MATRIX_H
#define METNUM_TP1_SPARSE_MATRIX_H

#include <map>
#include <vector>
#include <unordered_map>
#include "matrix.h"

using std::vector;
using std::pair;
using std::make_pair;

typedef std::unordered_map<size_t, double> bucket;

class sparse_matrix {

    public:
        sparse_matrix(size_t rows, size_t cols) : rows(rows), cols(cols), matrix(cols) {
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
            const bucket& x_map = matrix[x];
            auto y_map = x_map.find(y);
            return (y_map != x_map.end()) ? y_map->second : 0;
        }

        void set(size_t x, size_t y, double num) {
            if (trans){
                size_t w = x; x = y; y = w;
            }
            bucket& x_map = matrix[x];
            if (num == 0) {
                x_map.erase(y);
            } else {
                x_map[y] = num;
            }

        }

        void transponse() {
            trans = !trans;
        }

        vector<pair<size_t, size_t>> notZeros() {
            vector<pair<size_t, size_t>> nc;
            for (size_t i = 0; i < cols; ++i) {
                bucket& x = matrix[i];
                for(auto y = x.begin(); y != x.end(); ++y) {
                    pair<size_t, size_t> pair = (trans) ? make_pair(y->first, i) : make_pair(i, y->first);
                    nc.push_back(pair);
                }
            }
            return nc;
        };

        row<double> transposedProductWithVector(const row<double> &b) {
            row<double> result(cols, 0);

            for (size_t i = 0; i < cols; ++i) {
                bucket& column = matrix[i];
                double sum = 0;
                for (auto column_row = column.begin(); column_row != column.end(); ++column_row) {
                    sum += column_row->second * b[column_row->first];
                }
                result[i] = sum;
            }

            return result;
        }

        sparse_matrix transposedByNotTransposedProduct() {
            sparse_matrix result(cols, cols);
            for (size_t i = 0; i < cols; ++i) {
                bucket& column = matrix[i];
                for (size_t j = 0; j <= i; ++j) {
                    bucket& another_column = matrix[j];
                    double sum = 0;
                    for (auto column_row = column.begin(); column_row != column.end(); ++column_row) {
                        auto another_column_row = another_column.find(column_row->first);
                        if(another_column_row != another_column.end()) {
                            sum += column_row->second * another_column_row->second;
                        }
                    }
                    result.set(i,j, sum);
                    if (i != j) {
                        result.set(j, i, sum);
                    }
                }
            }
            return result;
        }


        // Esta funcion asume que la matriz es cuadrada y triangular inferior.
        row<double> solveCholeskySystem(row<double> b){
            // Resuelvo Lz = b
            size_t z_size = b.size();
            row<double> z(z_size, 0);
            for (size_t i = 0; i < cols; ++i) {
                // TODO revisar esto, no son filas
                bucket& row = matrix[i];
                double sumOfRowI = 0;
                double c = 0.0;
                for (auto row_column = row.begin(); row_column != row.end(); row_column++) {
                    double y = (row_column->second * z[row_column->first]) - c;
                    double t = sumOfRowI + y;
                    c = (t - sumOfRowI) - y;
                    sumOfRowI = t;
                }
                z[i] = (b[i] - sumOfRowI) / row[i];
            }

            // Resuelvo L'x = z
            trans = true;
            size_t x_size = z.size();
            row<double> x(x_size, 0);

            for (size_t i = 1; i <= cols; ++i) {
                bucket& row = matrix[cols - i];
                double sumOfRowI = 0;
                double c = 0.0;
                for (auto row_column = row.begin(); row_column != row.end(); row_column++) {
                    double y = (row_column->second * z[row_column->first]) - c;
                    double t = sumOfRowI + y;
                    c = (t - sumOfRowI) - y;
                    sumOfRowI = t;
                }
                x[i] = (z[i] - sumOfRowI) / row[i];
            }
            return x;
        }

        const bucket& column(size_t col) const {
            return matrix[col];
        }

private:
        bool trans;
        size_t rows;
        size_t cols;
        vector<bucket> matrix;
};


#endif //METNUM_TP1_SPARSE_MATRIX_H
