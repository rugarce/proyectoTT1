//$Source$
//------------------------------------------------------------------------------
//                              G_AccelHarmonic
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file G_AccelHarmonic.cpp
 * @brief Implementación de la operación G_AccelHarmonic.
 *
 * Esta función implementa el cálculo de la matriz Jacobiana de la aceleración 
 * gravitacional debida al potencial armónico, utilizando diferencias centradas.
 * El cálculo se realiza perturbando cada componente del vector de posición 
 * y observando el cambio resultante en la aceleración.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#include "../include/G_AccelHarmonic.hpp"
#include "../include/AccelHarmonic.hpp"

Matrix& G_AccelHarmonic(Matrix& r, Matrix& U, int n_max, int m_max) {
    double d = 1.0; 

    Matrix &G = zeros(3,3);
    Matrix &dr = zeros(3);
    Matrix& da = zeros(3);

    for (int i = 1; i <= 3; ++i) {
        dr=zeros(3);

        dr(i) = d;

        da = AccelHarmonic(r + dr / 2.0, U, n_max, m_max) - AccelHarmonic(r - dr / 2.0, U, n_max, m_max);

        assign_column(G,da/d,i);
    }

    return G;
}
