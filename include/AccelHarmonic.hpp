//$Header$
//------------------------------------------------------------------------------
//                                  AccelHarmonic
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file AccelHarmonic.hpp
 * @brief Cabecera de la operacion AccelHarmonic.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------

#ifndef ACCELHARMONIC_HPP
#define ACCELHARMONIC_HPP

#include <cmath>
#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// Matrix& AccelHarmonic(Matrix &r, Matrix &E, int n_max, int m_max)
//------------------------------------------------------------------------------
/**
 * @brief Operacion AccelHarmonic.
 *
 * @param [in] r Vector columna posicion del satelite.
 * @param [in] E Matriz de transformación.
 * @param [in] n_max Grado maximo.
 * @param [in] m_max Orden maximo.
 * @return Vector columna aceleracion.
 */
//------------------------------------------------------------------------------
Matrix& AccelHarmonic(Matrix &r, Matrix &E, int n_max, int m_max);

#endif