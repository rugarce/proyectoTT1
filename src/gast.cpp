//$Source$
//------------------------------------------------------------------------------
//                                      gast
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file gast.cpp
 * @brief Implementación de la operación gast.
 *
 * Calcula el Tiempo Sideral Aparente de Greenwich (GAST), el cual representa 
 * la orientación de la Tierra respecto a las estrellas, incluyendo la corrección 
 * de la ecuación de los equinoccios. Es la suma del GMST con dicha corrección, 
 * y se normaliza al intervalo [0, 2π].
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#include "../include/gast.hpp"
#include "../include/gmst.hpp"
#include "../include/EqnEquinox.hpp"
#include "../include/SAT_Const.hpp"
#include <cmath>

double gast(double Mjd_UT1) {
    double g = gmst(Mjd_UT1) + EqnEquinox(Mjd_UT1);
    double gstime = fmod(g, SAT_Const::pi2);
    if(gstime < 0){
        gstime += SAT_Const::pi2;
    }
    return gstime;
}
