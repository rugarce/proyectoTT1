//$Source$
//------------------------------------------------------------------------------
//                                      gmst
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file gmst.cpp
 * @brief Implementación de la operación gmst.
 *
 * Calcula el Tiempo Sideral Medio de Greenwich (GMST) en radianes a partir
 * de la fecha juliana modificada UT1. Utiliza una fórmula precisa basada en 
 * el modelo de la IAU para determinar la rotación de la Tierra.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#include "../include/gmst.hpp"
#include "../include/Frac.hpp"
#include "../include/SAT_Const.hpp"
#include <cmath>

double gmst(double Mjd_UT1) {
    const double Secs = 86400.0;
    const double MJD_J2000 = 51544.5;

    double Mjd_0 = std::floor(Mjd_UT1);
    double UT1 = Secs * (Mjd_UT1 - Mjd_0);  
    double T_0 = (Mjd_0 - MJD_J2000) / 36525.0;
    double T = (Mjd_UT1 - MJD_J2000) / 36525.0;

    double gmst = 24110.54841 + 8640184.812866 * T_0
                + 1.002737909350795 * UT1
                + (0.093104 - 6.2e-6 * T) * T * T;

    double gmstime = 2.0 * SAT_Const::pi * Frac(gmst / Secs); 

    return gmstime;
}
