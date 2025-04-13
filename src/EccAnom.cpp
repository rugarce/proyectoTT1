#include "../include/EccAnom.hpp"
#include "../include/SAT_Const.hpp"
#include <cmath>


Matrix EccAnom(double M, double e) {
    const int maxit = 15;
    int i = 1;

    M = fmod(M, SAT_Const::pi2);

    Matrix E(1);
    if (e < 0.8) {
        E(1) = M;
    } else {
        E(1) = SAT_Const::pi;
    }

    double f = E(1) - e * sin(E(1)) - M;
    E(1) = E(1) - f / (1.0 - e * cos(E(1)));

    while (fabs(f) > 1e2 * SAT_Const::eps) {
        f = E(1) - e * sin(E(1)) - M;
        E(1) = E(1) - f / (1.0 - e * cos(E(1)));
        i++;

        if (i == maxit) {
            cout << "ERROR: Convergence problems in EccAnom";
            exit(EXIT_FAILURE);
        }
    }

    return E;
}
