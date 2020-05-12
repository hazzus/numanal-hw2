#ifndef JACOBISYSTEMSOLVER
#define JACOBISYSTEMSOLVER

using Line = std::vector<double>;
using Matrix = std::vector<Line>;

class JacobiSystemSolver {
public:
    explicit JacobiSystemSolver(double eps, int maxIterations);

    void findSolution(Matrix const &, Line const &, Line &, double matrixNorm);

private:
    double mEps;
    int mIterations;
};

#endif
