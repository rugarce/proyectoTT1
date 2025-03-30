#include "..\include\matrix.h"
#include <cstdio>
#include <cmath>

int tests_run = 0;

#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)

int m_equals(Matrix A, Matrix B, double p) {
	if (A.n_row != B.n_row || A.n_column != B.n_column)
		return 0;
	else
		for(int i = 1; i <= A.n_row; i++)
			for(int j = 1; j <= A.n_column; j++)
				if(fabs(A(i,j)-B(i,j)) > p) {
					printf("%2.20lf %2.20lf\n",A(i,j),B(i,j));
					return 0;
				}
	
	return 1;
}

int m_sum_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(f, c);
	B(1,1) = 2; B(1,2) =  0; B(1,3) = 0; B(1,4) = 0;
	B(2,1) = 7; B(2,2) = -2; B(2,3) = 1; B(2,4) = 0;
	B(3,1) = 0; B(3,2) = -3; B(3,3) = 0; B(3,4) = 2;
	
	Matrix C(f, c);
	C(1,1) = 2; C(1,2) =  2; C(1,3) = 8; C(1,4) = 0;
	C(2,1) = 8; C(2,2) = -3; C(2,3) = 1; C(2,4) = 0;
	C(3,1) = 0; C(3,2) = -2; C(3,3) = 0; C(3,4) = 7;
	
	Matrix R = A + B;
    
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_sub_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) = 2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) = 1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(f, c);
	B(1,1) = 2; B(1,2) = 0; B(1,3) = 0; B(1,4) = 0;
	B(2,1) = 7; B(2,2) = -2; B(2,3) = 1; B(2,4) = 0;
	B(3,1) = 0; B(3,2) = -3; B(3,3) = 0; B(3,4) = 2;
	
	Matrix C(f, c);
	C(1,1) = -2; C(1,2) = 2; C(1,3) = 8; C(1,4) = 0;
	C(2,1) = -6; C(2,2) = 1; C(2,3) = -1; C(2,4) = 0;
	C(3,1) = 0; C(3,2) = 4; C(3,3) = 0; C(3,4) = 3;
	
	Matrix R = A - B;
    
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_zeros_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) = 0; A(1,3) = 0; A(1,4) = 0;
	A(2,1) = 0; A(2,2) = 0; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) = 0; A(3,3) = 0; A(3,4) = 0;
	
	Matrix B = zeros(3, 4);
    
    _assert(m_equals(A, B, 1e-10));
    
    return 0;
}

int m_mul_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) = 2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) = 1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(c, f);
	B(1,1) = 2; B(1,2) = 0; B(1,3) = 0; 
	B(2,1) = 7; B(2,2) = -2; B(2,3) = 1; 
	B(3,1) = 0; B(3,2) = -3; B(3,3) = 0; 
	B(4,1) = 1; B(4,2) = -2; B(4,3) = 0;
	
	Matrix C(f, f);
	C(1,1) = 14; C(1,2) = -28; C(1,3) = 2;
	C(2,1) = -5; C(2,2) = 2; C(2,3) = -1; 
	C(3,1) = 12; C(3,2) = -12; C(3,3) = 1;
	
	Matrix R = A * B;
    
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_div_01() {
    int f = 3;
    int c = 3;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) = 2; A(1,3) = 8;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0;
	A(3,1) = 0; A(3,2) = 1; A(3,3) = 0;
	
	Matrix B(f, c);
	B(1,1) = 2; B(1,2) = 0; B(1,3) = 0;
	B(2,1) = 7; B(2,2) = -2; B(2,3) = 1;
	B(3,1) = 0; B(3,2) = -3; B(3,3) = 0;
	
	Matrix C(f, c);
	C(1,1) = -28; C(1,2) = 8; C(1,3) = -6;
	C(2,1) = 0.5; C(2,2) = 0; C(2,3) = 0.3333333333333;
	C(3,1) = 0; C(3,2) = 0; C(3,3) = -0.333333333333; 
	
	Matrix R = A / B;

    cout << "A\n" << A << "\n";
    cout << "B\n" << B << "\n";
    cout << "R\n" << R << "\n";
    cout << "R\n" << C << "\n";
    
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_assign_01() {
    int f = 3;
    int c = 3;

    Matrix A(f, c);
    A(1,1) = 1; A(1,2) = 2; A(1,3) = 3;
    A(2,1) = 4; A(2,2) = 5; A(2,3) = 6;
    A(3,1) = 7; A(3,2) = 8; A(3,3) = 9;

    Matrix B(f, c);
    B = A;  

    _assert(m_equals(A, B, 1e-10));
    
    return 0;
}

int m_sum_scalar_01() {
    int f = 3, c = 3;
    double scalar = 2.5;

    Matrix A(f, c);
    A(1,1) = 1; A(1,2) = 2; A(1,3) = 3;
    A(2,1) = 4; A(2,2) = 5; A(2,3) = 6;
    A(3,1) = 7; A(3,2) = 8; A(3,3) = 9;

    Matrix C(f, c);
    C(1,1) = 3.5; C(1,2) = 4.5; C(1,3) = 5.5;
    C(2,1) = 6.5; C(2,2) = 7.5; C(2,3) = 8.5;
    C(3,1) = 9.5; C(3,2) = 10.5; C(3,3) = 11.5;

    Matrix R = A + scalar;
    _assert(m_equals(C, R, 1e-10));
    return 0;
}

int m_sub_scalar_01() {
    int f = 3, c = 3;
    double scalar = 2.5;

    Matrix A(f, c);
    A(1,1) = 5; A(1,2) = 6; A(1,3) = 7;
    A(2,1) = 8; A(2,2) = 9; A(2,3) = 10;
    A(3,1) = 11; A(3,2) = 12; A(3,3) = 13;

    Matrix C(f, c);
    C(1,1) = 2.5; C(1,2) = 3.5; C(1,3) = 4.5;
    C(2,1) = 5.5; C(2,2) = 6.5; C(2,3) = 7.5;
    C(3,1) = 8.5; C(3,2) = 9.5; C(3,3) = 10.5;

    Matrix R = A - scalar;
    _assert(m_equals(C, R, 1e-10));
    return 0;
}

int m_mul_scalar_01() {
    int f = 2, c = 2;
    double scalar = 3.0;

    Matrix A(f, c);
    A(1,1) = 1; A(1,2) = 2;
    A(2,1) = 3; A(2,2) = 4;

    Matrix C(f, c);
    C(1,1) = 3; C(1,2) = 6;
    C(2,1) = 9; C(2,2) = 12;

    Matrix R = A * scalar;
    _assert(m_equals(C, R, 1e-10));
    return 0;
}

int m_div_scalar_01() {
    int f = 2, c = 2;
    double scalar = 2.0;

    Matrix A(f, c);
    A(1,1) = 2; A(1,2) = 4;
    A(2,1) = 6; A(2,2) = 8;

    Matrix C(f, c);
    C(1,1) = 1; C(1,2) = 2;
    C(2,1) = 3; C(2,2) = 4;

    Matrix R = A / scalar;
    _assert(m_equals(C, R, 1e-10));
    return 0;
}

int all_tests()
{
    _verify(m_sum_01);
    _verify(m_sub_01);
    _verify(m_zeros_01);
	_verify(m_sum_01);
	_verify(m_assign_01);
	_verify(m_sum_scalar_01);
	_verify(m_sub_scalar_01);
	_verify(m_mul_scalar_01);
	_verify(m_div_scalar_01);
    _verify(m_div_01);

    return 0;
}

int main()
{
    int result = all_tests();

    if (result == 0)
        printf("PASSED\n");

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
