//$Header$
//------------------------------------------------------------------------------
//                                   Sign
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/** @file Sign.hpp
 *  @brief Función para asignar signo de un valor a otro.
 *
 *  La función sign_ devuelve el valor absoluto de `a` con el signo de `b`.
 *
 *  @param a Valor cuyo módulo se quiere conservar.
 *  @param b Valor que proporciona el signo.
 *  @return `a` con el signo de `b`.
 *
 *  @author Rubén García Eguizábal
 *  @bug No hay bugs conocidos
 */
//------------------------------------------------------------------------------

#ifndef SIGN_HPP
#define SIGN_HPP

/**
 * @brief Devuelve el valor absoluto de `a` con el signo de `b`.
 * 
 * @param a Valor cuyo módulo se conserva.
 * @param b Valor que indica el signo.
 * @return double `a` con el signo de `b`.
 */
double sign_(double a, double b);

#endif
