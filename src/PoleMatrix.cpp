//$Source$
//------------------------------------------------------------------------------
//                                  PoleMatrix
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file PoleMatrix.cpp
 * @brief Implementación de la matriz de transformación por movimiento polar.
 *
 * Esta función construye la matriz que representa la corrección del sistema de
 * referencia debido al movimiento del polo terrestre. Utiliza rotaciones sucesivas
 * en torno a los ejes Y y X con los ángulos de desplazamiento proporcionados.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
#include "../include/PoleMatrix.hpp"
#include "../include/R_y.hpp"
#include "../include/R_x.hpp"

Matrix& PoleMatrix(double xp, double yp) {
    Matrix& Ry = R_y(-xp);
    Matrix& Rx = R_x(-yp);

    return Ry * Rx;
}
