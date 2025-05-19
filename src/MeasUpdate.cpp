//$Source$
//------------------------------------------------------------------------------
//                                MeasUpdate
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file MeasUpdate.cpp
 * @brief Implementación de la operación MeasUpdate.
 *
 * Esta función implementa una única iteración de actualización de un filtro de Kalman 
 * para una medición escalar. Se calcula la ganancia de Kalman y se actualizan tanto 
 * el vector de estado como la matriz de covarianza del estado.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#include "../include/MeasUpdate.hpp"

tuple<Matrix&, Matrix&, Matrix&> MeasUpdate(Matrix& x, double z, double g, double s, Matrix& G, Matrix& P, int n) {
    int m = 1; 

    Matrix& Inv_W = zeros(m, m);
    Inv_W(1,1) = s * s;

    Matrix& K = P * transpose(G) * inv(Inv_W + G * P * transpose(G));

    Matrix& A= zeros(1);
    A(1) = z - g;

    x = x + K * A;

    P = (eye(n) - K * G) * P;

    return tie(K, x, P);
}
