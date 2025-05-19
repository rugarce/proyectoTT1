//$Header$
//------------------------------------------------------------------------------
//                                  DEInteg
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file DEInteg.hpp
 * @brief Cabecera de la operación DEInteg.
 *
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#ifndef DEINTEG_HPP
#define DEINTEG_HPP

#include "../include/matrix.hpp" 

//------------------------------------------------------------------------------
// Matrix& DEInteg(Matrix& f(double t, Matrix& y), double t, double tout, double relerr, double abserr, int n_eqn, Matrix& y)
//------------------------------------------------------------------------------
/**
 * @brief Función principal de integración diferencial utilizando un método adaptativo multistep.
 * 
 * @param f       Función del sistema de ecuaciones diferenciales ordinarias (ODEs): f(t, y)
 * @param t       Tiempo inicial
 * @param tout    Tiempo objetivo de integración
 * @param relerr  Error relativo permitido
 * @param abserr  Error absoluto permitido
 * @param n_eqn   Número de ecuaciones a integrar
 * @param y       Estado inicial del sistema (vector de tamaño n_eqn)
 * @return Matrix& Estado del sistema en el tiempo tout
 */
//------------------------------------------------------------------------------
Matrix& DEInteg(Matrix& f(double t, Matrix& y), double t, double tout, double relerr, double abserr, int n_eqn, Matrix& y);

#endif