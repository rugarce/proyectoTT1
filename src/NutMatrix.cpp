//$Source$
//------------------------------------------------------------------------------
//                                  NutMatrix
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file NutMatrix.cpp
 * @brief Implementación de la matriz de transformación por nutación.
 *
 * Esta función construye la matriz que representa los efectos de la nutación en
 * las coordenadas celestes, utilizando la oblicuidad media y los ángulos de nutación.
 * La matriz se genera como una combinación de rotaciones alrededor de los ejes X y Z.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#include "../include/NutMatrix.hpp"
#include "../include/MeanObliquity.hpp"
#include "../include/NutAngles.hpp"
#include "../include/R_x.hpp"
#include "../include/R_z.hpp"

Matrix& NutMatrix(double Mjd_TT) {

    double eps = MeanObliquity(Mjd_TT);

    auto[dpsi, deps] = NutAngles(Mjd_TT);

    Matrix& Rx1 = R_x(-eps - deps);
    Matrix& Rz  = R_z(-dpsi);
    Matrix& Rx2 = R_x(+eps);

    return Rx1 * Rz * Rx2;
}
