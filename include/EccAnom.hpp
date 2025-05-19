//$Header$
//------------------------------------------------------------------------------
//                                  EccAnom
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file EccAnom.hpp
 * @brief Cabecera para el cálculo de la anomalía excéntrica a partir de la media.
 *
 * Esta función implementa un método iterativo para resolver la ecuación de Kepler,
 * obteniendo la anomalía excéntrica a partir de la anomalía media y la excentricidad.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#ifndef ECCANOM_HPP
#define ECCANOM_HPP

#include "../include/matrix.hpp" 

//------------------------------------------------------------------------------
// Matrix EccAnom(double M, double e)
//------------------------------------------------------------------------------
/**
 * @brief Calcula la anomalía excéntrica usando un método iterativo.
 *
 * @param [in] M Anomalía media [rad].
 * @param [in] e Excentricidad (adimensional).
 * @return Matriz 1x1 que contiene la anomalía excéntrica [rad].
 */
//------------------------------------------------------------------------------

Matrix EccAnom(double M, double e);

#endif // ECCANOM_HPP
