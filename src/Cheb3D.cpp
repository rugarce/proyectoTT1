//$Source$
//------------------------------------------------------------------------------
//                                  Cheb3D
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file Cheb3D.cpp
 * @brief Implementación de la función de interpolación con polinomios de Chebyshev en 3D.
 *
 * Esta función calcula una interpolación tridimensional usando los coeficientes
 * de los polinomios de Chebyshev mediante el algoritmo de Clenshaw.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#include "../include/Cheb3D.hpp"

Matrix& Cheb3D(double t, int N, double Ta, double Tb, Matrix& Cx, Matrix& Cy, Matrix& Cz) {
    if (t < Ta || t > Tb) {
        cout << "ERROR: Time out of range in Cheb3D::Value";
        exit(EXIT_FAILURE);
    }

    double tau = (2 * t - Ta - Tb) / (Tb - Ta);

    Matrix& f1 = zeros(3);
    Matrix& f2 = zeros(3);
    Matrix& old_f1 = zeros(3);
    for (int i = N; i >= 2; i--) {
        old_f1 = f1;
        f1(1) = 2 * tau * f1(1) - f2(1) + Cx(i);  
        f1(2) = 2 * tau * f1(2) - f2(2) + Cy(i); 
        f1(3) = 2 * tau * f1(3) - f2(3) + Cz(i);  
        f2 = old_f1;
    }

    Matrix& ChebApp= zeros(3);
    ChebApp(1) = tau * f1(1) - f2(1) + Cx(1);
    ChebApp(2) = tau * f1(2) - f2(2) + Cy(1);
    ChebApp(3) = tau * f1(3) - f2(3) + Cz(1);

    return ChebApp;
}
