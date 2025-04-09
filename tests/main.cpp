#include "..\include\matrix.hpp"
#include "..\include\R_x.hpp"
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    Matrix M1(3, 2);
	M1(1,1) = 5;
	
    Matrix M2(3, 2);
	M2(1,1) = -3;
	
    Matrix M3 = M1 - M2;

    Matrix Rx = R_x(30);

    cout << "M1\n" << M1 << "\n";
    cout << "M2\n" << M2 << "\n";
    cout << "M3\n" << M3 << "\n";
    cout << "Rx\n" << Rx << "\n";
	
	cout << M1(1,1) << "\n";

    return 0;
}