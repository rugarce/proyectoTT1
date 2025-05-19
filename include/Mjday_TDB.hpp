//$Header$
//------------------------------------------------------------------------------
//                                  Mjday_TDB
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file Mjday_TDB.hpp
 * @brief Cabecera de la función para calcular el día juliano modificado en tiempo dinámico (TDB).
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------

#ifndef MJDAY_TDB_HPP
#define MJDAY_TDB_HPP

//------------------------------------------------------------------------------
// double Mjday_TDB(double Mjd_TT)
//------------------------------------------------------------------------------
/**
 * @brief Calcula el día juliano modificado en tiempo dinámico (TDB) a partir del tiempo terrestre (TT).
 *
 * @param [in] Mjd_TT Día Juliano Modificado en tiempo terrestre (TT).
 * @return Día Juliano Modificado en tiempo dinámico (TDB).
 */
//------------------------------------------------------------------------------
double Mjday_TDB(double Mjd_TT);

#endif

