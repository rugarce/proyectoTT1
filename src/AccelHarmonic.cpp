//$Source$
//------------------------------------------------------------------------------
//                                  AccelHarmonic
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file AccelHarmonic.cpp
 * @brief Implementación de la operacion AccelHarmonic.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#include "../include/AccelHarmonic.hpp"
#include "../include/SAT_Const.hpp"
#include "../include/Legendre.hpp"
#include "../include/matrix.hpp"
#include "../include/global.hpp"

Matrix& AccelHarmonic(Matrix &r, Matrix &E, int n_max, int m_max)
{
    GGM03S(181);

    double r_ref = 6378136.3;    
    double gm = 398600.4415e9;   

    Matrix& r_bf = transpose(E * transpose(r));
    double d = norm(r_bf);
    double latgc = asin(r_bf(3) / d);
    double lon = atan2(r_bf(2), r_bf(1));

    auto [pnm, dpnm] = Legendre(n_max, m_max, latgc);

    double dUdr = 0.0, dUdlatgc = 0.0, dUdlon = 0.0;
    double q1 = 0.0, q2 = 0.0, q3 = 0.0;

    for (int n = 0; n <= n_max; ++n) {
        double b1 = (-gm / (d * d)) * pow(r_ref / d, n) * (n + 1);
        double b2 =  (gm / d) * pow(r_ref / d, n);
        double b3 =  b2;

        for (int m = 0; m <= m_max; ++m) {
            double C = Cnm(n + 1, m + 1);
            double S = Snm(n + 1, m + 1);
            double cosml = cos(m * lon);
            double sinml = sin(m * lon);

            q1 += pnm(n + 1, m + 1) * (C * cosml + S * sinml);
            q2 += dpnm(n + 1, m + 1) * (C * cosml + S * sinml);
            q3 += m * pnm(n + 1, m + 1) * (S * cosml - C * sinml);
        }

        dUdr     += q1 * b1;
        dUdlatgc += q2 * b2;
        dUdlon   += q3 * b3;

        q1 = q2 = q3 = 0.0;
    }

    double r2xy = r_bf(1) * r_bf(1) + r_bf(2) * r_bf(2);

    double ax = (1/d * dUdr - r_bf(3)/(d*d*sqrt(r2xy)) * dUdlatgc) * r_bf(1) - (1/r2xy * dUdlon) * r_bf(2);
    double ay = (1/d * dUdr - r_bf(3)/(d*d*sqrt(r2xy)) * dUdlatgc) * r_bf(2) + (1/r2xy * dUdlon) * r_bf(1);
    double az = 1/d * dUdr * r_bf(3) + sqrt(r2xy)/(d*d) * dUdlatgc;

    Matrix a_bf = zeros(3);
    a_bf(1) = ax;
    a_bf(2) = ay;
    a_bf(3) = az;

    Matrix& a = transpose(E) * transpose(a_bf);
    return transpose(a);
}
