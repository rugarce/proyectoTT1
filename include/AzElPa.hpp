//$Header$
//------------------------------------------------------------------------------
//                                  AzElPa
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/** @file AzElPa.hpp
 *  @brief Declaración de la función AzElPa para calcular azimut, elevación y sus derivadas.
 *
 *  La función calcula el ángulo de azimut y elevación a partir de un vector posición,
 *  y devuelve además las matrices de derivadas parciales respecto al vector de entrada.
 *
 *  @param s Vector posición 3D (matriz 3x1).
 *  @return std::tuple<double, double, Matrix&, Matrix&>
 *          Azimut, elevación, derivada del azimut respecto a s,
 *          derivada de la elevación respecto a s.
 *  
 *  @author Rubén García Eguizábal
 *  @bug No hay bugs conocidos
 */
//------------------------------------------------------------------------------

#ifndef AZELPA_HPP
#define AZELPA_HPP

#include "../include/matrix.hpp"
#include <tuple>

/**
 * @brief Calcula azimut, elevación y sus derivadas parciales respecto a vector s.
 * 
 * @param s Vector posición (3x1) en coordenadas cartesianas.
 * @return std::tuple<double, double, Matrix&, Matrix&> Azimut (rad), elevación (rad),
 *         derivada parcial del azimut, derivada parcial de la elevación.
 */
std::tuple<double, double, Matrix&, Matrix&> AzElPa(Matrix& s);

#endif
