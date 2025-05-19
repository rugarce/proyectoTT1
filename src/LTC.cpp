//$Source$
//------------------------------------------------------------------------------
//                                  LTC
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file LTC.cpp
 * @brief Implementación de la transformación desde el sistema local tangente.
 *
 * Esta función construye la matriz de transformación desde un sistema de
 * coordenadas local tangente a la superficie terrestre, en base a los
 * ángulos de latitud y longitud proporcionados. Internamente usa rotaciones
 * sobre los ejes Y y Z, y reordena las filas de la matriz resultante.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#include "../include/LTC.hpp"
#include "../include/R_y.hpp"
#include "../include/R_z.hpp"

Matrix& LTC(double lon, double lat) {
    Matrix& M = R_y(-1.0 * lat) * R_z(lon);

    for (int j = 1; j <= 3; j++) {
        double aux = M(1, j);
        M(1, j) = M(2, j);
        M(2, j) = M(3, j);
        M(3, j) = aux;
    }

    return M;
}
