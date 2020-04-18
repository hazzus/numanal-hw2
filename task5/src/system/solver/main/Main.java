package system.solver.main;

import system.solver.util.Matrix;
import system.solver.Solver;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<List<Double>> table = new ArrayList<>() {{ // example matrix A
            add(new ArrayList<>() {{ add(2.0); add(1.0); add(1.0); add(4.0); }});
            add(new ArrayList<>() {{ add(1.0); add(-1.0); add(0.0); add(2.0); }});
            add(new ArrayList<>() {{ add(1.0); add(0.0); add(2.0); add(5.0); }});
            add(new ArrayList<>() {{ add(4.0); add(2.0); add(5.0); add(-2.0); }});
        }};

        List<List<Double>> bTable = new ArrayList<>() {{ // example vector (which is considered as a matrix) b
            add(new ArrayList<>() {{ add(2.0); }});
            add(new ArrayList<>() {{ add(-1.0); }});
            add(new ArrayList<>() {{ add(4.0); }});
            add(new ArrayList<>() {{ add(3.0); }});
        }};

        Matrix A = new Matrix(table);
        Matrix b = new Matrix(bTable);

        Solver solver = new Solver(A, b);
        solver.solve(); // solve Ax = b
    }
}
