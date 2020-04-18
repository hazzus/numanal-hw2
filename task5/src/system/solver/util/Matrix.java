package system.solver.util;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Matrix {
    private List<List<Double>> matrix;
    private Size size;

    public Matrix(Matrix other) {
        List<List<Double>> otherMatrix = other.matrix;
        matrix = new ArrayList<>(otherMatrix);
        size = getSize();
    }

    public Matrix(List<List<Double>> matrix) {
        this.matrix = matrix;
        size = getSize();
    }

    public List<List<Double>> getMatrix() {
        return matrix;
    }

    public Matrix multiply(Matrix other) {
        List<List<Double>> otherMatrix = other.matrix;
        Size otherSize = other.size;

        List<List<Double>> result = new ArrayList<>();

        for (int i = 0; i < size.n; i++) {
            List<Double> row = new ArrayList<>();
            for (int j = 0; j < otherSize.m; j++) {
                double element = 0;
                for (int k = 0; k < size.m; k++) {
                    element += matrix.get(i).get(k) * otherMatrix.get(k).get(j);
                }
                row.add(element);
            }
            result.add(row);
        }

        return new Matrix(result);
    }

    public Matrix multiply(double n) {
        List<List<Double>> result = new ArrayList<>();

        for (int i = 0; i < size.n; i++) {
            List<Double> row = new ArrayList<>();
            for (int j = 0; j < size.m; j++) {
                row.add(n * matrix.get(i).get(j));
            }
            result.add(row);
        }

        return new Matrix(result);
    }

    public Matrix add(Matrix other) {
        if (!size.equals(other.size)) {
            return null;
        }

        List<List<Double>> otherMatrix = other.matrix;

        List<List<Double>> result = new ArrayList<>();

        for (int i = 0; i < size.n; i++) {
            List<Double> row = new ArrayList<>();
            for (int j = 0; j < size.m; j++) {
                row.add(matrix.get(i).get(j) + otherMatrix.get(i).get(j));
            }
            result.add(row);
        }

        return new Matrix(result);
    }

    public Matrix subtract(Matrix other) {
        if (!size.equals(other.size)) {
            return null;
        }

        List<List<Double>> otherMatrix = other.matrix;

        List<List<Double>> result = new ArrayList<>();

        for (int i = 0; i < size.n; i++) {
            List<Double> row = new ArrayList<>();
            for (int j = 0; j < size.m; j++) {
                row.add(matrix.get(i).get(j) - otherMatrix.get(i).get(j));
            }
            result.add(row);
        }

        return new Matrix(result);
    }

    public Matrix transpose() {
        List<List<Double>> result = new ArrayList<>();

        for (int i = 0; i < size.m; i++) {
            List<Double> row = new ArrayList<>();
            for (int j = 0; j < size.n; j++) {
                row.add(matrix.get(j).get(i));
            }
            result.add(row);
        }

        return new Matrix(result);
    }

    public Size getSize() {
        List<List<Double>> table = matrix;
        return new Size(table.size(), table.get(0).size());
    }

    public Double getOnlyElement() {
        if (size.n == 1 && size.m == 1) {
            return matrix.get(0).get(0);
        }
        return null;
    }

    public static class Size {
        public int n;
        public int m;

        Size(int n, int m) {
            this.n = n;
            this.m = m;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Size size = (Size) o;
            return n == size.n &&
                    m == size.m;
        }

        @Override
        public int hashCode() {
            return Objects.hash(n, m);
        }
    }
}
