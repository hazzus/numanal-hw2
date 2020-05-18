//
// Created by polinb on 17.04.2020.
//

#pragma once

#include <vector>
#include <cmath>
#include <cstddef>

using SquareMatrix = std::vector<std::vector<double>>;
using Column = std::vector<double>;

class SeidelSolver {
public:
    explicit SeidelSolver(double eps = 0.001, size_t matrix_size = 10);

    Column getSolution(const SquareMatrix& a, const Column& b) const;
private:
    Column getStartSolution() const;
    Column copyColumn(const Column& c) const;
    bool checkEnd(const Column& x, const Column& prev) const;
    SquareMatrix transposeMatrix(const SquareMatrix& matrix) const;
    SquareMatrix multiplyTwoSquareMatrix(const SquareMatrix& matrix1, const SquareMatrix& matrix2) const;
    Column multiplyMatrixAndColumn(const SquareMatrix& matrix, const Column& column) const;
    void printMatrix(const SquareMatrix& matrix) const;
    void printColumn(const Column& column) const;
    void normalizeMatrixAndColumn(SquareMatrix& matrix, Column& column) const;

    double eps;
    size_t matrix_size;
};
