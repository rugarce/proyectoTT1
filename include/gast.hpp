//$Header$
//------------------------------------------------------------------------------
//                                      gast
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file gast.hpp
 * @brief Cabecera de la operación gast.
 *
 * Calcula el Tiempo Sideral Aparente de Greenwich (GAST) a partir de la fecha juliana
 * modificada en tiempo universal (UT1), sumando la ecuación de los equinoccios al GMST.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#ifndef GAST_HPP
#define GAST_HPP

//------------------------------------------------------------------------------
// double gast(double Mjd_UT1)
//------------------------------------------------------------------------------
/**
 * @brief Calcula el Tiempo Sideral Aparente de Greenwich (GAST).
 *
 * @param [in] Mjd_UT1 Fecha juliana modificada en tiempo universal (UT1).
 * @return Tiempo sideral aparente de Greenwich [rad].
 */
//------------------------------------------------------------------------------
double gast(double Mjd_UT1);

#endif // GAST_HPP
