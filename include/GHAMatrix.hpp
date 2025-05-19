//$Header$
//------------------------------------------------------------------------------
//                                  GHAMatrix
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file GHAMatrix.hpp
 * @brief Cabecera de la operación GHAMatrix.
 *
 * Esta función devuelve la matriz de rotación para la Hora Angular de Greenwich 
 * (GHA), basada en el Tiempo Universal UT1.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#ifndef GHAMATRIX_HPP
#define GHAMATRIX_HPP

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// Matrix& GHAMatrix(double Mjd_UT1)
//------------------------------------------------------------------------------
/**
 * @brief Genera la matriz de rotación correspondiente a la Hora Angular de Greenwich.
 *
 * @param [in] Mjd_UT1 Fecha juliana modificada (UT1).
 * @return Matriz de rotación 3x3 correspondiente a la GHA.
 */
//------------------------------------------------------------------------------
Matrix& GHAMatrix(double Mjd_UT1);

#endif // GHAMATRIX_HPP
