//$Source$
//------------------------------------------------------------------------------
// tests
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
//
/**@file tests.cpp
* @brief Tests de las funciones.
*
* @author Rubén García Eguizábal
* @bug No hay bugs
*/
//------------------------------------------------------------------------------
#include "..\include\matrix.hpp"
#include "..\include\R_x.hpp"
#include "..\include\R_y.hpp"
#include "..\include\R_z.hpp"
#include "..\include\AccelPointMass.hpp"
#include "../include/Cheb3D.hpp"
#include "../include/EccAnom.hpp"
#include "../include/SAT_Const.hpp"
#include "../include/MeanObliquity.hpp"
#include "../include/Frac.hpp"
#include "../include/Mjday.hpp"
#include "../include/Mjday_TDB.hpp"
#include "../include/Position.hpp"
#include "../include/Sign.hpp"
#include "../include/timediff.hpp"
#include "..\include\global.hpp"
#include "..\include\AzElPa.hpp"
#include "..\include\IERS.hpp"
#include "..\include\Legendre.hpp"
#include "..\include\TimeUpdate.hpp"
#include "..\include\NutAngles.hpp"
#include "..\include\AccelHarmonic.hpp"
#include "..\include\EqnEquinox.hpp"
#include "..\include\JPL_Eph_DE430.hpp"
#include "..\include\LTC.hpp"
#include "..\include\NutMatrix.hpp"
#include "..\include\PoleMatrix.hpp"
#include "..\include\PrecMatrix.hpp"
#include "..\include\gmst.hpp"
#include "..\include\gast.hpp"
#include "..\include\MeasUpdate.hpp"
#include "..\include\G_AccelHarmonic.hpp"
#include "..\include\GHAMatrix.hpp"
#include "..\include\Accel.hpp"
#include "..\include\VarEqn.hpp"
#include "..\include\DEInteg.hpp"

#include <iostream>
#include <cstdio>
#include <cmath>

int tests_run = 0;

#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) \
    do                \
    {                 \
        if (!(test))  \
        {             \
            FAIL();   \
            return 1; \
        }             \
    } while (0)
#define _verify(test)   \
    do                  \
    {                   \
        int r = test(); \
        tests_run++;    \
        if (r)          \
            return r;   \
    } while (0)

int m_equals(Matrix A, Matrix B, double p)
{
    if (A.n_row != B.n_row || A.n_column != B.n_column)
        return 0;
    else
        for (int i = 1; i <= A.n_row; i++)
            for (int j = 1; j <= A.n_column; j++)
                if (fabs(A(i, j) - B(i, j)) > p)
                {
                    printf("%2.20lf %2.20lf\n", A(i, j), B(i, j));
                    return 0;
                }

    return 1;
}

int m_sum_01()
{
    int f = 3;
    int c = 4;

    Matrix A(f, c);
    A(1, 1) = 0;
    A(1, 2) = 2;
    A(1, 3) = 8;
    A(1, 4) = 0;
    A(2, 1) = 1;
    A(2, 2) = -1;
    A(2, 3) = 0;
    A(2, 4) = 0;
    A(3, 1) = 0;
    A(3, 2) = 1;
    A(3, 3) = 0;
    A(3, 4) = 5;

    Matrix B(f, c);
    B(1, 1) = 2;
    B(1, 2) = 0;
    B(1, 3) = 0;
    B(1, 4) = 0;
    B(2, 1) = 7;
    B(2, 2) = -2;
    B(2, 3) = 1;
    B(2, 4) = 0;
    B(3, 1) = 0;
    B(3, 2) = -3;
    B(3, 3) = 0;
    B(3, 4) = 2;

    Matrix C(f, c);
    C(1, 1) = 2;
    C(1, 2) = 2;
    C(1, 3) = 8;
    C(1, 4) = 0;
    C(2, 1) = 8;
    C(2, 2) = -3;
    C(2, 3) = 1;
    C(2, 4) = 0;
    C(3, 1) = 0;
    C(3, 2) = -2;
    C(3, 3) = 0;
    C(3, 4) = 7;

    Matrix R = A + B;

    _assert(m_equals(C, R, 1e-10));

    return 0;
}

int m_sub_01()
{
    int f = 3;
    int c = 4;

    Matrix A(f, c);
    A(1, 1) = 0;
    A(1, 2) = 2;
    A(1, 3) = 8;
    A(1, 4) = 0;
    A(2, 1) = 1;
    A(2, 2) = -1;
    A(2, 3) = 0;
    A(2, 4) = 0;
    A(3, 1) = 0;
    A(3, 2) = 1;
    A(3, 3) = 0;
    A(3, 4) = 5;

    Matrix B(f, c);
    B(1, 1) = 2;
    B(1, 2) = 0;
    B(1, 3) = 0;
    B(1, 4) = 0;
    B(2, 1) = 7;
    B(2, 2) = -2;
    B(2, 3) = 1;
    B(2, 4) = 0;
    B(3, 1) = 0;
    B(3, 2) = -3;
    B(3, 3) = 0;
    B(3, 4) = 2;

    Matrix C(f, c);
    C(1, 1) = -2;
    C(1, 2) = 2;
    C(1, 3) = 8;
    C(1, 4) = 0;
    C(2, 1) = -6;
    C(2, 2) = 1;
    C(2, 3) = -1;
    C(2, 4) = 0;
    C(3, 1) = 0;
    C(3, 2) = 4;
    C(3, 3) = 0;
    C(3, 4) = 3;

    Matrix R = A - B;

    _assert(m_equals(C, R, 1e-10));

    return 0;
}

int m_zeros_01()
{
    int f = 3;
    int c = 4;

    Matrix A(f, c);
    A(1, 1) = 0;
    A(1, 2) = 0;
    A(1, 3) = 0;
    A(1, 4) = 0;
    A(2, 1) = 0;
    A(2, 2) = 0;
    A(2, 3) = 0;
    A(2, 4) = 0;
    A(3, 1) = 0;
    A(3, 2) = 0;
    A(3, 3) = 0;
    A(3, 4) = 0;

    Matrix B = zeros(3, 4);

    _assert(m_equals(A, B, 1e-10));

    return 0;
}

int m_zeros_n_01()
{
    int n = 3;

    Matrix A(n);
    A(1, 1) = 0;
    A(1, 2) = 0;
    A(1, 3) = 0;

    Matrix B = zeros(3);

    _assert(m_equals(A, B, 1e-10));

    return 0;
}

int m_mul_01()
{
    int f = 3;
    int c = 4;

    Matrix A(f, c);
    A(1, 1) = 0;
    A(1, 2) = 2;
    A(1, 3) = 8;
    A(1, 4) = 0;
    A(2, 1) = 1;
    A(2, 2) = -1;
    A(2, 3) = 0;
    A(2, 4) = 0;
    A(3, 1) = 0;
    A(3, 2) = 1;
    A(3, 3) = 0;
    A(3, 4) = 5;

    Matrix B(c, f);
    B(1, 1) = 2;
    B(1, 2) = 0;
    B(1, 3) = 0;
    B(2, 1) = 7;
    B(2, 2) = -2;
    B(2, 3) = 1;
    B(3, 1) = 0;
    B(3, 2) = -3;
    B(3, 3) = 0;
    B(4, 1) = 1;
    B(4, 2) = -2;
    B(4, 3) = 0;

    Matrix C(f, f);
    C(1, 1) = 14;
    C(1, 2) = -28;
    C(1, 3) = 2;
    C(2, 1) = -5;
    C(2, 2) = 2;
    C(2, 3) = -1;
    C(3, 1) = 12;
    C(3, 2) = -12;
    C(3, 3) = 1;

    Matrix R = A * B;

    _assert(m_equals(C, R, 1e-10));

    return 0;
}

int m_div_01()
{
    int f = 3;
    int c = 3;

    Matrix A(f, c);
    A(1, 1) = 0;
    A(1, 2) = 2;
    A(1, 3) = 8;
    A(2, 1) = 1;
    A(2, 2) = -1;
    A(2, 3) = 0;
    A(3, 1) = 0;
    A(3, 2) = 1;
    A(3, 3) = 0;

    Matrix B(f, c);
    B(1, 1) = 2;
    B(1, 2) = 0;
    B(1, 3) = 0;
    B(2, 1) = 7;
    B(2, 2) = -2;
    B(2, 3) = 1;
    B(3, 1) = 0;
    B(3, 2) = -3;
    B(3, 3) = 0;

    Matrix C(f, c);
    C(1, 1) = -28;
    C(1, 2) = 8;
    C(1, 3) = -6;
    C(2, 1) = 0.5;
    C(2, 2) = 0;
    C(2, 3) = 0.3333333333333;
    C(3, 1) = 0;
    C(3, 2) = 0;
    C(3, 3) = -0.333333333333;

    Matrix R = A / B;

    _assert(m_equals(C, R, 1e-10));

    return 0;
}

int m_operator_parens_row_column_01()
{
    Matrix A(2, 2);
    A(1, 1) = 5.5;
    A(1, 2) = 6.6;
    A(2, 1) = 7.7;
    A(2, 2) = 8.8;

    _assert(fabs(A(1, 1) - 5.5) < 1e-10);
    _assert(fabs(A(1, 2) - 6.6) < 1e-10);
    _assert(fabs(A(2, 1) - 7.7) < 1e-10);
    _assert(fabs(A(2, 2) - 8.8) < 1e-10);

    return 0;
}

int m_operator_parens_n_01()
{
    Matrix A(2, 2);
    A(1, 1) = 10;
    A(1, 2) = 20;
    A(2, 1) = 30;
    A(2, 2) = 40;

    _assert(fabs(A(1) - 10) < 1e-10);
    _assert(fabs(A(2) - 20) < 1e-10);
    _assert(fabs(A(3) - 30) < 1e-10);
    _assert(fabs(A(4) - 40) < 1e-10);

    return 0;
}

int m_eye_01()
{
    int n = 3;

    Matrix C(n, n);
    C(1, 1) = 1;
    C(1, 2) = 0;
    C(1, 3) = 0;
    C(2, 1) = 0;
    C(2, 2) = 1;
    C(2, 3) = 0;
    C(3, 1) = 0;
    C(3, 2) = 0;
    C(3, 3) = 1;

    Matrix R = eye(n);

    _assert(m_equals(C, R, 1e-10));

    return 0;
}

int m_transpose_01()
{
    Matrix A(2, 3);
    A(1, 1) = 1;
    A(1, 2) = 2;
    A(1, 3) = 3;
    A(2, 1) = 4;
    A(2, 2) = 5;
    A(2, 3) = 6;

    Matrix C(3, 2);
    C(1, 1) = 1;
    C(1, 2) = 4;
    C(2, 1) = 2;
    C(2, 2) = 5;
    C(3, 1) = 3;
    C(3, 2) = 6;

    Matrix R = transpose(A);

    _assert(m_equals(C, R, 1e-10));

    return 0;
}

int m_inv_01()
{
    Matrix A(2, 2);
    A(1, 1) = 4;
    A(1, 2) = 7;
    A(2, 1) = 2;
    A(2, 2) = 6;

    Matrix C(2, 2);
    C(1, 1) = 0.6;
    C(1, 2) = -0.7;
    C(2, 1) = -0.2;
    C(2, 2) = 0.4;

    Matrix R = inv(A);

    _assert(m_equals(C, R, 1e-10));

    return 0;
}

int m_assign_01()
{
    int f = 3;
    int c = 3;

    Matrix A(f, c);
    A(1, 1) = 1;
    A(1, 2) = 2;
    A(1, 3) = 3;
    A(2, 1) = 4;
    A(2, 2) = 5;
    A(2, 3) = 6;
    A(3, 1) = 7;
    A(3, 2) = 8;
    A(3, 3) = 9;

    Matrix B(f, c);
    B = A;

    _assert(m_equals(A, B, 1e-10));

    return 0;
}

int m_sum_scalar_01()
{
    int f = 3, c = 3;
    double scalar = 2.5;

    Matrix A(f, c);
    A(1, 1) = 1;
    A(1, 2) = 2;
    A(1, 3) = 3;
    A(2, 1) = 4;
    A(2, 2) = 5;
    A(2, 3) = 6;
    A(3, 1) = 7;
    A(3, 2) = 8;
    A(3, 3) = 9;

    Matrix C(f, c);
    C(1, 1) = 3.5;
    C(1, 2) = 4.5;
    C(1, 3) = 5.5;
    C(2, 1) = 6.5;
    C(2, 2) = 7.5;
    C(2, 3) = 8.5;
    C(3, 1) = 9.5;
    C(3, 2) = 10.5;
    C(3, 3) = 11.5;

    Matrix R = A + scalar;
    _assert(m_equals(C, R, 1e-10));
    return 0;
}

int m_sub_scalar_01()
{
    int f = 3, c = 3;
    double scalar = 2.5;

    Matrix A(f, c);
    A(1, 1) = 5;
    A(1, 2) = 6;
    A(1, 3) = 7;
    A(2, 1) = 8;
    A(2, 2) = 9;
    A(2, 3) = 10;
    A(3, 1) = 11;
    A(3, 2) = 12;
    A(3, 3) = 13;

    Matrix C(f, c);
    C(1, 1) = 2.5;
    C(1, 2) = 3.5;
    C(1, 3) = 4.5;
    C(2, 1) = 5.5;
    C(2, 2) = 6.5;
    C(2, 3) = 7.5;
    C(3, 1) = 8.5;
    C(3, 2) = 9.5;
    C(3, 3) = 10.5;

    Matrix R = A - scalar;
    _assert(m_equals(C, R, 1e-10));
    return 0;
}

int m_mul_scalar_01()
{
    int f = 2, c = 2;
    double scalar = 3.0;

    Matrix A(f, c);
    A(1, 1) = 1;
    A(1, 2) = 2;
    A(2, 1) = 3;
    A(2, 2) = 4;

    Matrix C(f, c);
    C(1, 1) = 3;
    C(1, 2) = 6;
    C(2, 1) = 9;
    C(2, 2) = 12;

    Matrix R = A * scalar;
    _assert(m_equals(C, R, 1e-10));
    return 0;
}

int m_div_scalar_01()
{
    int f = 2, c = 2;
    double scalar = 2.0;

    Matrix A(f, c);
    A(1, 1) = 2;
    A(1, 2) = 4;
    A(2, 1) = 6;
    A(2, 2) = 8;

    Matrix C(f, c);
    C(1, 1) = 1;
    C(1, 2) = 2;
    C(2, 1) = 3;
    C(2, 2) = 4;

    Matrix R = A / scalar;
    _assert(m_equals(C, R, 1e-10));
    return 0;
}

int m_norm_01()
{
    Matrix A(3);
    A(1) = 2;
    A(2) = 4;
    A(3) = 6;

    double expected = sqrt(56);
    double result = norm(A);
    _assert(m_equals(result, expected, 1e-10));
    return 0;
}

int m_dot_01()
{
    Matrix A(3);
    A(1) = 2;
    A(2) = 4;
    A(3) = 6;

    Matrix B(3);
    B(1) = 1;
    B(2) = 2;
    B(3) = 3;

    double expected = 28;
    double result = dot(A, B);
    _assert(m_equals(result, expected, 1e-10));
    return 0;
}

int m_cross_01()
{
    Matrix A(3);
    A(1) = 2;
    A(2) = 4;
    A(3) = 6;

    Matrix B(3);
    B(1) = 1;
    B(2) = 3;
    B(3) = 2;

    Matrix C(3);
    C(1) = -10;
    C(2) = 2;
    C(3) = 2;

    Matrix result = cross(A, B);

    _assert(m_equals(result, C, 1e-10));
    return 0;
}

int m_extract_vector_01()
{
    Matrix A(3);
    A(1) = -10;
    A(2) = 2;
    A(3) = 2;

    Matrix B(2);
    B(1) = 2;
    B(2) = 2;
    Matrix C = extract_vector(A, 2, 3);

    _assert(m_equals(B, C, 1e-10));
    return 0;
}

int m_extract_row_01()
{
    Matrix A(3, 3);
    A(1, 1) = 5;
    A(1, 2) = 6;
    A(1, 3) = 7;
    A(2, 1) = 8;
    A(2, 2) = 9;
    A(2, 3) = 10;
    A(3, 1) = 11;
    A(3, 2) = 12;
    A(3, 3) = 13;

    Matrix B(3);
    B(1) = 5;
    B(2) = 6;
    B(3) = 7;

    Matrix C = extract_row(A, 1);

    _assert(m_equals(B, C, 1e-10));
    return 0;
}

int m_extract_column_01()
{
    Matrix A(3, 3);
    A(1, 1) = 5;
    A(1, 2) = 6;
    A(1, 3) = 7;
    A(2, 1) = 8;
    A(2, 2) = 9;
    A(2, 3) = 10;
    A(3, 1) = 11;
    A(3, 2) = 12;
    A(3, 3) = 13;

    Matrix B(3);
    B(1) = 5;
    B(2) = 8;
    B(3) = 11;

    Matrix C = extract_column(A, 1);

    _assert(m_equals(B, C, 1e-10));
    return 0;
}

int m_union_vector_01()
{
    Matrix A(3);
    A(1) = -10;
    A(2) = 2;
    A(3) = 2;

    Matrix B(2);
    B(1) = 22;
    B(2) = 6;

    Matrix C(5);
    C(1) = -10;
    C(2) = 2;
    C(3) = 2;
    C(4) = 22;
    C(5) = 6;
    Matrix D = union_vector(A, B);

    _assert(m_equals(D, C, 1e-10));
    return 0;
}

int m_assign_column_01()
{
    Matrix A(3, 3);
    A(1, 1) = 5;
    A(1, 2) = 6;
    A(1, 3) = 7;
    A(2, 1) = 8;
    A(2, 2) = 9;
    A(2, 3) = 10;
    A(3, 1) = 11;
    A(3, 2) = 12;
    A(3, 3) = 13;

    Matrix B(3);
    B(1) = 10;
    B(2) = 3;
    B(3) = 0;

    Matrix C(3, 3);
    C(1, 1) = 10;
    C(1, 2) = 6;
    C(1, 3) = 7;
    C(2, 1) = 3;
    C(2, 2) = 9;
    C(2, 3) = 10;
    C(3, 1) = 0;
    C(3, 2) = 12;
    C(3, 3) = 13;

    Matrix D = assign_column(A, B, 1);

    _assert(m_equals(D, C, 1e-10));
    return 0;
}

int m_assign_row_01()
{
    Matrix A(3, 3);
    A(1, 1) = 5;
    A(1, 2) = 6;
    A(1, 3) = 7;
    A(2, 1) = 8;
    A(2, 2) = 9;
    A(2, 3) = 10;
    A(3, 1) = 11;
    A(3, 2) = 12;
    A(3, 3) = 13;

    Matrix B(3);
    B(1) = 10;
    B(2) = 3;
    B(3) = 0;

    Matrix C(3, 3);
    C(1, 1) = 10;
    C(1, 2) = 3;
    C(1, 3) = 0;
    C(2, 1) = 8;
    C(2, 2) = 9;
    C(2, 3) = 10;
    C(3, 1) = 11;
    C(3, 2) = 12;
    C(3, 3) = 13;

    Matrix D = assign_row(A, B, 1);

    _assert(m_equals(D, C, 1e-10));
    return 0;
}

int m_R_x_01()
{
    double angle = SAT_Const::pi / 2;
    Matrix Rx = R_x(angle);

    Matrix expected(3, 3);
    expected(1, 1) = 1.0;
    expected(1, 2) = 0.0;
    expected(1, 3) = 0.0;
    expected(2, 1) = 0.0;
    expected(2, 2) = 0.0;
    expected(2, 3) = 1.0;
    expected(3, 1) = 0.0;
    expected(3, 2) = -1.0;
    expected(3, 3) = 0.0;

    _assert(m_equals(Rx, expected, 1e-10));
    return 0;
}

int m_R_y_01()
{
    double angle = SAT_Const::pi / 2;
    Matrix Ry = R_y(angle);

    Matrix expected(3, 3);
    expected(1, 1) = 0.0;
    expected(1, 2) = 0.0;
    expected(1, 3) = -1.0;
    expected(2, 1) = 0.0;
    expected(2, 2) = 1.0;
    expected(2, 3) = 0.0;
    expected(3, 1) = 1.0;
    expected(3, 2) = 0.0;
    expected(3, 3) = 0.0;

    _assert(m_equals(Ry, expected, 1e-10));
    return 0;
}

int m_R_z_01()
{
    double angle = SAT_Const::pi / 2;
    Matrix Rz = R_z(angle);

    Matrix expected(3, 3);
    expected(1, 1) = 0.0;
    expected(1, 2) = 1.0;
    expected(1, 3) = 0.0;
    expected(2, 1) = -1.0;
    expected(2, 2) = 0.0;
    expected(2, 3) = 0.0;
    expected(3, 1) = 0.0;
    expected(3, 2) = 0.0;
    expected(3, 3) = 1.0;

    _assert(m_equals(Rz, expected, 1e-10));
    return 0;
}

int accel_point_mass_01()
{
    Matrix r(3);
    r(1) = 7000.0;
    r(2) = 0.0;
    r(3) = 0.0;

    Matrix s(3);
    s(1) = 384400.0;
    s(2) = 0.0;
    s(3) = 0.0;

    double GM = 4902.800066;

    Matrix a = AccelPointMass(r, s, GM);

    Matrix expected(3);
    expected(1) = 1.242260401960810e-09;
    expected(2) = 0.0;
    expected(3) = 0.0;

    _assert(m_equals(a, expected, 1e-10));

    return 0;
}

int cheb_3D_01()
{
    Matrix Cx(3);
    Matrix Cy(3);
    Matrix Cz(3);

    for (int i = 1; i <= 3; i++)
    {
        Cx(i) = 1.0 * i;
        Cy(i) = 2.0 * i;
        Cz(i) = 3.0 * i;
    }

    double t = 3;
    int N = 3;
    double Ta = 1.0;
    double Tb = 5.0;

    Matrix result = Cheb3D(t, N, Ta, Tb, Cx, Cy, Cz);

    Matrix expected(3);
    expected(1) = -2.0;
    expected(2) = -4.0;
    expected(3) = -6.0;

    _assert(m_equals(result, expected, 1e-10));

    return 0;
}

int ecc_anom_01()
{
    double M = 1.0;
    double e = 0.3;
    Matrix E = EccAnom(M, e);
    double expected = 1.28809131321184;
    _assert(m_equals(E(1), expected, 1e-10));

    return 0;
}

int frac_func_01()
{
    _assert(m_equals(Frac(5.75), 0.75, 1e-10));
    _assert(m_equals(Frac(3.0), 0.0, 1e-10));
    _assert(m_equals(Frac(-2.75), 0.25, 1e-10));
    return 0;
}

int mean_obliquity_01()
{
    double Mjd_TT = SAT_Const::MJD_J2000;

    double expected = 84381.448 / 3600.0 * SAT_Const::Rad;
    double result = MeanObliquity(Mjd_TT);

    _assert(m_equals(result, expected, 1e-10));
    return 0;
}

int mjday_01()
{
    int yr = 2000;
    int mon = 1;
    int day = 1;

    double Mjd = Mjday(yr, mon, day);

    double expected = 51544.5;
    _assert(m_equals(Mjd, expected, 1e-10));
    return 0;
}

int mjday_TDB_01()
{
    double Mjd_TT = 51544.5;

    double Mjd_TDB = Mjday_TDB(Mjd_TT);

    double expected = Mjd_TT + (0.001658 * std::sin(628.3076 * (0.0) + 6.2401) +
                                0.000022 * std::sin(575.3385 * (0.0) + 4.2970) +
                                0.000014 * std::sin(1256.6152 * (0.0) + 6.1969) +
                                0.000005 * std::sin(606.9777 * (0.0) + 4.0212) +
                                0.000005 * std::sin(52.9691 * (0.0) + 0.4444) +
                                0.000002 * std::sin(21.3299 * (0.0) + 5.5431) +
                                0.000010 * std::sin(628.3076 * (0.0) + 4.2490)) /
                                   86400.0;

    _assert(m_equals(Mjd_TDB, expected, 1e-10));
    return 0;
}

int position_01()
{
    double lon = 0.0;
    double lat = SAT_Const::pi / 4.0;
    double h = 0.0;

    Matrix r = Position(lon, lat, h);

    Matrix expected(3);

    expected(1) = 4.517590383043712e+06;
    expected(2) = 0.0;
    expected(3) = 4.487347916379808e+06;

    _assert(m_equals(r, expected, 1e-8));

    return 0;
}

int sign_01()
{
    double result = sign_(5.0, 3.0);
    _assert(m_equals(result, 5.0, 1e-10));
    return 0;
}

int timediff_01()
{
    double UT1_UTC = 0.3341;
    double TAI_UTC = 37.0;

    auto [UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC] = timediff(UT1_UTC, TAI_UTC);

    double UT1_TAI_expected = -36.6659;
    double UTC_GPS_expected = -18.0;
    double UT1_GPS_expected = -17.6659;
    double TT_UTC_expected = 69.184;
    double GPS_UTC_expected = 18.0;

    _assert(std::abs(UT1_TAI - UT1_TAI_expected) < 1e-10);
    _assert(std::abs(UTC_GPS - UTC_GPS_expected) < 1e-10);
    _assert(std::abs(UT1_GPS - UT1_GPS_expected) < 1e-10);
    _assert(std::abs(TT_UTC - TT_UTC_expected) < 1e-10);
    _assert(std::abs(GPS_UTC - GPS_UTC_expected) < 1e-10);

    return 0;
}

int azelpa_01()
{
    Matrix s(3);
    s(1) = 1.0;
    s(2) = 1.0;
    s(3) = std::sqrt(2.0);

    auto [Az, El, dAds, dEds] = AzElPa(s);

    double expected_Az = SAT_Const::pi / 4.0;
    double expected_El = SAT_Const::pi / 4.0;

    _assert(std::abs(Az - expected_Az) < 1e-10);
    _assert(std::abs(El - expected_El) < 1e-10);

    Matrix expected_dAds(1, 3);
    expected_dAds(1, 1) = 0.5;
    expected_dAds(1, 2) = -0.5;
    expected_dAds(1, 3) = 0.0;

    Matrix expected_dEds(1, 3);
    expected_dEds(1, 1) = -1.0 / 4.0;
    expected_dEds(1, 2) = -1.0 / 4.0;
    expected_dEds(1, 3) = 0.353553390593274;

    _assert(m_equals(dAds, expected_dAds, 1e-10));
    _assert(m_equals(dEds, expected_dEds, 1e-10));

    return 0;
}

int iers_01()
{

    double Mjd_UTC = 37666.0;
    string interp = "l";

    tuple[x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC] = IERS(Mjd_UTC, interp);

    _assert(std::abs(x_pole - (-0.015900 / SAT_Const::Arcs)) < 1e-10);
    _assert(std::abs(y_pole - 0.214100 / SAT_Const::Arcs) < 1e-10);
    _assert(std::abs(UT1_UTC - 0.0320547) < 1e-10);
    _assert(fabs(LOD - 0.0016690) < 1e-10);
    _assert(std::abs(dpsi - 0.063979 / SAT_Const::Arcs) < 1e-10);
    _assert(std::abs(deps - 0.006290 / SAT_Const::Arcs) < 1e-10);
    _assert(std::abs(dx_pole - 0.0) < 1e-10);
    _assert(std::abs(dy_pole - 0.0) < 1e-10);
    _assert(std::abs(TAI_UTC - 2.0) < 1e-10);

    return 0;
}

int legendre_01()
{
    int n = 5;
    int m = 5;
    double fi = 0.5;

    tuple[pnm, dpnm] = Legendre(n, m, fi);

    Matrix expected_pnm(6, 6);

    expected_pnm(1, 1) = 1.0;
    expected_pnm(1, 2) = 0.0;
    expected_pnm(1, 3) = 0.0;
    expected_pnm(1, 4) = 0.0;
    expected_pnm(1, 5) = 0.0;
    expected_pnm(1, 6) = 0.0;

    expected_pnm(2, 1) = 0.830389391308554;
    expected_pnm(2, 2) = 1.52001758503058;
    expected_pnm(2, 3) = 0.0;
    expected_pnm(2, 4) = 0.0;
    expected_pnm(2, 5) = 0.0;
    expected_pnm(2, 6) = 0.0;

    expected_pnm(3, 1) = -0.347097518865836;
    expected_pnm(3, 2) = 1.62950155523887;
    expected_pnm(3, 3) = 1.49139129468805;
    expected_pnm(3, 4) = 0.0;
    expected_pnm(3, 5) = 0.0;
    expected_pnm(3, 6) = 0.0;

    expected_pnm(4, 1) = -1.17378701262255;
    expected_pnm(4, 2) = 0.212202357272447;
    expected_pnm(4, 3) = 1.89174148838053;
    expected_pnm(4, 4) = 1.41368608598461;
    expected_pnm(4, 5) = 0.0;
    expected_pnm(4, 6) = 0.0;

    expected_pnm(5, 1) = -0.767399315461537;
    expected_pnm(5, 2) = -1.38808376073941;
    expected_pnm(5, 3) = 0.786498890737644;
    expected_pnm(5, 4) = 2.03327163957131;
    expected_pnm(5, 5) = 1.31588285891418;
    expected_pnm(5, 6) = 0.0;

    expected_pnm(6, 1) = 0.445002604545034;
    expected_pnm(6, 2) = -1.56190112426287;
    expected_pnm(6, 3) = -0.973923036046662;
    expected_pnm(6, 4) = 1.25262365245443;
    expected_pnm(6, 5) = 2.0923519453586;
    expected_pnm(6, 6) = 1.21116010580682;

    Matrix expected_dpnm(6, 6);

    expected_dpnm(1, 1) = 0.0;
    expected_dpnm(1, 2) = 0.0;
    expected_dpnm(1, 3) = 0.0;
    expected_dpnm(1, 4) = 0.0;
    expected_dpnm(1, 5) = 0.0;
    expected_dpnm(1, 6) = 0.0;

    expected_dpnm(2, 1) = 1.52001758503058;
    expected_dpnm(2, 2) = -0.830389391308554;
    expected_dpnm(2, 3) = 0.0;
    expected_dpnm(2, 4) = 0.0;
    expected_dpnm(2, 5) = 0.0;
    expected_dpnm(2, 6) = 0.0;

    expected_dpnm(3, 1) = 2.82237948468622;
    expected_dpnm(3, 2) = 2.09258183254477;
    expected_dpnm(3, 3) = -1.62950155523887;
    expected_dpnm(3, 4) = 0.0;
    expected_dpnm(3, 5) = 0.0;
    expected_dpnm(3, 6) = 0.0;

    expected_dpnm(4, 1) = 0.519787497533268;
    expected_dpnm(4, 2) = 5.86628517139076;
    expected_dpnm(4, 3) = 1.39588339664843;
    expected_dpnm(4, 4) = -2.31690068589274;
    expected_dpnm(4, 5) = 0.0;
    expected_dpnm(4, 6) = 0.0;

    expected_dpnm(5, 1) = -4.38950626702873;
    expected_dpnm(5, 2) = 4.09514580882138;
    expected_dpnm(5, 3) = 6.74847324498126;
    expected_dpnm(5, 4) = 0.389534693461711;
    expected_dpnm(5, 5) = -2.87548032867033;
    expected_dpnm(5, 6) = 0.0;

    expected_dpnm(6, 1) = -6.04921704269275;
    expected_dpnm(6, 2) = -4.30024582591831;
    expected_dpnm(6, 3) = 7.20069073552648;
    expected_dpnm(6, 4) = 6.82416323463234;
    expected_dpnm(6, 5) = -0.742203764035525;
    expected_dpnm(6, 6) = -3.30829890700867;

    _assert(m_equals(pnm, expected_pnm, 1e-10));
    _assert(m_equals(dpnm, expected_dpnm, 1e-10));

    return 0;
}

int nutAngles_01()
{

    tuple<double, double> R = NutAngles(2025);

    _assert((fabs(5.81895359450653e-05 - get<0>(R)) < 1e-10) && (fabs(-3.27016318829544e-05 - get<1>(R)) < 1e-10));

    return 0;
}

int timeupdate_01()
{
    Matrix P(2, 2);
    P(1, 1) = 1.0;
    P(1, 2) = 2.0;
    P(2, 1) = 3.0;
    P(2, 2) = 4.0;

    Matrix Phi(2, 2);
    Phi(1, 1) = 0.0;
    Phi(1, 2) = 1.0;
    Phi(2, 1) = -1.0;
    Phi(2, 2) = 0.0;

    double Qdt = 0.5;

    Matrix result = TimeUpdate(P, Phi, Qdt);

    Matrix expected(2, 2);
    expected(1, 1) = 4.5;
    expected(1, 2) = -2.5;
    expected(2, 1) = -1.5;
    expected(2, 2) = 1.5;

    _assert(m_equals(result, expected, 1e-10));

    return 0;
}

int accelHarmonic_01()
{
    Matrix r(3);
    r(1) = 1;
    r(2) = 1;
    r(3) = 1;

    Matrix E(3, 3);
    E(1, 1) = 1;
    E(1, 2) = 2;
    E(1, 3) = 3;
    E(2, 1) = 4;
    E(2, 2) = 5;
    E(2, 3) = 6;
    E(3, 1) = 7;
    E(3, 2) = 8;
    E(3, 3) = 9;

    Matrix acc = AccelHarmonic(r, E, 1, 1);
    Matrix expected(3);
    expected(1) = -3851815228199.55;
    expected(2) = -4592548925930.23;
    expected(3) = -5333282623660.91;
    _assert(m_equals(acc, expected, 1e3));

    return 0;
}

int eqnEquinox_01()
{
    double Mjd_TT = 58000.0;

    double expected = -4.31583150818001e-05;

    double result = EqnEquinox(Mjd_TT);
    _assert(fabs(result - expected) < 1e-9);

    return 0;
}

int JPL_Eph_DE430_01()
{
    auto [r_Mercury, r_Venus, r_Earth, r_Mars, r_Jupiter, r_Saturn, r_Uranus, r_Neptune, r_Pluto, r_Moon, r_Sun] = JPL_Eph_DE430(100000);

    Matrix r_Mercury1(3);
    r_Mercury1(1) = -195379933713.174;
    r_Mercury1(2) = 24889282524.4898;
    r_Mercury1(3) = 13659249623.9719;
    Matrix r_Venus1(3);
    r_Venus1(1) = -74560569435.7555;
    r_Venus1(2) = 134389113640.238;
    r_Venus1(3) = 55519333430.5081;
    Matrix r_Earth1(3);
    r_Earth1(1) = 139822428053.531;
    r_Earth1(2) = -54116562492.9123;
    r_Earth1(3) = -23475004419.5427;
    Matrix r_Mars1(3);
    r_Mars1(1) = -385472438973.092;
    r_Mars1(2) = 40969369956.1128;
    r_Mars1(3) = 24001995646.8146;
    Matrix r_Jupiter1(3);
    r_Jupiter1(1) = -352750667611.312;
    r_Jupiter1(2) = 739008106634.661;
    r_Jupiter1(3) = 322129216748.907;
    Matrix r_Saturn1(3);
    r_Saturn1(1) = -974677952750.267;
    r_Saturn1(2) = -1097154154749.29;
    r_Saturn1(3) = -416216319745.686;
    Matrix r_Uranus1(3);
    r_Uranus1(1) = -2724659946987.63;
    r_Uranus1(2) = 862863757243.402;
    r_Uranus1(3) = 414159147707.102;
    Matrix r_Neptune1(3);
    r_Neptune1(1) = -2773245643825.31;
    r_Neptune1(2) = -3387788674757.46;
    r_Neptune1(3) = -1319742432982.22;
    Matrix r_Pluto1(3);
    r_Pluto1(1) = 3126099113128.16;
    r_Pluto1(2) = 6469644202896.34;
    r_Pluto1(3) = 1041707374400.33;
    Matrix r_Moon1(3);
    r_Moon1(1) = 274034658.475311;
    r_Moon1(2) = 238824661.381708;
    r_Moon1(3) = 82835622.8223107;
    Matrix r_Sun1(3);
    r_Sun1(1) = -139132455067.65;
    r_Sun1(2) = 53933688929.6047;
    r_Sun1(3) = 23367676110.66;

    _assert(m_equals(r_Mercury, transpose(r_Mercury1), 1e-2));
    _assert(m_equals(r_Venus, transpose(r_Venus1), 1e-2));
    _assert(m_equals(r_Earth, transpose(r_Earth1), 1e-2));
    _assert(m_equals(r_Mars, transpose(r_Mars1), 1e-2));
    _assert(m_equals(r_Jupiter, transpose(r_Jupiter1), 1e-2));
    _assert(m_equals(r_Saturn, transpose(r_Saturn1), 1e-2));
    _assert(m_equals(r_Uranus, transpose(r_Uranus1), 1e-2));
    _assert(m_equals(r_Neptune, transpose(r_Neptune1), 1e-2));
    _assert(m_equals(r_Pluto, transpose(r_Pluto1), 1e-2));
    _assert(m_equals(r_Moon, transpose(r_Moon1), 1e-2));
    _assert(m_equals(r_Sun, transpose(r_Sun1), 1e-2));

    return 0;
}

int LTC_01()
{
    Matrix E(3, 3);
    E(1, 1) = -0.841470984807897;
    E(1, 2) = 0.54030230586814;
    E(1, 3) = 0;

    E(2, 1) = -0.454648713412841;
    E(2, 2) = -0.708073418273571;
    E(2, 3) = 0.54030230586814;

    E(3, 1) = 0.291926581726429;
    E(3, 2) = 0.454648713412841;
    E(3, 3) = 0.841470984807897;

    _assert(m_equals(E, LTC(1, 1), 1e-10));

    return 0;
}

int NutMatrix_01()
{
    double Mjd_TT = 58000.0;

    Matrix E(3, 3);
    E(1, 1) = 0.99999999889366;
    E(1, 2) = 4.31583150658842e-05;
    E(1, 3) = 1.87093629248343e-05;

    E(2, 1) = -4.31589451133806e-05;
    E(2, 2) = 0.999999998501602;
    E(2, 3) = 3.36764228041631e-05;

    E(3, 1) = -1.87079094791345e-05;
    E(3, 2) = -3.36772302432786e-05;
    E(3, 3) = 0.999999999257929;

    Matrix &N = NutMatrix(Mjd_TT);

    _assert(m_equals(E, N, 1e-9));

    return 0;
}

int PoleMatrix_01()
{
    double xp = 0.1;
    double yp = 0.2;

    Matrix E(3, 3);
    E(1, 1) = 0.995004165278026;
    E(1, 2) = 0.0198338380762099;
    E(1, 3) = 0.0978433950072557;

    E(2, 1) = 0.0;
    E(2, 2) = 0.980066577841242;
    E(2, 3) = -0.198669330795061;

    E(3, 1) = -0.0998334166468282;
    E(3, 2) = 0.197676811654084;
    E(3, 3) = 0.975170327201816;

    Matrix &M = PoleMatrix(xp, yp);

    _assert(m_equals(E, M, 1e-10));

    return 0;
}

int PrecMatrix_01()
{
    double Mjd_1 = 51544.5;
    double Mjd_2 = 58000.0;

    Matrix E(3, 3);
    E(1, 1) = 0.99999071434493;
    E(1, 2) = -0.00395245373859934;
    E(1, 3) = -0.00171736232685012;
    E(2, 1) = 0.00395245373842227;
    E(2, 2) = 0.999992189018458;
    E(2, 3) = -3.39401643492424e-06;
    E(3, 1) = 0.00171736232725763;
    E(3, 2) = -3.39381022972602e-06;
    E(3, 3) = 0.999998525326472;

    Matrix &P = PrecMatrix(Mjd_1, Mjd_2);

    _assert(m_equals(E, P, 1e-9));
    return 0;
}

int gmst_01()
{
    double Mjd_UT1 = 53736.0;
    double gmstime = gmst(Mjd_UT1);

    double expected = 1.75417498186068;

    _assert(fabs(gmstime - expected) < 1e-9);

    return 0;
}

int gast_01()
{
    double Mjd_UT1 = 53736.0;
    double result = gast(Mjd_UT1);

    double expected = 1.75416613392489;

    _assert(fabs(result - expected) < 1e-9);

    return 0;
}

int MeasUpdate_01()
{
    Matrix x(2, 1);
    x(1, 1) = 1.0;
    x(2, 1) = 2.0;

    Matrix P(2, 2);
    P(1, 1) = 1.0;
    P(1, 2) = 0.0;
    P(2, 1) = 0.0;
    P(2, 2) = 1.0;

    double z = 2.5;
    double g = 2.0;
    double s = 0.5;

    Matrix G(1, 2);
    G(1, 1) = 1.0;
    G(1, 2) = 0.0;

    int n = 2;

    Matrix x_expected(2, 1);
    x_expected(1, 1) = 1.4;
    x_expected(2, 1) = 2.0;

    Matrix P_expected(2, 2);
    P_expected(1, 1) = 0.2;
    P_expected(1, 2) = 0.0;
    P_expected(2, 1) = 0.0;
    P_expected(2, 2) = 1.0;

    Matrix K_expected(2, 1);
    K_expected(1, 1) = 0.8;
    K_expected(2, 1) = 0.0;

    auto [K, x_updated, P_updated] = MeasUpdate(x, z, g, s, G, P, n);

    _assert(m_equals(x_updated, x_expected, 1e-9));
    _assert(m_equals(P_updated, P_expected, 1e-9));
    _assert(m_equals(K, K_expected, 1e-9));

    return 0;
}

int G_AccelHarmonic_01()
{
    Matrix r = zeros(3);
    r(1) = 7000e3;
    r(2) = 0.0;
    r(3) = 0.0;

    Matrix U = eye(3);
    int n_max = 4;
    int m_max = 4;

    Matrix G = G_AccelHarmonic(r, U, n_max, m_max);

    Matrix excepted(3, 3);
    excepted(1, 1) = 2.33048175246608e-06;
    excepted(1, 2) = -1.88080662155699e-11;
    excepted(1, 3) = -5.18909359925601e-11;
    excepted(2, 1) = -1.88040301950557e-11;
    excepted(2, 2) = -1.1636930401132e-06;
    excepted(2, 3) = -5.90145164317381e-12;
    excepted(3, 1) = -5.18900588865551e-11;
    excepted(3, 2) = -5.90145164995007e-12;
    excepted(3, 3) = -1.16678871423606e-06;

    _assert(m_equals(G, excepted, 1e-10));

    return 0;
}

int GHAMatrix_01()
{
    double Mjd_UT1 = 53736.0;

    Matrix E(3, 3);
    E(1, 1) = -0.182343914148772;
    E(1, 2) = 0.983234812734428;
    E(1, 3) = 0.0;

    E(2, 1) = -0.983234812734428;
    E(2, 2) = -0.182343914148772;
    E(2, 3) = 0.0;

    E(3, 1) = 0.0;
    E(3, 2) = 0.0;
    E(3, 3) = 1.0;

    Matrix &GHAmat = GHAMatrix(Mjd_UT1);

    _assert(m_equals(E, GHAmat, 1e-9));
    return 0;
}

int Accel_01()
{
    Matrix Y(6);
    Y(1) = 6524000.000000;  
    Y(2) = 1223000.000000;  
    Y(3) = 2800000.000000;  
    Y(4) = -500.000000;     
    Y(5) = 5700.000000;    
    Y(6) = 3800.000000;     
    double x = 125.349830192;

    Matrix exp(6);
    exp(1) = -500.000000;    
    exp(2) = 5700.000000;    
    exp(3) = 3800.000000;     
    exp(4) = -6.95755523897325;  
    exp(5) = -1.30432214898872;  
    exp(6) = -2.99374240926662;  

    Matrix result = Accel(x, Y);
    cout << "result\n"<<result<<"\n";
    _assert(m_equals(result, exp, 1e-5));
    return 0;	
}

int VarEqn_01()
{
    Matrix A(42);
    A(1) = 7101576.98990384;
    A(2) = 1295199.87127754;
    A(3) = 12739.2823333893;
    A(4) = 576.004651192995;
    A(5) = -3084.62203617269;
    A(6) = -6736.02594582755;
    A(7) = 1.0000252553551;
    A(8) = 7.08259815193455e-06;
    A(9) = 1.91608860896806e-07;
    A(10) = 1.01043851885367e-05;
    A(11) = 2.8276833653238e-06;
    A(12) = 6.44131450915386e-08;
    A(13) = 7.08259832338682e-06;
    A(14) = 0.999988040046621;
    A(15) = 3.53015287901517e-08;
    A(16) = 2.82768356912433e-06;
    A(17) = -4.78603729148054e-06;
    A(18) = 1.18527460879032e-08;
    A(19) = 1.91609345962692e-07;
    A(20) = 3.53016112726607e-08;
    A(21) = 0.999986704774626;
    A(22) = 6.4413632355971e-08;
    A(23) = 1.1852833714462e-08;
    A(24) = -5.31820682447183e-06;
    A(25) = 5.00001498082565;
    A(26) = 1.17818628283062e-05;
    A(27) = 2.68389762643458e-07;
    A(28) = 1.00002526606745;
    A(29) = 7.05571100209626e-06;
    A(30) = 1.3045513745088e-07;
    A(31) = 1.17818628680213e-05;
    A(32) = 4.99995293819717;
    A(33) = 4.93630677857456e-08;
    A(34) = 7.05571115134612e-06;
    A(35) = 0.999988029832341;
    A(36) = 2.39618836715383e-08;
    A(37) = 2.68390167250762e-07;
    A(38) = 4.93631355286403e-08;
    A(39) = 4.99995072081276;
    A(40) = 1.30455626093002e-07;
    A(41) = 2.39619734956897e-08;
    A(42) = 0.999986704276552;

    Matrix R(42);
    R(1) = 576.004651192995;
    R(2) = -3084.62203617269;
    R(3) = -6736.02594582755;
    R(4) = -7.53466223591457;
    R(5) = -1.37422019436673;
    R(6) = -0.0135523187799121;
    R(7) = 1.01043851885367e-05;
    R(8) = 2.8276833653238e-06;
    R(9) = 6.44131450915386e-08;
    R(10) = 2.02219654248567e-06;
    R(11) = 5.62315204439794e-07;
    R(12) = 5.54306321371307e-09;
    R(13) = 2.82768356912433e-06;
    R(14) = -4.78603729148054e-06;
    R(15) = 1.18527460879032e-08;
    R(16) = 5.62315384924689e-07;
    R(17) = -9.58426102130373e-07;
    R(18) = 1.01508481987677e-09;
    R(19) = 6.4413632355971e-08;
    R(20) = 1.1852833714462e-08;
    R(21) = -5.31820682447183e-06;
    R(22) = 5.54345513187772e-09;
    R(23) = 1.01515642021777e-09;
    R(24) = -1.06368579634227e-06;
    R(25) = 1.00002526606745;
    R(26) = 7.05571100209626e-06;
    R(27) = 1.3045513745088e-07;
    R(28) = 1.01107443644805e-05;
    R(29) = 2.81153608797401e-06;
    R(30) = 2.77154087394259e-08;
    R(31) = 7.05571115134612e-06;
    R(32) = 0.999988029832341;
    R(33) = 2.39618836715383e-08;
    R(34) = 2.81153630108919e-06;
    R(35) = -4.79215600734273e-06;
    R(36) = 5.07544128312994e-09;
    R(37) = 1.30455626093002e-07;
    R(38) = 2.39619734956897e-08;
    R(39) = 0.999986704276552;
    R(40) = 2.77159049063872e-08;
    R(41) = 5.07553361934993e-09;
    R(42) = -5.31844727804691e-06;

    Matrix C = VarEqn(0, A);

    _assert(m_equals(R, C, 1e-5));

    return 0;
}

int DEInteg_01()
{

    Matrix A(42, 1);
    A(1, 1) = 7101576.98990384;
    A(2, 1) = 1295199.87127754;
    A(3, 1) = 12739.2823333893;
    A(4, 1) = 576.004651192995;
    A(5, 1) = -3084.62203617269;
    A(6, 1) = -6736.02594582755;
    A(7, 1) = 1.0000252553551;
    A(8, 1) = 7.08259815193455e-06;
    A(9, 1) = 1.91608860896806e-07;
    A(10, 1) = 1.01043851885367e-05;
    A(11, 1) = 2.8276833653238e-06;
    A(12, 1) = 6.44131450915386e-08;
    A(13, 1) = 7.08259832338682e-06;
    A(14, 1) = 0.999988040046621;
    A(15, 1) = 3.53015287901517e-08;
    A(16, 1) = 2.82768356912433e-06;
    A(17, 1) = -4.78603729148054e-06;
    A(18, 1) = 1.18527460879032e-08;
    A(19, 1) = 1.91609345962692e-07;
    A(20, 1) = 3.53016112726607e-08;
    A(21, 1) = 0.999986704774626;
    A(22, 1) = 6.4413632355971e-08;
    A(23, 1) = 1.1852833714462e-08;
    A(24, 1) = -5.31820682447183e-06;
    A(25, 1) = 5.00001498082565;
    A(26, 1) = 1.17818628283062e-05;
    A(27, 1) = 2.68389762643458e-07;
    A(28, 1) = 1.00002526606745;
    A(29, 1) = 7.05571100209626e-06;
    A(30, 1) = 1.3045513745088e-07;
    A(31, 1) = 1.17818628680213e-05;
    A(32, 1) = 4.99995293819717;
    A(33, 1) = 4.93630677857456e-08;
    A(34, 1) = 7.05571115134612e-06;
    A(35, 1) = 0.999988029832341;
    A(36, 1) = 2.39618836715383e-08;
    A(37, 1) = 2.68390167250762e-07;
    A(38, 1) = 4.93631355286403e-08;
    A(39, 1) = 4.99995072081276;
    A(40, 1) = 1.30455626093002e-07;
    A(41, 1) = 2.39619734956897e-08;
    A(42, 1) = 0.999986704276552;

    Matrix C = DEInteg(VarEqn, 0, 360, 1e-12, 1e-12, 42, A);

    Matrix R(42, 1);

    R(1, 1) = 6821609.74522937;
    R(2, 1) = 121982.065011877;
    R(3, 1) = -2357778.20701206;
    R(4, 1) = -2113.23656442262;
    R(5, 1) = -3358.39286741755;
    R(6, 1) = -6281.96749444169;
    R(7, 1) = 1.13712347165515;
    R(8, 1) = 0.026746086542629;
    R(9, 1) = -0.0229614376149257;
    R(10, 1) = 0.000753320162663904;
    R(11, 1) = 0.000113849369546736;
    R(12, 1) = -0.000194190817958882;
    R(13, 1) = 0.0272124349474678;
    R(14, 1) = 0.933969328304028;
    R(15, 1) = -0.00240445552613348;
    R(16, 1) = 0.000120184257952543;
    R(17, 1) = -0.000363739107689719;
    R(18, 1) = -1.5794971980583e-05;
    R(19, 1) = -0.0219713131356206;
    R(20, 1) = -0.00222482527750201;
    R(21, 1) = 0.933725536647773;
    R(22, 1) = -0.000180740980009023;
    R(23, 1) = -1.33551920603137e-05;
    R(24, 1) = -0.000337799228714819;
    R(25, 1) = 381.318839091144;
    R(26, 1) = 2.55208742151169;
    R(27, 1) = -4.1576943617873;
    R(28, 1) = 1.13171673221751;
    R(29, 1) = 0.0150532776208764;
    R(30, 1) = -0.0456780531844568;
    R(31, 1) = 2.58059634087403;
    R(32, 1) = 356.761588658086;
    R(33, 1) = -0.36188929682662;
    R(34, 1) = 0.0155194304382489;
    R(35, 1) = 0.931634940399625;
    R(36, 1) = -0.00288637911880647;
    R(37, 1) = -4.09716577241087;
    R(38, 1) = -0.350909513117262;
    R(39, 1) = 357.275060899264;
    R(40, 1) = -0.0446883505533562;
    R(41, 1) = -0.00270687142267959;
    R(42, 1) = 0.941465188267883;

    _assert(m_equals(R, C, 1e-6));

    return 0;
}

int all_tests()
{
    _verify(m_sum_01);
    _verify(m_sub_01);
    _verify(m_zeros_01);
    _verify(m_mul_01);
    _verify(m_div_01);
    _verify(m_eye_01);
    _verify(m_transpose_01);
    _verify(m_inv_01);
    _verify(m_assign_01);
    _verify(m_sum_scalar_01);

    _verify(m_sub_scalar_01);
    _verify(m_mul_scalar_01);
    _verify(m_div_scalar_01);
    _verify(m_operator_parens_row_column_01);
    _verify(m_operator_parens_n_01);
    _verify(m_zeros_n_01);
    _verify(m_norm_01);
    _verify(m_dot_01);
    _verify(m_cross_01);
    _verify(m_extract_vector_01);

    _verify(m_extract_row_01);
    _verify(m_extract_column_01);
    _verify(m_union_vector_01);
    _verify(m_assign_row_01);
    _verify(m_assign_column_01);
    _verify(m_R_x_01);
    _verify(m_R_y_01);
    _verify(m_R_z_01);
    _verify(accel_point_mass_01);
    _verify(cheb_3D_01);

    _verify(ecc_anom_01);
    _verify(frac_func_01);
    _verify(mean_obliquity_01);
    _verify(mjday_01);
    _verify(mjday_TDB_01);
    _verify(position_01);
    _verify(sign_01);
    _verify(timediff_01);
    _verify(azelpa_01);
    _verify(iers_01);

    _verify(legendre_01);
    _verify(nutAngles_01);
    _verify(timeupdate_01);
    _verify(accelHarmonic_01);
    _verify(eqnEquinox_01);
    _verify(JPL_Eph_DE430_01);
    _verify(LTC_01);
    _verify(NutMatrix_01);
    _verify(PoleMatrix_01);
    _verify(PrecMatrix_01);

    _verify(gmst_01);
    _verify(gast_01);
    _verify(MeasUpdate_01);
    _verify(G_AccelHarmonic_01);
    _verify(GHAMatrix_01);
    _verify(Accel_01);
    _verify(VarEqn_01);
    _verify(DEInteg_01);

    return 0;
}

int main()
{
    eop19620101(21413);
    DE430Coeff(2285, 1020);
    GGM03S(6);
    int result = all_tests();

    if (result == 0)
        printf("PASSED\n");

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
