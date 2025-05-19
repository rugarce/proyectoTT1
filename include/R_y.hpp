//$Header$
//------------------------------------------------------------------------------
//                                     R_y
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file R_y.hpp
 * @brief Cabecera para la matriz de rotación alrededor del eje Y.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------

#ifndef _R_y_
#define _R_y_

#include <cmath>
#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// Matrix& R_y(double angle)
//------------------------------------------------------------------------------
/**
 * @brief Construye una matriz de rotación 3x3 para rotar un vector alrededor del eje Y.
 *
 * @param [in] angle Ángulo de rotación en radianes.
 * @return Referencia a una matriz 3x3 de rotación alrededor del eje Y.
 */
//------------------------------------------------------------------------------
Matrix& R_y(double angle);

#endif
