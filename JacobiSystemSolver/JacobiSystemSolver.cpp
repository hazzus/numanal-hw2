#include <vector>
#include <cmath>
#include <iostream>

#include "JacobiSystemSolver.h"

#define MAX_NORM 1e9f

JacobiSystemSolver::JacobiSystemSolver(double eps) : mEps(eps) {}

void JacobiSystemSolver::findSolution(Matrix const &coeffs, Line const &freeVars, Line &startApproach) {
    unsigned int lineSize = startApproach.size();

    Line tempApproach(lineSize);
    double norm;

    do {
        for (int i = 0; i < lineSize; ++i) {
            tempApproach[i] = freeVars[i];
            for (int j = 0; j < lineSize; ++j) {
                if (i != j) {
                    tempApproach[i] -= coeffs[i][j] * startApproach[j];
                }
                tempApproach[i] /= coeffs[i][i];
            }
        }
        norm = fabs(startApproach[0] - tempApproach[0]);
        for (int i = 0; i < lineSize; ++i) {
            norm = std::max(norm, fabs(startApproach[i] - tempApproach[i]));
            startApproach[i] = tempApproach[i];
        }
        if (norm > MAX_NORM) {
            std::cout << "Impossible to solve!\n";
            norm = 0;
            for (auto & element : startApproach) {
                element = 0;
            }
        }
    } while (norm > mEps);
}
