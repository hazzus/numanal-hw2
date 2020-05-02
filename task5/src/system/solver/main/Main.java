package system.solver.main;

import system.solver.util.Matrix;
import system.solver.Solver;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    private static final String DOMINATED = "matrices/dominated";
    public static final String HILBERT = "matrices/hilbert";
    public static final String RANDOM = "matrices/random";

    public static void main(String[] args) {
        List<List<Double>> A = new ArrayList<>();
        List<List<Double>> b = new ArrayList<>();
        Solver solver;

        readInput(DOMINATED, A, b);

        solver = new Solver(new Matrix(A), new Matrix(b));
        solver.solve();

        readInput(HILBERT, A, b);

        solver = new Solver(new Matrix(A), new Matrix(b));
        solver.solve();

        readInput(RANDOM, A, b);

        solver = new Solver(new Matrix(A), new Matrix(b));
        solver.solve();
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
