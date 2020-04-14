#ifndef JACOBISYSTEMSOLVER
#define JACOBISYSTEMSOLVER

using Line = std::vector<double>;
using Matrix = std::vector<Line>;

class JacobiSystemSolver {
public:
    explicit JacobiSystemSolver(double eps);

    void findSolution(Matrix const &, Line const &, Line &);

private:
    double mEps;
};

#endif