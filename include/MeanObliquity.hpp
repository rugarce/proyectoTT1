//$Header$
//------------------------------------------------------------------------------
//                               MeanObliquity
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file MeanObliquity.hpp
 * @brief Cabecera de la función para calcular la oblicuidad media de la eclíptica.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------

#ifndef MEANOBLIQUITY_HPP
#define MEANOBLIQUITY_HPP

//------------------------------------------------------------------------------
// double MeanObliquity(double Mjd_TT)
//------------------------------------------------------------------------------
/**
 * @brief Calcula la oblicuidad media de la eclíptica para un tiempo dado.
 *
 * @param [in] Mjd_TT Tiempo en días julianos modificados (Tiempo Terrestre).
 * @return Oblicuidad media en radianes.
 */
//------------------------------------------------------------------------------
double MeanObliquity(double Mjd_TT);

#endif
