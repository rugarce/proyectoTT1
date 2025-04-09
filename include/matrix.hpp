#ifndef _MATRIX_
#define _MATRIX_

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

class Matrix {
public:
    int n_row, n_column;
	double **data;

    // Parameterized constructor
    Matrix(const int n_row, const int n_column);
	Matrix(const int v_size);

	
	// Member operators
	double& operator () (const int row, const int column);
	double& operator () (const int n);
	Matrix& operator + (Matrix &m);
	Matrix& operator - (Matrix &m);
	Matrix& operator * (Matrix &m);  
    Matrix& operator / (Matrix &m);  
    Matrix& operator = (Matrix &m); 
	Matrix& operator * (double scalar);
	Matrix& operator + (double scalar);
	Matrix& operator - (double scalar);
	Matrix& operator / (double scalar);         
	
	// Non-member operators
	friend ostream& operator << (ostream &o, Matrix &m);
};

// Operator overloading
ostream& operator << (ostream &o, Matrix &m);

// Methods
Matrix& zeros(const int n_row, const int n_column);
Matrix& eye(const int n); 
Matrix& transpose(Matrix &m);      
Matrix inv(Matrix &m); 
Matrix& zeros(const int n);

// Vector operations
double norm(Matrix &v);             
double dot(Matrix &a, Matrix &b);   
Matrix &cross(Matrix &a, Matrix &b);
Matrix &extract_vector(Matrix &m, const int n, const int k);
Matrix &extract_row(Matrix &m, const int n);
Matrix &extract_column(Matrix &m, const int n);
Matrix &union_vector(Matrix &m, Matrix &k);
Matrix &assign_column(Matrix &m, Matrix &k, const int n);
Matrix &assign_row(Matrix &m, Matrix &k, const int n);
#endif