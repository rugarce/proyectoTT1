//$Source$
//------------------------------------------------------------------------------
//                                  Accel
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/** @file Accel.cpp
 * @brief Implementación de la operación Accel.
 *
 * Calcula la derivada del estado (posición y velocidad) en el marco inercial 
 * del sistema Tierra-Centrada no giratoria (ECI), considerando efectos de:
 * - Precesión, nutación y movimiento polar.
 * - Aceleraciones armónicas por geopotencial.
 * - Perturbaciones de cuerpos celestes (si están habilitadas).
 * 
 * Hace uso de constantes físicas, efemérides planetarias (JPL_DE430) y datos
 * de IERS para obtener los parámetros necesarios.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#include "../include/global.hpp"
#include "../include/SAT_Const.hpp"
#include "../include/Accel.hpp"
#include "../include/IERS.hpp"
#include "../include/timediff.hpp"
#include "../include/PrecMatrix.hpp"
#include "../include/NutMatrix.hpp"
#include "../include/PoleMatrix.hpp"
#include "../include/GHAMatrix.hpp"
#include "../include/Mjday_TDB.hpp"
#include "../include/JPL_Eph_DE430.hpp"
#include "../include/AccelHarmonic.hpp"
#include "../include/AccelPointMass.hpp"
#include <tuple>

Matrix& Accel(double x, Matrix& Y) {
    auto[x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC] =IERS( AuxParam.Mjd_UTC + x / 86400.0, "l");

    auto[UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC] = timediff(UT1_UTC, TAI_UTC);

    double Mjd_UT1 = AuxParam.Mjd_UTC + x / 86400.0 + UT1_UTC / 86400.0;
    double Mjd_TT  = AuxParam.Mjd_UTC + x / 86400.0 + TT_UTC / 86400.0;

    Matrix& P = PrecMatrix(SAT_Const::MJD_J2000, Mjd_TT);
    Matrix& N = NutMatrix(Mjd_TT);
    Matrix& T = N * P;
    Matrix& E = PoleMatrix(x_pole, y_pole) * GHAMatrix(Mjd_UT1) * T;

    double MJD_TDB = Mjday_TDB(Mjd_TT);
    auto[r_Mercury, r_Venus, r_Earth, r_Mars, r_Jupiter, r_Saturn, r_Uranus, r_Neptune, r_Pluto, r_Moon, r_Sun] = JPL_Eph_DE430(MJD_TDB);

    Matrix& r = extract_vector(Y, 1, 3);
    Matrix& a = AccelHarmonic(r, E, AuxParam.n, AuxParam.m);


    if (AuxParam.sun) {
        a = a + AccelPointMass(r, transpose(r_Sun), SAT_Const::GM_Sun);
    }

    if (AuxParam.moon) {
        a = a + AccelPointMass(r, transpose(r_Moon), SAT_Const::GM_Moon);
    }

    if (AuxParam.planets) {
        a = a + AccelPointMass(r, transpose(r_Mercury), SAT_Const::GM_Mercury);
        a = a + AccelPointMass(r, transpose(r_Venus),   SAT_Const::GM_Venus);
        a = a + AccelPointMass(r, transpose(r_Mars),    SAT_Const::GM_Mars);
        a = a + AccelPointMass(r, transpose(r_Jupiter), SAT_Const::GM_Jupiter);
        a = a + AccelPointMass(r, transpose(r_Saturn),  SAT_Const::GM_Saturn);
        a = a + AccelPointMass(r, transpose(r_Uranus),  SAT_Const::GM_Uranus);
        a = a + AccelPointMass(r, transpose(r_Neptune), SAT_Const::GM_Neptune);
        a = a + AccelPointMass(r, transpose(r_Pluto),   SAT_Const::GM_Pluto);
    }

    Matrix& dY = union_vector(extract_vector(Y, 4, 6), a);
    return dY;
}
