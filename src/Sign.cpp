//$Source$
//------------------------------------------------------------------------------
//                                   Sign
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/** @file Sign.cpp
 *  @brief Implementación de la función sign_.
 *
 *  La función devuelve el valor absoluto de `a` con el signo de `b`.
 *
 *  @author Rubén García Eguizábal
 *  @bug No hay bugs conocidos
 */
//------------------------------------------------------------------------------
#include "../include/Sign.hpp"
#include <cmath> 

double sign_(double a, double b) {
    return (b >= 0.0) ? std::abs(a) : -std::abs(a);
}
