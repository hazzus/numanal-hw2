package system.solver;

import system.solver.util.Matrix;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Conjugate gradients method implementation
 * for solving the systems of linear equations
 */
public class Solver {
    private final double EPS = 0.000001;

    private Matrix A;
    private Matrix b;
    private List<Double> iterationsConvergence;

    private int n;

    public Solver(Matrix A, Matrix b) {
        this.A = A;
        this.b = b;
        n = A.getSize().n;
        iterationsConvergence = new ArrayList<>();
    }

    public List<Double> getIterationsConvergence() {
        return iterationsConvergence;
    }

    public Matrix solve() {
        iterationsConvergence.clear();

        Matrix x = new Matrix(Collections.nCopies(n, Collections.singletonList(1.0))); // initial approximation, x0
        iterationsConvergence.add(calculateConvergence(x));

        // iteration 0
        Matrix r = b.subtract(A.multiply(x));
        Matrix p = r;
        double alpha = r.transpose().multiply(r).getOnlyElement() / p.transpose().multiply(A).multiply(p).getOnlyElement();
        x = x.add(p.multiply(alpha));
        iterationsConvergence.add(calculateConvergence(x));

        // other iterations
        while (true) {
            Matrix rPrev = new Matrix(r);
            r = rPrev.subtract(A.multiply(p).multiply(alpha));
            double betta = r.transpose().multiply(r).getOnlyElement() / rPrev.transpose().multiply(rPrev).getOnlyElement();
            p = r.add(p.multiply(betta));
            alpha = r.transpose().multiply(r).getOnlyElement() / p.transpose().multiply(A).multiply(p).getOnlyElement();
            Matrix xPrev = new Matrix(x);
            x = x.add(p.multiply(alpha));
            iterationsConvergence.add(calculateConvergence(x));
            if (x.subtract(xPrev).abs() < EPS) {
                break;
            }
        }

        return x;
    }

    private double calculateConvergence(Matrix x) {
        return A.multiply(x).subtract(b).abs();
    }
}
