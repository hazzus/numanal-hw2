#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

#include "JacobiSystemSolver.h"

#define LINE_SIZE 5

std::random_device rd;
std::mt19937 e2(rd());

void fillLineWithRandom(Line &line, double from, double to) {
    std::uniform_real_distribution<> uniformDistribution(from, to);

    for (auto & element : line) {
        element = uniformDistribution(e2);
    }
}

void computeAndPrintInfo(
        JacobiSystemSolver &jacobiSystemSolver,
        Matrix const &coefs,
        Line const &freeVars,
        Line &approach,
        int indent = 14) {
    for (int i = 0; i < LINE_SIZE; ++i) {
        for (int j = 0; j < LINE_SIZE; ++j) {
            std::cout << std::setw(14) << coefs[i][j];
        }
        std::cout << " | " << std::setw(14) << freeVars[i] << '\n';
    }

    std::cout << "With start approach\n";
    for (auto element : approach) {
        std::cout << std::setw(14) << element;
    }
    std::cout << '\n';

    jacobiSystemSolver.findSolution(coefs, freeVars, approach);

    std::cout << "Solution\n";
    for (auto element : approach) {
        std::cout << std::setw(14) << element;
    }
    std::cout << "\n\n";
}

int main() {
    srand(time(nullptr));

    JacobiSystemSolver jacobiSystemSolver(1e-8);

    std::cout << "Good conditional matrix\n";
    Matrix conditionCoefs(LINE_SIZE, Line(LINE_SIZE));
    for (int i = 0; i < LINE_SIZE; ++i) {
        for (int j = 0; j < LINE_SIZE; ++j) {
            if (i == j || rand() % LINE_SIZE > std::abs(i - j)) {
                conditionCoefs[i][j] = (rand() % LINE_SIZE) + 1;
            }
        }
    }

    Line conditionFreeVars(LINE_SIZE);
    fillLineWithRandom(conditionFreeVars, 0, 5);

    Line conditionStart(LINE_SIZE);
    fillLineWithRandom(conditionStart, 0, 5);

    computeAndPrintInfo(jacobiSystemSolver, conditionCoefs, conditionFreeVars, conditionStart);

    std::cout << "Hilbert matrix case\n";
    Matrix hilbertCoefs(LINE_SIZE, Line(LINE_SIZE));
    for (int i = 0; i < LINE_SIZE; ++i) {
        for (int j = 0; j < LINE_SIZE; ++j) {
            hilbertCoefs[i][j] = 1.0 / (1.0 + i + j);
        }
    }

    Line hilbertFreeVars(LINE_SIZE);
    fillLineWithRandom(hilbertFreeVars, 0, 5);

    Line hilbertStart(LINE_SIZE);
    fillLineWithRandom(hilbertStart, 0, 5);

    computeAndPrintInfo(jacobiSystemSolver, hilbertCoefs, hilbertFreeVars, hilbertStart);

    std::cout << "Random elements case\n";
    Matrix randomCoefs(LINE_SIZE, Line(LINE_SIZE));
    for (Line &line : randomCoefs) {
        fillLineWithRandom(line, 0, 1);
    }

    Line randomFreeVars(LINE_SIZE);
    fillLineWithRandom(randomFreeVars, 0, 1);

    Line randomStart(LINE_SIZE);
    fillLineWithRandom(randomStart, 0, 5);

    computeAndPrintInfo(jacobiSystemSolver, randomCoefs, randomFreeVars, randomStart);
    return 0;
}
