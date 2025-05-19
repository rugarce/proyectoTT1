//$Header$
//------------------------------------------------------------------------------
//                                  Accel
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file Accel.hpp
 * @brief Cabecera de la operación Accel.
 *
 * Esta función calcula el vector derivada del estado orbital, incluyendo 
 * aceleraciones gravitatorias y perturbaciones debido a cuerpos celestes.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#ifndef ACCEL_HPP
#define ACCEL_HPP

#include "../include/matrix.hpp"
#include <tuple>

//------------------------------------------------------------------------------
// Matrix& Accel(double x, Matrix& Y)
//------------------------------------------------------------------------------
/**
 * @brief Calcula la derivada del estado orbital (posición y velocidad).
 *
 * Esta función implementa el modelo dinámico completo, incluyendo:
 * - Aceleración armónica por geopotencial terrestre.
 * - Perturbaciones por cuerpos celestes (Sol, Luna, planetas).
 * - Transformaciones entre marcos de referencia (precesión, nutación, etc).
 *
 * @param [in] x Tiempo transcurrido en segundos desde Mjd_UTC inicial.
 * @param [in] Y Vector de estado 6x1 (posición y velocidad) [km y km/s].
 * @return Vector derivada 6x1 (velocidad y aceleración).
 */
//------------------------------------------------------------------------------
Matrix& Accel(double x, Matrix& Y);

#endif // ACCEL_HPP
