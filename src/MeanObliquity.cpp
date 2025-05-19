//$Source$
//------------------------------------------------------------------------------
//                               MeanObliquity
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file MeanObliquity.cpp
 * @brief Implementación de la función para calcular la oblicuidad media de la eclíptica.
 *
 * Se calcula usando una expresión polinómica en T (siglos julianos desde J2000).
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#include "../include/MeanObliquity.hpp"
#include "../include/SAT_Const.hpp"

double MeanObliquity(double Mjd_TT) {
    const double T = (Mjd_TT - SAT_Const::MJD_J2000) / 36525.0;
    const double arcsec = 84381.448 - (46.8150 + (0.00059 - 0.001813 * T) * T) * T;

    return arcsec / 3600.0 * SAT_Const::Rad; 
}
