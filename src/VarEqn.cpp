//$Source$
//------------------------------------------------------------------------------
//                                  VarEqn
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file VarEqn.cpp
 * @brief Implementación de la operación VarEqn.
 *
 * Esta función evalúa simultáneamente:
 *  - Las ecuaciones del movimiento del satélite.
 *  - La matriz de variación del sistema (ecuaciones de sensibilidad).
 *
 * Se considera el modelo dinámico incluyendo geopotencial y transformación 
 * entre marcos de referencia (ECI -> cuerpo).
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#include "../include/VarEqn.hpp"
#include "../include/global.hpp"
#include "../include/SAT_Const.hpp"
#include "../include/IERS.hpp"
#include "../include/timediff.hpp"
#include "../include/PrecMatrix.hpp"
#include "../include/NutMatrix.hpp"
#include "../include/PoleMatrix.hpp"
#include "../include/GHAMatrix.hpp"
#include "../include/AccelHarmonic.hpp"
#include "../include/G_AccelHarmonic.hpp"

Matrix &VarEqn(double x, Matrix &yPhi)
{
    auto [x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC] = IERS(AuxParam.Mjd_UTC, "l");

    auto [UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC] = timediff(UT1_UTC, TAI_UTC);

    double Mjd_UT1 = AuxParam.Mjd_TT + (UT1_UTC - TT_UTC) / 86400.0;

    Matrix &P = PrecMatrix(SAT_Const::MJD_J2000, AuxParam.Mjd_TT + x / 86400.0);
    Matrix &N = NutMatrix(AuxParam.Mjd_TT + x / 86400.0);
    Matrix &T = N * P;
    Matrix &E = PoleMatrix(x_pole, y_pole) * GHAMatrix(Mjd_UT1) * T;

    Matrix &r = extract_vector(yPhi, 1, 3);
    Matrix &v = transpose(extract_vector(yPhi, 4, 6));
    Matrix &Phi = zeros(6, 6);

    for (int j = 1; j <= 6; j++)
    {
        for (int i = 1; i <= 6; i++)
        {
            Phi(i, j) = yPhi(1, 6 * j + i);
        }
    }

    Matrix &a = AccelHarmonic(r, E, AuxParam.n, AuxParam.m);
    Matrix &G = G_AccelHarmonic(r, E, AuxParam.n, AuxParam.m);

    Matrix &dfdy = zeros(6, 6);
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            dfdy(i, j) = 0.0;
            dfdy(i + 3, j) = G(i, j);
            dfdy(i, j + 3) = (i == j) ? 1.0 : 0.0;
            dfdy(i + 3, j + 3) = 0.0;
        }
    }

    Matrix &Phip = dfdy * Phi;
    Matrix &yPhip = zeros(42, 1);
    for (int i = 1; i <= 3; i++)
    {
        yPhip(i, 1) = v(i, 1);
        yPhip(i + 3, 1) = a(i);
    }

    for (int i = 1; i <= 6; i++)
    {
        for (int j = 1; j <= 6; j++)
        {
            yPhip(6 * j + i, 1) = Phip(i, j); 
        }
    }
    
    return transpose(yPhip);
}
