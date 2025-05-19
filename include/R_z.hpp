//$Header$
//------------------------------------------------------------------------------
//                                     R_z
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file R_z.hpp
 * @brief Cabecera para la matriz de rotación alrededor del eje Z.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------

#ifndef _R_z_
#define _R_z_

#include <cmath>
#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// Matrix& R_z(double angle)
//------------------------------------------------------------------------------
/**
 * @brief Construye una matriz de rotación 3x3 para rotar un vector alrededor del eje Z.
 *
 * @param [in] angle Ángulo de rotación en radianes.
 * @return Referencia a una matriz 3x3 de rotación alrededor del eje Z.
 */
//------------------------------------------------------------------------------
Matrix& R_z(double angle);

#endif
