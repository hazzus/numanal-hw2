package system.solver.main;

import system.solver.util.Matrix;
import system.solver.Solver;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    private static final String DOMINATED = "matrices/dominated";
    private static final String HILBERT = "matrices/hilbert";
    private static final String RANDOM = "matrices/random";

    private static List<List<Double>> iterationsConvergenceLists;

    public static void main(String[] args) {
        iterationsConvergenceLists = new ArrayList<>();
        solve(DOMINATED, false);
        solve(HILBERT, false);
        solve(RANDOM, true);

        System.out.println();
        for (List<Double> l : iterationsConvergenceLists) {
            for (double n : l) {
                System.out.print(n + " ");
            }
            System.out.println();
        }
    }

    private static void solve(String fileName, boolean needToModifyMatrix) {
        List<List<Double>> A = new ArrayList<>();
        List<List<Double>> b = new ArrayList<>();

        readInput(fileName, A, b);

        Matrix aMatrix = new Matrix(A);
        Matrix bMatrix = new Matrix(b);

        if (needToModifyMatrix) {
            Matrix aTransposed = aMatrix.transpose();
            aMatrix = aTransposed.multiply(aMatrix);
            bMatrix = aTransposed.multiply(bMatrix);
        }

        Solver solver = new Solver(aMatrix, bMatrix);
        Matrix x = solver.solve();

        System.out.println(x.getMatrix());

        iterationsConvergenceLists.add(solver.getIterationsConvergence());
    }

    private static void readInput(String fileName, List<List<Double>> A, List<List<Double>> b) {
        try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
            int n = Integer.parseInt(reader.readLine());

            for (int i = 0; i < n; i++) {
                String line = reader.readLine();
                Scanner scanner = new Scanner(line);

                List<Double> row = new ArrayList<>();
                for (int j = 0; j < n; j++) {
                    row.add(scanner.nextDouble());
                }
                A.add(row);
            }

            String line = reader.readLine();
            Scanner scanner = new Scanner(line);
            for (int i = 0; i < n; i++) {
                List<Double> row = new ArrayList<>();
                row.add(scanner.nextDouble());
                b.add(row);
            }
        } catch (IOException e) {
            System.err.println("Failed to read input from file \"" + fileName + "\"");
        }
    }
}
