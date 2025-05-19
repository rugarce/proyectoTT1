//$Source$
//------------------------------------------------------------------------------
//                                Legendre
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/** @file Legendre.cpp
 *  @brief Implementación de la función que computa los polinomios asociados de Legendre
 *         normalizados de Schmidt y sus derivadas respecto al ángulo geocéntrico.
 *
 *  La función construye recursivamente los polinomios de Legendre asociados (Pnm)
 *  normalizados según Schmidt hasta el grado `n` y orden `m`, así como sus derivadas
 *  respecto al ángulo `fi`. Estos valores son fundamentales en la representación
 *  del potencial gravitacional terrestre en coordenadas esféricas.
 *
 *  @param n Grado máximo.
 *  @param m Orden máximo.
 *  @param fi Ángulo geocéntrico (latitud geocéntrica) en radianes.
 *  @return Tupla con dos matrices:
 *          - pnm: valores de los polinomios Pnm.
 *          - dpnm: derivadas de Pnm con respecto a fi.
 *
 *  @note Se utilizan fórmulas de recurrencia para calcular tanto los valores
 *        como las derivadas. Las matrices resultantes tienen tamaño (n+1)x(m+1).
 *
 *  @warning Se utilizan referencias a matrices creadas dinámicamente; el manejo de memoria
 *           deberá cuidarse para evitar fugas.
 *
 *  @author Rubén García Eguizábal
 *  @bug No hay bugs conocidos
 */
//------------------------------------------------------------------------------
#include "../include/matrix.hpp"
#include "../include/Legendre.hpp"
#include <cmath> 
#include <tuple>

using namespace std;

tuple<Matrix&, Matrix&> Legendre(int n, int m, double fi) {
    Matrix& pnm = zeros(n + 1, m + 1);
    Matrix& dpnm = zeros(n + 1, m + 1);

    pnm(1, 1) = 1.0;
    dpnm(1, 1) = 0.0;
    pnm(2, 2) = sqrt(3.0) * cos(fi);
    dpnm(2, 2) = -sqrt(3.0) * sin(fi);

    for (int i = 2; i <= n; ++i) {
        pnm(i + 1, i + 1) = sqrt((2.0 * i + 1.0) / (2.0 * i)) * cos(fi) * pnm(i, i);
    }

    for (int i = 2; i <= n; ++i) {
        dpnm(i + 1, i + 1) = sqrt((2.0 * i + 1.0) / (2.0 * i)) * 
                            (cos(fi) * dpnm(i, i) - sin(fi) * pnm(i, i));
    }

    for (int i = 1; i <= n; ++i) {
        pnm(i + 1, i) = sqrt(2.0 * i + 1.0) * sin(fi) * pnm(i, i);
    }

    for (int i = 1; i <= n; ++i) {
        dpnm(i + 1, i) = sqrt(2.0 * i + 1.0) * 
                        (cos(fi) * pnm(i, i) + sin(fi) * dpnm(i, i));
    }

    int j = 0, k = 2;
    while (true) {
        for (int i = k; i <= n; ++i) {
            pnm(i + 1, j + 1) = sqrt((2.0 * i + 1.0) / ((i - j) * (i + j))) *
                                (sqrt(2.0 * i - 1.0) * sin(fi) * pnm(i, j + 1) -
                                 sqrt((i + j - 1.0) * (i - j - 1.0) / (2.0 * i - 3.0)) * pnm(i - 1, j + 1));
        }
        j++;
        k++;
        if (j > m) break;
    }

    j = 0;
    k = 2;
    while (true) {
        for (int i = k; i <= n; ++i) {
            dpnm(i + 1, j + 1) = sqrt((2.0 * i + 1.0) / ((i - j) * (i + j))) *
                                (sqrt(2.0 * i - 1.0) * sin(fi) * dpnm(i, j + 1) +
                                 sqrt(2.0 * i - 1.0) * cos(fi) * pnm(i, j + 1) -
                                 sqrt((i + j - 1.0) * (i - j - 1.0) / (2.0 * i - 3.0)) * dpnm(i - 1, j + 1));
        }
        j++;
        k++;
        if (j > m) break;
    }

    return tie(pnm, dpnm);
}
