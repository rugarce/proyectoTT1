//$Header$
//------------------------------------------------------------------------------
//                                  VarEqn
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file VarEqn.hpp
 * @brief Cabecera de la operación VarEqn.
 *
 * Define la función que calcula simultáneamente la derivada del vector de 
 * estado (posición y velocidad) y de la matriz de variación del estado.
 * 
 * Se utiliza típicamente en propagadores que integran tanto la dinámica del 
 * satélite como la sensibilidad del sistema (ej. para el filtro de Kalman).
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#ifndef VAREQN_HPP
#define VAREQN_HPP

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// Matrix& VarEqn(double x, Matrix& yPhi)
//------------------------------------------------------------------------------
/**
 * @brief Evalúa las derivadas del estado y la matriz de transición.
 *
 * Esta función calcula las derivadas de la posición y velocidad, así como de 
 * la matriz de transición del sistema dinámico, en un solo paso.
 *
 * @param [in] x     Tiempo transcurrido desde Mjd_UTC inicial [s].
 * @param [in] yPhi  Vector columna 42x1 que contiene:
 *                   - Las 6 primeras filas: vector de estado [r; v].
 *                   - Las 36 siguientes: matriz Phi (6x6) apilada por columnas.
 * @return Derivada del vector yPhi (también 42x1).
 */
//------------------------------------------------------------------------------
Matrix& VarEqn(double x, Matrix& yPhi);

#endif // VAREQN_HPP
