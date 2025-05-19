//$Header$
//------------------------------------------------------------------------------
//                                  PoleMatrix
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file PoleMatrix.hpp
 * @brief Cabecera para la generación de la matriz de corrección por movimiento del polo.
 *
 * Esta función construye la matriz de transformación que representa el movimiento polar,
 * corrigiendo la orientación de la Tierra en función de los desplazamientos del polo en X e Y.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#ifndef POLEMATRIX_HPP
#define POLEMATRIX_HPP

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// Matrix& PoleMatrix(double xp, double yp)
//------------------------------------------------------------------------------
/**
 * @brief Genera la matriz de transformación por movimiento polar.
 *
 * Calcula y devuelve una referencia a la matriz de transformación que representa
 * la corrección de la orientación terrestre debido al movimiento del polo,
 * en función de los desplazamientos en las coordenadas X e Y.
 *
 * @param [in] xp Desplazamiento del polo en la dirección X [rad].
 * @param [in] yp Desplazamiento del polo en la dirección Y [rad].
 * @return Referencia a la matriz de transformación 3x3 por movimiento polar.
 */
//------------------------------------------------------------------------------
Matrix& PoleMatrix(double xp, double yp);

#endif
