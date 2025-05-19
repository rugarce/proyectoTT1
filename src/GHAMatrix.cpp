//$Source$
//------------------------------------------------------------------------------
//                                  GHAMatrix
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file GHAMatrix.cpp
 * @brief Implementación de la operación GHAMatrix.
 *
 * Esta función construye y devuelve la matriz de rotación correspondiente a 
 * la Hora Angular de Greenwich (GHA), utilizando la función `gast()` para 
 * obtener la GHA en radianes y aplicando una rotación alrededor del eje Z.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#include "../include/GHAMatrix.hpp"
#include "../include/gast.hpp"
#include "../include/R_z.hpp"

Matrix& GHAMatrix(double Mjd_UT1) {
    return R_z(gast(Mjd_UT1));
}
