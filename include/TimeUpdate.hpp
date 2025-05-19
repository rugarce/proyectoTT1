//$Header$
//------------------------------------------------------------------------------
//                                   TimeUpdate
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/** @file TimeUpdate.hpp
 *  @brief Prototipo de la función que actualiza la matriz de covarianza en el
 *         paso temporal de un filtro de Kalman.
 *
 *  La función realiza la propagación temporal de la matriz de covarianza P 
 *  usando la matriz de transición de estado Phi y, opcionalmente, añade el 
 *  ruido de proceso escalado Qdt.
 *
 *  @author Rubén García Eguizábal
 *  @bug No hay bugs conocidos
 */
//------------------------------------------------------------------------------

#ifndef TIMEUPDATE_HPP
#define TIMEUPDATE_HPP

#include "../include/matrix.hpp"

/**
 * @brief Actualiza la matriz de covarianza propagándola temporalmente.
 * 
 * @param P Matriz de covarianza previa.
 * @param Phi Matriz de transición de estado.
 * @param Qdt Ruido de proceso escalado (por defecto 0.0).
 * @return Matriz de covarianza actualizada.
 */
Matrix& TimeUpdate(Matrix& P, Matrix& Phi, double Qdt = 0.0);

#endif
