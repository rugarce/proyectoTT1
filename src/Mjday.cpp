//$Source$
//------------------------------------------------------------------------------
//                                   Mjday
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file Mjday.cpp
 * @brief Implementación de la función para calcular el día juliano modificado a partir de fecha y hora.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#include "../include/Mjday.hpp"
#include <cmath>

double Mjday(int yr, int mon, int day, int hr, int min, int sec) {

    double jd = 367.0 * yr
        - floor((7 * (yr + floor((mon + 9) / 12.0))) * 0.25)
        + floor(275 * mon / 9.0)
        + day + 1721013.5
        + (((sec / 60.0 + min) / 60.0 + hr) / 24.0);

    return jd - 2400000.5;
}
