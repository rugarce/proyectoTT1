//$Header$
//------------------------------------------------------------------------------
//                              G_AccelHarmonic
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file G_AccelHarmonic.hpp
 * @brief Cabecera de la operación G_AccelHarmonic.
 *
 * Esta función calcula la matriz Jacobiana de la aceleración gravitacional 
 * debida al potencial armónico, evaluada en una posición determinada.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#ifndef G_ACCELHARMONIC_HPP
#define G_ACCELHARMONIC_HPP

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// Matrix& G_AccelHarmonic(Matrix& r, Matrix& U, int n_max, int m_max)
//------------------------------------------------------------------------------
/**
 * @brief Calcula la matriz Jacobiana de la aceleración armónica.
 *
 * @param [in] r Vector de posición [m].
 * @param [in] U Matriz de coeficientes armónicos.
 * @param [in] n_max Orden máximo del desarrollo armónico.
 * @param [in] m_max Grado máximo del desarrollo armónico.
 * @return Matriz 3x3 que representa el Jacobiano de la aceleración respecto a la posición.
 */
//------------------------------------------------------------------------------
Matrix& G_AccelHarmonic(Matrix& r, Matrix& U, int n_max, int m_max);

#endif // G_ACCELHARMONIC_HPP
