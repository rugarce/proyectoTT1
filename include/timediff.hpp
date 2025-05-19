//$Header$
//------------------------------------------------------------------------------
//                                  timediff
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/** @file timediff.hpp
 *  @brief Declaración de la función timediff para calcular diferencias temporales entre estándares.
 *
 *  Esta función calcula y devuelve diversas diferencias temporales entre las escalas
 *  UT1, UTC, TAI, GPS y TT (Tiempo Terrestre).
 *
 *  @author Rubén García Eguizábal
 *  @bug No hay bugs conocidos
 */
//------------------------------------------------------------------------------

#ifndef TIMEDIFF_HPP
#define TIMEDIFF_HPP

#include <tuple>
using namespace std;

/**
 * @brief Calcula diferencias temporales entre escalas de tiempo.
 * 
 * @param UT1_UTC Diferencia UT1-UTC en segundos.
 * @param TAI_UTC Diferencia TAI-UTC en segundos.
 * @return tuple<double, double, double, double, double> 
 *         Diferencias: UT1-TAI, UTC-GPS, UT1-GPS, TT-UTC, GPS-UTC en segundos.
 */
tuple<double, double, double, double, double> timediff(double UT1_UTC, double TAI_UTC);

#endif
