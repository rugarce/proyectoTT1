//$Header$
//------------------------------------------------------------------------------
//                                      gmst
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file gmst.hpp
 * @brief Cabecera de la operación gmst.
 *
 * Calcula el Tiempo Sideral Medio de Greenwich (GMST) a partir de la fecha juliana
 * modificada en tiempo universal (UT1).
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#ifndef GMST_HPP
#define GMST_HPP

//------------------------------------------------------------------------------
// double gmst(double Mjd_UT1)
//------------------------------------------------------------------------------
/**
 * @brief Calcula el tiempo sideral medio de Greenwich (GMST).
 *
 * @param [in] Mjd_UT1 Fecha juliana modificada en tiempo universal (UT1).
 * @return Tiempo sideral medio de Greenwich [rad].
 */
//------------------------------------------------------------------------------
double gmst(double Mjd_UT1);

#endif // GMST_HPP
