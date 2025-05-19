#include "..\include\matrix.hpp"
#include "..\include\global.hpp"
#include "..\include\R_x.hpp"
#include "..\include\SAT_Const.hpp"
#include "../include/Position.hpp"
#include "../include/Accel.hpp"
#include "../include/DEInteg.hpp"
#include "../include/Mjday.hpp"
#include "../include/LTC.hpp"
#include "../include/VarEqn.hpp"
#include "../include/timediff.hpp"
#include "../include/IERS.hpp"
#include "../include/TimeUpdate.hpp"
#include "../include/AzElPa.hpp"
#include "../include/MeasUpdate.hpp"
#include "../include/gmst.hpp"
#include "../include/R_z.hpp"

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    eop19620101(21413);
    DE430Coeff(2285, 1020);
    GGM03S(181);
    GEOS3(46);

    double sigma_range = 92.5;
    double sigma_az = 0.0224 * SAT_Const::Rad;
    double sigma_el = 0.0139 * SAT_Const::Rad;

    double lat = SAT_Const::Rad * 21.5748;
    double lon = SAT_Const::Rad * (-158.2706);
    double alt = 300.20;

    Matrix Rs = zeros(3);
    Rs = transpose(Position(lon, lat, alt));

    double Mjd1 = obs(1, 1);
    double Mjd2 = obs(9, 1);
    double Mjd3 = obs(18, 1);

    Matrix r2 = zeros(3);
    Matrix v2 = zeros(3);

    r2(1) = 6221397.62857869;
    r2(2) = 2867713.77965738;
    r2(3) = 3006155.98509949;
    v2(1) = 4645.04725161806;
    v2(2) = -2752.21591588204;
    v2(3) = -7507.99940987031;

    Matrix Y0_apr = union_vector(r2, v2);
    double Mjd0 = Mjday(1995, 1, 29, 2, 38, 0);

    double Mjd_UTC = obs(9, 1);
    AuxParam.Mjd_UTC = Mjd_UTC;
    AuxParam.n = 20;
    AuxParam.m = 20;
    AuxParam.sun = 1;
    AuxParam.moon = 1;
    AuxParam.planets = 1;

    int n_eqn = 6;
    Matrix Y = DEInteg(Accel, 0.0, -(obs(9, 1) - Mjd0) * 86400.0, 1e-13, 1e-6, 6, transpose(Y0_apr));
    Matrix P = zeros(6, 6);
    for (int i = 1; i <= 3; ++i)
        P(i, i) = 1e8;
    for (int i = 4; i <= 6; ++i)
        P(i, i) = 1e3;

    Matrix LT = LTC(lon, lat);

    Matrix yPhi = zeros(42, 1);
    Matrix Phi = zeros(6, 6);
    double t = 0.0;

    double t_old, Mjd_TT, Mjd_UT1;
    double theta;
    Matrix Y_old = zeros(6, 1);
    Matrix U = zeros(3, 3);
    Matrix r;
    Matrix s;
    Matrix dAdY;
    Matrix dEdY;
    double Dist;
    Matrix dDdY;
    Matrix dDds;
    double Azim, Elev;
    Matrix dAds, dEds, K;
    double x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC;
    double UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC;

    for (int i = 1; i <= 46; ++i)
    {
        t_old = t;
        Y_old = Y;

        Mjd_UTC = obs(i, 1);
        t = (Mjd_UTC - Mjd0) * 86400.0;

        tie(x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC) = IERS(Mjd_UTC, "l");
        tie(UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC) = timediff(UT1_UTC, TAI_UTC);

        Mjd_TT = Mjd_UTC + TT_UTC / 86400.0;
        Mjd_UT1 = Mjd_TT + (UT1_UTC - TT_UTC) / 86400.0;

        AuxParam.Mjd_UTC = Mjd_UTC;
        AuxParam.Mjd_TT = Mjd_TT;

        for (int ii = 1; ii <= 6; ++ii)
        {
            yPhi(ii) = Y_old(ii);
            for (int j = 1; j <= 6; ++j)
            {
                yPhi(6 * j + ii) = (ii == j) ? 1.0 : 0.0;
            }
        }
        yPhi = DEInteg(VarEqn, 0.0, t - t_old, 1e-13, 1e-6, 42, yPhi);

        for (int j = 1; j <= 6; ++j)
        {
            assign_column(Phi,extract_vector(transpose(yPhi),6*j+1, 6*j+6),j);
        }
        
        Y = DEInteg(Accel, 0.0, t - t_old, 1e-13, 1e-6, 6, Y_old);

        theta = gmst(Mjd_UT1);
        U = R_z(theta);
        r = transpose(extract_vector(transpose(Y), 1, 3));
        s = LT * (U * r - Rs);
        P = TimeUpdate(P, Phi);

        tie(Azim, Elev, dAds, dEds) = AzElPa(transpose(s));
        dAdY = union_vector(dAds * LT * U, zeros(3));
        tie(K, Y, P) = MeasUpdate(Y, obs(i, 2), Azim, sigma_az, dAdY, P, 6);

        r = transpose(extract_vector(transpose(Y), 1, 3));
        s = LT * (U * r - Rs);
        tie(Azim, Elev, dAds, dEds) = AzElPa(transpose(s));

        dEdY = union_vector(dEds * LT * U, zeros(3));

        tie(K, Y, P) = MeasUpdate(Y, obs(i, 3), Elev, sigma_el, dEdY, P, 6);
        r = transpose(extract_vector(transpose(Y), 1, 3));
        s = LT * (U * r - Rs);
        Dist = norm(transpose(s));
        dDds = transpose(s / Dist);
        dDdY = union_vector(dDds * LT * U, zeros(3));
        tie(K, Y, P) = MeasUpdate(Y, obs(i, 4), Dist, sigma_range, dDdY, P, 6);
    }
    cout << "aaaaaaaaaaaa\n";
    tie(x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC) = IERS(obs(46, 1), "l");
    tie(UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC) = timediff(UT1_UTC, TAI_UTC);
    Mjd_TT = Mjd_UTC + TT_UTC / 86400.0;

    AuxParam.Mjd_UTC = Mjd_UTC;
    AuxParam.Mjd_TT = Mjd_TT;

    Matrix Y0 = transpose(DEInteg(Accel, 0.0, -(obs(46, 1) - obs(1, 1)) * 86400.0, 1e-13, 1e-6, 6, Y));

    Matrix Y_true(6);

    Y_true(1) = 5753.173e3;
    Y_true(2) = 2673.361e3;
    Y_true(3) = 3440.304e3;
    Y_true(4) = 4.324207e3;
    Y_true(5) = -1.924299e3;
    Y_true(6) = -5.728216e3;

    printf("\nError of Position Estimation\n");
    printf("dX%10.1f [m]\n", Y0(1) - Y_true(1));
    printf("dY%10.1f [m]\n", Y0(2) - Y_true(2));
    printf("dZ%10.1f [m]\n", Y0(3) - Y_true(3));
    printf("\nError of Velocity Estimation\n");
    printf("dVx%8.1f [m/s]\n", Y0(4) - Y_true(4));
    printf("dVy%8.1f [m/s]\n", Y0(5) - Y_true(5));
    printf("dVz%8.1f [m/s]\n", Y0(6) - Y_true(6));

    return 0;
}