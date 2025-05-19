//$Header$
//------------------------------------------------------------------------------
//                                  NutAngles
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file NutAngles.hpp
 * @brief Cabecera de la operacion NutAngles.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#ifndef NUTANGLES_HPP
#define NUTANGLES_HPP

#include <cmath>
#include <tuple>
#include "../include/matrix.hpp"
using namespace std;

//------------------------------------------------------------------------------
// tuple<double,double> NutAngles (double Mjd_TT)
//------------------------------------------------------------------------------
/**
 * @brief Operacion NutAngles.
 *
 * @param [in] Mjd_TT Fecha juliana modificada (TT).  
 * @return Angulos de nutacion.
 */
//------------------------------------------------------------------------------
tuple<double,double> NutAngles (double Mjd_TT);

#endif