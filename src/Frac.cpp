//$Source$
//------------------------------------------------------------------------------
//                                  Frac
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file Frac.cpp
 * @brief Implementación de la función que calcula la parte fraccional de un número.
 *
 * Utiliza la función floor para extraer la parte entera y devolver la diferencia.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#include <cmath>
#include "../include/Frac.hpp"

double Frac(double x) {
    return x - floor(x);
}
