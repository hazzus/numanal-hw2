#include <iostream>
#include <vector>

using namespace std;

vector<double> gaussian_column(vector<vector<double>> matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    for (int i = 0; i < matrix.size() - 1; ++i) {
        //find row id with maximum element in first column
        int row = i;
        for (int j = i + 1; j < matrix.size(); ++j) {
            if (abs(matrix[j][i]) > abs(matrix[row][i]))
                row = j;
        }
        swap(matrix[i], matrix[row]);
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
    return xs;
}
