//$Source$
//------------------------------------------------------------------------------
//                                   TimeUpdate
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/** @file TimeUpdate.cpp
 *  @brief Implementación de la función TimeUpdate.
 *
 *  Esta función calcula la actualización temporal de la matriz de covarianza P
 *  aplicando la propagación a través de la matriz Phi y sumando el ruido de 
 *  proceso escalado Qdt si es distinto de cero.
 *
 *
 *  @author Rubén García Eguizábal
 *  @bug No hay bugs conocidos
 */
//------------------------------------------------------------------------------
#include "../include/matrix.hpp"
#include "../include/TimeUpdate.hpp"

Matrix& TimeUpdate(Matrix& P, Matrix& Phi, double Qdt) {
    Matrix& result = Phi * P * transpose(Phi);
    if (Qdt != 0.0) {
        result = result + Qdt;
    }
    return result;
}
