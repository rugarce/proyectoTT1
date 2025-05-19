//$Source$
//------------------------------------------------------------------------------
//                                  AzElPa
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/** @file AzElPa.cpp
 *  @brief Implementación de la función AzElPa.
 *
 *  Calcula el azimut y elevación dados un vector de posición 3D y sus derivadas parciales.
 *  El azimut está en el rango [0, 2π].
 *  Se devuelven referencias a matrices que contienen las derivadas parciales respecto a s.
 *
 *  @author Rubén García Eguizábal
 *  @bug No hay bugs conocidos
 */
//------------------------------------------------------------------------------
#include "../include/AzElPa.hpp"
#include "../include/SAT_Const.hpp"
#include <cmath>

tuple<double, double, Matrix&, Matrix&> AzElPa(Matrix& s)
{

    const double rho = std::sqrt(s(1) * s(1) + s(2) * s(2));

    double Az = std::atan2(s(1), s(2));
    if (Az < 0.0)
    {
        Az += SAT_Const::pi2;
    }

    double El = std::atan(s(3) / rho);

    Matrix* dAds = new Matrix(1, 3);
    (*dAds)(1, 1) = s(2) / (rho * rho);
    (*dAds)(1, 2) = -s(1) / (rho * rho);
    (*dAds)(1, 3) = 0.0;

    Matrix* dEds = new Matrix(1, 3);
    (*dEds)(1, 1) = -s(1) * s(3) / rho / dot(s, s);
    (*dEds)(1, 2) = -s(2) * s(3) / rho / dot(s, s);
    (*dEds)(1, 3) = rho / dot(s, s);

    return tie(Az, El, *dAds, *dEds);
}
