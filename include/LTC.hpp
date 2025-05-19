//$Header$
//------------------------------------------------------------------------------
//                                  LTC
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file LTC.hpp
 * @brief Cabecera para la transformación de coordenadas desde el sistema geodésico local.
 *
 * Esta función genera la matriz de transformación desde un sistema de coordenadas local
 * tangente a la Tierra en una posición definida por su latitud y longitud geodésicas.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#ifndef LTC_HPP
#define LTC_HPP

#include "../include/matrix.hpp" 

//------------------------------------------------------------------------------
// Matrix& LTC(double lon, double lat)
//------------------------------------------------------------------------------
/**
 * @brief Genera la matriz de transformación desde el sistema local tangente.
 *
 * Calcula y devuelve una referencia a la matriz de transformación del sistema
 * de coordenadas geodésico local tangente (LTC) en función de la longitud y latitud.
 *
 * @param [in] lon Longitud geodésica [rad].
 * @param [in] lat Latitud geodésica [rad].
 * @return Referencia a la matriz de transformación 3x3.
 */
//------------------------------------------------------------------------------
Matrix& LTC(double lon, double lat);

#endif
