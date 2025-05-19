//$Header$
//------------------------------------------------------------------------------
//                                Legendre
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/** @file Legendre.hpp
 *  @brief Declaración de la función que calcula los polinomios de Legendre asociados
 *         y sus derivadas respecto al ángulo fi.
 *
 *  Esta función genera los polinomios asociados de Legendre normalizados de Schmidt,
 *  junto con sus derivadas con respecto al ángulo geocéntrico (fi). Los resultados
 *  se utilizan comúnmente en cálculos relacionados con modelos gravitacionales
 *  como el geopotencial terrestre.
 *
 *  @param n Grado máximo del polinomio.
 *  @param m Orden máximo del polinomio.
 *  @param fi Ángulo geocéntrico en radianes.
 *  @return Tupla con dos matrices: pnm (valores de los polinomios) y dpnm (derivadas).
 *
 *  @author Rubén García Eguizábal
 *  @bug No hay bugs conocidos
 */
//------------------------------------------------------------------------------

#ifndef LEGENDRE_HPP
#define LEGENDRE_HPP

#include "../include/matrix.hpp"
#include <tuple>

/**
 * @brief Calcula los polinomios de Legendre asociados normalizados y sus derivadas.
 *
 * @param n Grado máximo.
 * @param m Orden máximo.
 * @param fi Ángulo geocéntrico (radianes).
 * @return Tupla de matrices: pnm (valores) y dpnm (derivadas).
 */
std::tuple<Matrix&, Matrix&> Legendre(int n, int m, double fi);

#endif
