//$Header$
//------------------------------------------------------------------------------
//                                MeasUpdate
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file MeasUpdate.hpp
 * @brief Cabecera de la operación MeasUpdate.
 *
 * Esta función realiza la actualización de estado en un filtro de Kalman,
 * utilizando una nueva medición escalar.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#ifndef MEASUPDATE_HPP
#define MEASUPDATE_HPP

#include "../include/matrix.hpp"
#include <tuple>

using std::tuple;

//------------------------------------------------------------------------------
// tuple<Matrix&, Matrix&, Matrix&> MeasUpdate(Matrix& x, double z, double g, double s, Matrix& G, Matrix& P, int n)
//------------------------------------------------------------------------------
/**
 * @brief Realiza una actualización de medición (filtro de Kalman).
 *
 * @param [in,out] x Vector de estado a actualizar.
 * @param [in] z Valor medido.
 * @param [in] g Valor estimado de la medición.
 * @param [in] s Desviación estándar de la medición.
 * @param [in] G Matriz de sensibilidad (Jacobiano de la medición respecto al estado).
 * @param [in,out] P Matriz de covarianza del estado.
 * @param [in] n Dimensión del estado.
 * @return Tupla con las referencias a: matriz de ganancia de Kalman K, estado x actualizado y matriz de covarianza P actualizada.
 */
//------------------------------------------------------------------------------
tuple<Matrix&, Matrix&, Matrix&> MeasUpdate(Matrix& x, double z, double g, double s, Matrix& G, Matrix& P, int n);

#endif // MEASUPDATE_HPP
