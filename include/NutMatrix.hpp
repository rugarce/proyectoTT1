//$Header$
//------------------------------------------------------------------------------
//                                  NutMatrix
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file NutMatrix.hpp
 * @brief Cabecera para la generación de la matriz de nutación.
 *
 * Esta función construye la matriz de transformación que representa los efectos de la nutación
 * sobre el sistema de coordenadas celeste, en función de la fecha juliana modificada (TT).
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#ifndef NUTMATRIX_HPP
#define NUTMATRIX_HPP

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// Matrix& NutMatrix(double Mjd_TT)
//------------------------------------------------------------------------------
/**
 * @brief Genera la matriz de transformación por nutación.
 *
 * Calcula y devuelve una referencia a la matriz que representa la transformación
 * de nutación basada en el modelo de precesión y nutación de la IAU, en función
 * del tiempo terrestre (TT).
 *
 * @param [in] Mjd_TT Fecha juliana modificada (Tiempo Terrestre).
 * @return Referencia a la matriz de transformación 3x3 por nutación.
 */
//------------------------------------------------------------------------------
Matrix& NutMatrix(double Mjd_TT);

#endif
