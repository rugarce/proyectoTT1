//$Source$
//------------------------------------------------------------------------------
//                                  timediff
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/** @file timediff.cpp
 *  @brief Implementación de la función timediff.
 *
 *  Calcula varias diferencias temporales entre UT1, UTC, TAI, GPS y TT, usando las constantes
 *  definidas y los parámetros de entrada UT1_UTC y TAI_UTC.
 *
 *  @author Rubén García Eguizábal
 *  @bug No hay bugs conocidos
 */
//------------------------------------------------------------------------------
#include "../include/timediff.hpp"
using namespace std;

tuple<double, double, double, double, double> timediff(double UT1_UTC, double TAI_UTC) {
    const double TT_TAI  = 32.184;  
    const double GPS_TAI = -19.0;  
    const double TT_GPS  = TT_TAI - GPS_TAI;
    const double TAI_GPS = -GPS_TAI;

    double UT1_TAI = UT1_UTC - TAI_UTC;
    double UTC_TAI = -TAI_UTC;
    double UTC_GPS = UTC_TAI - GPS_TAI;
    double UT1_GPS = UT1_TAI - GPS_TAI;
    double TT_UTC  = TT_TAI - UTC_TAI;
    double GPS_UTC = GPS_TAI - UTC_TAI;

    return tie(UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC );
}
