#include <iostream>
#include "SeidelSolver.h"

using namespace std;

int main() {
    /*SquareMatrix matrix = {{3.6, 1.8, -4.7}, {2.7, -3.6, 1.9}, {1.5, 4.5, 3.3}};
    Column b = {3.8, 0.4, -1.6};
    double eps = 0.001;
    SeidelSolver solver(eps, matrix.size());*/
    SquareMatrix matrix = {{0.17,  0.75, -0.18, 0.21},
                           {0.75,  0.13, 0.11,  1},
                           {-0.33, 0.11, 3.01,  -2.01},
                           {0.11,  1.12, 1.11,  -1.31}};
    Column b = {0.11, 2, 0.11, 0.13};
    double eps = 0.0001;
    SeidelSolver solver(eps, matrix.size());
    Column res = solver.getSolution(matrix, b);
    for (size_t i = 0; i < res.size(); ++i) {
        cout << "x" << i + 1 << " = " << res[i] << endl;
    }
    return 0;
}
