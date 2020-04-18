package system.solver;

import system.solver.util.Matrix;

import java.util.Collections;

/**
 * Conjugate gradients method implementation
 * for solving the systems of linear equations
 */
public class Solver {
    private Matrix A;
    private Matrix b;

    private int n;

    public Solver(Matrix A, Matrix b) {
        this.A = A;
        this.b = b;
        n = A.getSize().n;
    }

    public void solve() {
        Matrix x = new Matrix(Collections.nCopies(n, Collections.singletonList(1.0))); // initial approximation, x_0

        // iteration #0
        Matrix r = b.subtract(A.multiply(x));
        Matrix p = r;
        double alpha = r.transpose().multiply(r).getOnlyElement() / p.transpose().multiply(A).multiply(p).getOnlyElement();
        x = x.add(p.multiply(alpha));

        // other n - 1 iterations
        for (int i = 1; i < n; i++) {
            Matrix rPrev = new Matrix(r);
            r = rPrev.subtract(A.multiply(p).multiply(alpha));
            double betta = r.transpose().multiply(r).getOnlyElement() / rPrev.transpose().multiply(rPrev).getOnlyElement();
            p = r.add(p.multiply(betta));
            alpha = r.transpose().multiply(r).getOnlyElement() / p.transpose().multiply(A).multiply(p).getOnlyElement();
            x = x.add(p.multiply(alpha));
        }

        System.out.println(x.getMatrix()); // print the result
    }
}
