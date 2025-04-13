#include "../include/AccelPointMass.hpp"
#include <cmath>

Matrix AccelPointMass(Matrix &r, Matrix &s, double GM) {
    Matrix d = r - s;
    Matrix a(r.n_column);

    for (int i = 1; i <= r.n_row; i++) {
        a(i) = -GM * (d(i) / pow(norm(d), 3) + s(i) / pow(norm(s), 3));
    }

    return a;
}

