//
// Created by polinb on 17.04.2020.
//

#include <stdexcept>
#include <iostream>
#include "SeidelSolver.h"

Column SeidelSolver::getSolution(const SquareMatrix &a, const Column &b) const {
    Column x = getStartSolution();
    SquareMatrix a_t = transposeMatrix(a);
    SquareMatrix a_new = multiplyTwoSquareMatrix(a_t, a);
    Column b_new = multiplyMatrixAndColumn(a_t, b);
    normalizeMatrixAndColumn(a_new, b_new);
    while (true) {
        Column prev = copyColumn(x);
        for (int i = 0; i < matrix_size; ++i) {
            double var = 0;
            for (int j = 0; j < i; j++)
                var += (a_new[i][j] * x[j]);
            for (int j = i + 1; j < matrix_size; j++)
                var += (a_new[i][j] * prev[j]);
            x[i] = b_new[i] - var;
        }
        if (checkEnd(x, prev)) {
            return x;
        }
    }
}

SeidelSolver::SeidelSolver(double eps, size_t matrix_size) : eps(eps), matrix_size(matrix_size) {}

Column SeidelSolver::getStartSolution() const {
    return Column(matrix_size, 0.0);
}

Column SeidelSolver::copyColumn(const Column &c) const {
    return c;
}

bool SeidelSolver::checkEnd(const Column &x, const Column &prev) const {
    double sum = 0;
    for (size_t i = 0; i < matrix_size; ++i)
        sum += (x[i] - prev[i]) * (x[i] - prev[i]);
    return (sqrt(sum) < eps);
}

SquareMatrix SeidelSolver::transposeMatrix(const SquareMatrix &matrix) const {
    SquareMatrix res(matrix_size, Column(matrix_size, 0));
    for (size_t i = 0; i < matrix_size; ++i) {
        for (size_t j = 0; j < matrix_size; ++j) {
            res[i][j] = matrix[j][i];
        }
    }
    return res;
}

SquareMatrix SeidelSolver::multiplyTwoSquareMatrix(const SquareMatrix &matrix1, const SquareMatrix &matrix2) const {
    SquareMatrix res(matrix_size, Column(matrix_size, 0));
    for (size_t i = 0; i < matrix_size; ++i) {
        for (size_t j = 0; j < matrix_size; ++j) {
            double sum = 0;
            for (size_t k = 0; k < matrix_size; ++k) {
                sum += (matrix1[i][k] * matrix2[k][j]);
            }
            res[i][j] = sum;
        }
    }
    return res;
}

Column SeidelSolver::multiplyMatrixAndColumn(const SquareMatrix &matrix, const Column &column) const {
    Column res(matrix_size, 0);
    for (size_t i = 0; i < matrix_size; ++i) {
        double sum = 0;
        for (size_t j = 0; j < matrix_size; ++j) {
            sum += (matrix[i][j] * column[j]);
        }
        res[i] = sum;
    }
    return res;
}

void SeidelSolver::printMatrix(const SquareMatrix &matrix) const {
    std::cout << "--MATRIX--" << std::endl;
    for (size_t i = 0; i < matrix_size; ++i) {
        for (size_t j = 0; j < matrix_size; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void SeidelSolver::printColumn(const Column &column) const {
    std::cout << "--COLUMN--" << std::endl;
    for (size_t i = 0; i < matrix_size; ++i) {
        std::cout << column[i] << " ";
    }
    std::cout << std::endl;
}

void SeidelSolver::normalizeMatrixAndColumn(SquareMatrix &matrix, Column& column) const {
    Column normal_vec(matrix_size);
    for (size_t i = 0; i < matrix_size; ++i) {
        normal_vec[i] = matrix[i][i];
    }
    for (size_t i = 0; i < matrix_size; ++i) {
        for (size_t j = 0; j < matrix_size; ++j) {
            matrix[i][j] /= normal_vec[i];
        }
        column[i] /= normal_vec[i];
    }
}


