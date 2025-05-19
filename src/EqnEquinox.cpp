//$Source$
//------------------------------------------------------------------------------
//                                  EqnEquinox
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file EqnEquinox.cpp
 * @brief Implementación de la operacion EqnEquinox.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#include "../include/EqnEquinox.hpp"
#include "../include/NutAngles.hpp"
#include "../include/MeanObliquity.hpp"
#include <cmath>

double EqnEquinox(double Mjd_TT)
{

    auto [dpsi, deps] = NutAngles(Mjd_TT);

    return dpsi * std::cos(MeanObliquity(Mjd_TT));
}
