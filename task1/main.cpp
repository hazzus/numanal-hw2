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


int main() {
    ofstream out("../results.txt");

    out << "dominated:" << endl;
    out << "column: ";
    print_vector(gaussian_column(dominated), out);
    out << "matrix: ";
    print_vector(gaussian_column(dominated), out);
    out << endl;

    out << "hilbert:" << endl;
    out << "column: ";
    print_vector(gaussian_column(hilbert), out);
    out << "matrix: ";
    print_vector(gaussian_column(hilbert), out);
    out << endl;

    out << "random:" << endl;
    out << "column: ";
    print_vector(gaussian_column(random_m), out);
    out << "matrix: ";
    print_vector(gaussian_column(random_m), out);
    out << endl;

    out.close();
    return 0;
}