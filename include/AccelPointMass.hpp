//$Header$
//------------------------------------------------------------------------------
//                            AccelPointMass
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file AccelPointMass.hpp
 * @brief Cabecera de la función que calcula la aceleración gravitatoria 
 *        generada por un cuerpo puntual.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#ifndef _ACCEL_POINT_MASS_
#define _ACCEL_POINT_MASS_

#include "../include/matrix.hpp" 
#include <cmath>

//------------------------------------------------------------------------------
// Matrix& AccelPointMass(Matrix& r, Matrix& s, double GM)
//------------------------------------------------------------------------------
/**
 * @brief Calcula la aceleración debida a un cuerpo puntual.
 *
 * @param [in] r Vector de posición del punto donde se evalúa la aceleración [m].
 * @param [in] s Vector de posición del cuerpo puntual [m].
 * @param [in] GM Constante gravitacional multiplicada por la masa del cuerpo [m^3/s^2].
 * @return Aceleración gravitatoria en forma de vector [m/s^2].
 */
//------------------------------------------------------------------------------
Matrix& AccelPointMass(Matrix& r, Matrix& s, double GM);

#endif
