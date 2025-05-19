//$Header$
//------------------------------------------------------------------------------
//                                  Position
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file Position.hpp
 * @brief Cabecera de la función para calcular la posición geocéntrica en coordenadas cartesianas.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------

#ifndef POSITION_HPP
#define POSITION_HPP

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// Matrix& Position(double lon, double lat, double h)
//------------------------------------------------------------------------------
/**
 * @brief Calcula la posición geocéntrica cartesiana a partir de la longitud, latitud y altura.
 *
 * @param [in] lon Longitud geodésica en radianes.
 * @param [in] lat Latitud geodésica en radianes.
 * @param [in] h Altura sobre el elipsoide en metros.
 * @return Vector columna (Matrix) de dimensión 3 con la posición en coordenadas ECEF (Earth-Centered, Earth-Fixed).
 */
//------------------------------------------------------------------------------
Matrix& Position(double lon, double lat, double h);

#endif
