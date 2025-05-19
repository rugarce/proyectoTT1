//$Header$
//------------------------------------------------------------------------------
//                                   Mjday
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file Mjday.hpp
 * @brief Cabecera de la función para calcular el día juliano modificado a partir de fecha y hora.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------

#ifndef MJDAY_HPP
#define MJDAY_HPP

//------------------------------------------------------------------------------
// double Mjday(int yr, int mon, int day, int hr = 0, int min = 0, int sec = 0)
//------------------------------------------------------------------------------
/**
 * @brief Calcula el día juliano modificado (MJD) a partir de fecha y hora.
 *
 * @param [in] yr  Año.
 * @param [in] mon Mes.
 * @param [in] day Día.
 * @param [in] hr  Hora (por defecto 0).
 * @param [in] min Minutos (por defecto 0).
 * @param [in] sec Segundos (por defecto 0).
 * @return Día Juliano Modificado (MJD).
 */
//------------------------------------------------------------------------------
double Mjday(int yr, int mon, int day, int hr = 0, int min = 0, int sec = 0);

#endif

