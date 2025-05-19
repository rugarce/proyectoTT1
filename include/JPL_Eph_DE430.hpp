//$Header$
//------------------------------------------------------------------------------
//                                  JPL_Eph_DE430
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/** @file JPL_Eph_DE430.hpp
 * @brief Cabecera de la operacion JPL_Eph_DE430.
 *
 *  @author Rubén García Eguizábal
 *  @bug No hay bugs conocidos
 */
//------------------------------------------------------------------------------
#ifndef JPL_EPH_DE430_HPP
#define JPL_EPH_DE430_HPP

#include <tuple>
#include "../include/matrix.hpp"
#include "../include/global.hpp"

//------------------------------------------------------------------------------
// tuple<Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&> JPL_Eph_DE430 (double Mjd_TDB);
//------------------------------------------------------------------------------
/**
 * @brief Operacion JPL_Eph_DE430.
 *
 * @param [in] Mjd_TDB Fecha juliana modificada de TDB. 
 * @return Vectores columna r_Earth(solar system barycenter (SSB)),r_Mars,r_Mercury,r_Venus,
 *  r_Jupiter,r_Saturn,r_Uranus,r_Neptune,r_Pluto,r_Moon,
 *  r_Sun(geocentric equatorial position ([m]) referred to the International Celestial Reference Frame (ICRF)).
 */
//------------------------------------------------------------------------------
tuple<Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&> JPL_Eph_DE430 (double Mjd_TDB);

#endif
