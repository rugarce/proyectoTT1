#include "../include/IERS.hpp"
#include "../include/SAT_Const.hpp"
#include <cmath>
#include <stdexcept>

extern Matrix eopdata; 

tuple<double, double, double, double, double, double, double, double, double> IERS(double Mjd_UTC,const string& interp) {

    double x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC;
    double mjd = floor(Mjd_UTC);

    int i = -1;
    for (int k = 1; k <= eopdata.n_column; ++k) {
        if (std::abs(eopdata(4, k) - mjd) < 1e-6) {
            i = k;
            break;
        }
    }
    if (i == -1) {
        cout << "IERS error: No matching MJD found in eopdata.\n";
        exit(EXIT_FAILURE);
    }

    if (interp == "l") {
        if (i + 1 > eopdata.n_column) {
            cout << "IERS error: Cannot interpolate, next entry missing.\n";
            exit(EXIT_FAILURE);
        }
        Matrix preeop = extract_column(eopdata,i);
        Matrix nexteop = extract_column(eopdata,i + 1);
        double mfme = 1440.0 * (Mjd_UTC - floor(Mjd_UTC));
        double fixf = mfme / 1440.0;

        x_pole  = preeop(5) + (nexteop(5) - preeop(5)) * fixf;
        y_pole  = preeop(6) + (nexteop(6) - preeop(6)) * fixf;
        UT1_UTC = preeop(7) + (nexteop(7) - preeop(7)) * fixf;
        LOD     = preeop(8) + (nexteop(8) - preeop(8)) * fixf;
        dpsi    = preeop(9) + (nexteop(9) - preeop(9)) * fixf;
        deps    = preeop(10)+ (nexteop(10)- preeop(10)) * fixf;
        dx_pole = preeop(11)+ (nexteop(11)- preeop(11)) * fixf;
        dy_pole = preeop(12)+ (nexteop(12)- preeop(12)) * fixf;
        TAI_UTC = preeop(13);

        x_pole= x_pole/SAT_Const::Arcs;
        y_pole= y_pole/SAT_Const::Arcs;
        dpsi = dpsi/SAT_Const::Arcs;
        deps = deps/SAT_Const::Arcs;
        dx_pole = dx_pole/SAT_Const::Arcs;
        dy_pole = dy_pole/SAT_Const::Arcs;
    } else if(interp == "n") {
        Matrix row = extract_column(eopdata, i);

        x_pole  = row(5)/SAT_Const::Arcs;
        y_pole  = row(6)/SAT_Const::Arcs;
        UT1_UTC = row(7);
        LOD     = row(8);
        dpsi    = row(9)/SAT_Const::Arcs;
        deps    = row(10)/SAT_Const::Arcs;
        dx_pole = row(11)/SAT_Const::Arcs;
        dy_pole = row(12)/SAT_Const::Arcs;
        TAI_UTC = row(13);
    }

    return make_tuple(x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC);
}
