#include <iostream>
#include <vector>

using namespace std;

vector<double> gaussian_matrix(vector<vector<double>> matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<int> permut;
    permut.reserve(n);
    for (int i = 0; i < n; ++i) {
        permut.push_back(i);
    }
    for (int i = 0; i < matrix.size() - 1; ++i) {
        //find maximum element in the remaining submatrix
        int max_i = i;
        int max_j = i;

        for (int j = i; j < n; ++j) {
            for (int k = i; k < n; ++k) {
                if (abs(matrix[j][k]) > abs(matrix[max_i][max_j])) {
                    max_i = j;
                    max_j = k;
                }
            }
        }
        swap(matrix[i], matrix[max_i]);
        for (int j = 0; j < n; ++j) {
            swap(matrix[j][max_j], matrix[j][i]);
        }

        swap(permut[max_j], permut[i]);

        for (int j = i + 1; j < matrix.size(); ++j) {
            double multiplier = matrix[j][i] / matrix[i][i];
            for (int k = i; k < m; ++k) {
                matrix[j][k] = matrix[j][k] - multiplier * matrix[i][k];
            }
        }
    }
    vector<double> xs(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < n; ++j) {
            sum += matrix[i][j] * xs[j];
        }
        xs[i] = (matrix[i][m - 1] - sum) / matrix[i][i];
    }
    for (int i = 0; i < n; ++i) {
        while (permut[i] != i) {
            int to = permut[i];
            swap(permut[i], permut[to]);
            swap(xs[i], xs[to]);
        }
    }
    return xs;
}
