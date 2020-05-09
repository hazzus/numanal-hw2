//
// Created by roman on 21.04.2020.
//

#include <fstream>
#include <iomanip>
#include "gaussian-column.h"
#include "gaussian-matrix.h"
#include "matrices.h"

using namespace std;

void print_vector(const vector<double> &vector, ostream &out) {
    for (double i : vector) {
        out << setprecision(9) << setw(9) << i << " ";
    }
    out << endl;
}

void printMethod(const string &methodName,
                 ostream &out,
                 const vector<vector<double>> &inp) {
    out << methodName + ":" << endl;
    out << "column: ";
    vector<double> columnRes = gaussian_column(inp);
    print_vector(columnRes, out);
    for (int i = 0; i < columnRes.size(); ++i) {
        double sum = 0;
        for (int j = 0; j < columnRes.size(); ++j) {
            sum += inp[i][j] * columnRes[j];
        }
        out << sum << " ";
    }
    out << endl;

    out << "matrix: ";
    vector<double> matrixRes = gaussian_column(inp);
    print_vector(matrixRes, out);
    for (int i = 0; i < matrixRes.size(); ++i) {
        double sum = 0;
        for (int j = 0; j < matrixRes.size(); ++j) {
            sum += inp[i][j] * matrixRes[j];
        }
        out << sum << " ";
    }
    out << endl;
    out << endl;
}

int main() {
    ofstream out("../results.txt");
    printMethod("dominated", out, dominated);
    printMethod("hilbert", out, hilbert);
    printMethod("random", out, random_m);

    out.close();
    return 0;
}