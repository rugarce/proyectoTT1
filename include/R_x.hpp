//$Header$
//------------------------------------------------------------------------------
//                                     R_x
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file R_x.hpp
 * @brief Cabecera para la matriz de rotación alrededor del eje X.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------

#ifndef _R_x_
#define _R_x_

#include <cmath>
#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// Matrix& R_x(double angle)
//------------------------------------------------------------------------------
/**
 * @brief Construye una matriz de rotación 3x3 para rotar un vector alrededor del eje X.
 *
 * @param [in] angle Ángulo de rotación en radianes.
 * @return Referencia a una matriz 3x3 de rotación alrededor del eje X.
 */
//------------------------------------------------------------------------------
Matrix& R_x(double angle);

#endif
