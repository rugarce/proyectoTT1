//$Header$
//------------------------------------------------------------------------------
//                                  Cheb3D
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file Cheb3D.hpp
 * @brief Cabecera de la función de interpolación con polinomios de Chebyshev en 3D.
 *
 * Esta función permite calcular una aproximación de la posición tridimensional
 * usando coeficientes de polinomios de Chebyshev.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#ifndef CHEB3D_HPP
#define CHEB3D_HPP

#include "../include/matrix.hpp" 

//------------------------------------------------------------------------------
// Matrix& Cheb3D(double t, int N, double Ta, double Tb, Matrix& Cx, Matrix& Cy, Matrix& Cz)
//------------------------------------------------------------------------------
/**
 * @brief Aproxima la posición tridimensional a partir de polinomios de Chebyshev.
 *
 * @param [in] t Tiempo en el que se desea la evaluación.
 * @param [in] N Orden del polinomio de Chebyshev.
 * @param [in] Ta Tiempo inicial del intervalo.
 * @param [in] Tb Tiempo final del intervalo.
 * @param [in] Cx Coeficientes de Chebyshev en la componente X.
 * @param [in] Cy Coeficientes de Chebyshev en la componente Y.
 * @param [in] Cz Coeficientes de Chebyshev en la componente Z.
 * @return Aproximación del vector de posición tridimensional en el instante t.
 */
//------------------------------------------------------------------------------
Matrix& Cheb3D(double t, int N, double Ta, double Tb, Matrix& Cx, Matrix& Cy, Matrix& Cz);

#endif


