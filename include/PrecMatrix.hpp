//$Header$
//------------------------------------------------------------------------------
//                                  PrecMatrix
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file PrecMatrix.hpp
 * @brief Cabecera de la operación PrecMatrix.
 *
 * Calcula la matriz de precesión entre dos fechas dadas en formato de fecha juliana modificada.
 * Esta matriz es utilizada para transformar coordenadas entre épocas diferentes según la precesión de los equinoccios.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#ifndef PRECMATRIX_HPP
#define PRECMATRIX_HPP

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// Matrix& PrecMatrix(double Mjd_1, double Mjd_2)
//------------------------------------------------------------------------------
/**
 * @brief Calcula la matriz de precesión entre dos épocas.
 *
 * @param [in] Mjd_1 Fecha juliana modificada inicial.
 * @param [in] Mjd_2 Fecha juliana modificada final.
 * @return Referencia a la matriz de rotación 3x3 que representa la precesión.
 */
//------------------------------------------------------------------------------
Matrix& PrecMatrix(double Mjd_1, double Mjd_2);

#endif // PRECMATRIX_HPP
