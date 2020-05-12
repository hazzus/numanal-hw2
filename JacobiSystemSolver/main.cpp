#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <fstream>

#include "JacobiSystemSolver.h"

#define LINE_SIZE 10

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
        double matrix_norm = 0.5,
        int indent = 14) {
    std::cout << "With start approach\n";
    for (auto element : approach) {
        std::cout << element << " ";
    }
    std::cout << '\n';
    std::cout << std::fixed << std::setprecision(10);

    jacobiSystemSolver.findSolution(coefs, freeVars, approach, matrix_norm);

    std::cout << "Solution\n";
    for (auto element : approach) {
        std::cout << element << " ";
    }

    std::cout << std::endl;
    std::cout << "Multilication result\n";
    for (int i = 0; i < LINE_SIZE; ++i) {
        double accum = 0;
        for (int j = 0; j < LINE_SIZE; ++j) {
            accum += coefs[i][j] * approach[j];
        }
        std::cout << accum << " "; 
    }
    
    std::cout << std::defaultfloat;
    std::cout << "\n\n";
}

int main() {
    srand(time(nullptr));

    JacobiSystemSolver jacobiSystemSolver(1e-6, 1000);

    std::cout << "Good conditional matrix\n";
    std::ifstream inp_random = std::ifstream("../matrices/random");
    std::ifstream inp_dominated = std::ifstream("../matrices/dominated");
    std::ifstream inp_hilbert = std::ifstream("../matrices/hilbert");
    int i;
    inp_dominated >> i;
    Matrix conditionCoefs(LINE_SIZE, Line(LINE_SIZE));
    for (int i = 0; i < LINE_SIZE; ++i) {
        for (int j = 0; j < LINE_SIZE; ++j) {
            inp_dominated >> conditionCoefs[i][j]; 
        }
    }

    Line conditionFreeVars(LINE_SIZE);
    for (int i = 0; i < LINE_SIZE; ++i) {
        inp_dominated >> conditionFreeVars[i];
    }

    Line conditionStart(LINE_SIZE);
   // fillLineWithRandom(conditionStart, 0, 1);

    computeAndPrintInfo(jacobiSystemSolver, conditionCoefs, conditionFreeVars, conditionStart, 0.73477, 10);

    std::cout << "Hilbert matrix case\n";
    inp_hilbert >> i;
    Matrix hilbertCoefs(LINE_SIZE, Line(LINE_SIZE));
    for (int i = 0; i < LINE_SIZE; ++i) {
        for (int j = 0; j < LINE_SIZE; ++j) {
            inp_hilbert >> hilbertCoefs[i][j];
        }
    }

    Line hilbertFreeVars(LINE_SIZE);
    for (int i = 0; i < LINE_SIZE; ++i) {
        inp_hilbert >> hilbertFreeVars[i];
    }

    Line hilbertStart(LINE_SIZE);
    //fillLineWithRandom(hilbertStart, 0, 1);

    computeAndPrintInfo(jacobiSystemSolver, hilbertCoefs, hilbertFreeVars, hilbertStart);

    std::cout << "Random elements case\n";
    Matrix randomCoefs(LINE_SIZE, Line(LINE_SIZE));
    inp_random >> i;
    for (int i = 0; i < LINE_SIZE; ++i) {
        for (int j = 0; j < LINE_SIZE; ++j) {
            inp_random >> randomCoefs[i][j];
        }
    }

    Line randomFreeVars(LINE_SIZE);
    for (int i = 0; i < LINE_SIZE; ++i) {
        inp_random >> randomFreeVars[i];
    }
    Line randomStart(LINE_SIZE);
    //fillLineWithRandom(randomStart, 0, 1);

    computeAndPrintInfo(jacobiSystemSolver, randomCoefs, randomFreeVars, randomStart);
    return 0;
}
