//$Header$
//------------------------------------------------------------------------------
//                                  IERS
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/** @file IERS.hpp
 *  @brief Declaración de la función IERS que proporciona parámetros del Servicio Internacional de Rotación de la Tierra.
 *
 *  Esta función recupera parámetros de orientación de la Tierra (EOP) para una fecha dada
 *  en Tiempo Universal Coordinado (UTC), como la posición del polo, UT1-UTC, longitud del día,
 *  desplazamientos de nutación y TAI-UTC. La información puede interpolarse linealmente
 *  entre dos entradas si se indica.
 *
 *  
 *  @author Rubén García Eguizábal
 *  @bug No hay bugs conocidos
 */
//------------------------------------------------------------------------------

#ifndef IERS_HPP
#define IERS_HPP

#include <tuple>
#include <string>
#include "../include/global.hpp"

/**
 * @brief Devuelve parámetros de orientación de la Tierra (EOP) para una fecha UTC dada.
 * 
 * @param Mjd_UTC Fecha en MJD (Modified Julian Date).
 * @param interp Método de interpolación ("l" para lineal, "n" para sin interpolación).
 * @return Tupla con los parámetros EOP: x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC.
 */
std::tuple<double, double, double, double, double, double, double, double, double>
IERS(double Mjd_UTC, std::string interp = "n");

#endif
