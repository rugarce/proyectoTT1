//$Source$
//------------------------------------------------------------------------------
//                                  PrecMatrix
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file PrecMatrix.cpp
 * @brief Implementación de la operación PrecMatrix.
 *
 * Calcula la matriz de precesión utilizando los elementos zeta, z y theta
 * derivados del modelo IAU de precesión para transformar coordenadas ecuatoriales
 * entre dos épocas distintas. Utiliza rotaciones sucesivas alrededor de los ejes Z, Y, Z.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#include "../include/PrecMatrix.hpp"
#include "../include/R_z.hpp"
#include "../include/R_y.hpp"
#include "../include/SAT_Const.hpp"

Matrix& PrecMatrix(double Mjd_1, double Mjd_2) {
    double T = (Mjd_1 - SAT_Const::MJD_J2000) / 36525.0;
    double dT = (Mjd_2 - Mjd_1) / 36525.0;

    double zeta = ((2306.2181 + (1.39656 - 0.000139 * T) * T) + 
                   ((0.30188 - 0.000344 * T) + 0.017998 * dT) * dT) * dT / SAT_Const::Arcs;

    double z = zeta + ((0.79280 + 0.000411 * T) + 0.000205 * dT) * dT * dT / SAT_Const::Arcs;

    double theta = ((2004.3109 - (0.85330 + 0.000217 * T) * T) -
                    ((0.42665 + 0.000217 * T) + 0.041833 * dT) * dT) * dT / SAT_Const::Arcs;

    Matrix& Rz1 = R_z(-z);
    Matrix& Ry  = R_y(theta);
    Matrix& Rz2 = R_z(-zeta);

    return Rz1 * Ry * Rz2;
}
