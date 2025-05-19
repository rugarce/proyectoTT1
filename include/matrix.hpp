//$Header$
//------------------------------------------------------------------------------
// 									matrix
//------------------------------------------------------------------------------
// Proyecto-TTI.
//
// Created: 2025/05/18
//
/**@file matrix.hpp
 * @brief Cabecera de las operaciones de las matrices.
 *
 * @author Rubén García Eguizábal
 * @bug No hay bugs
 */
//------------------------------------------------------------------------------
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


	//------------------------------------------------------------------------------
	// Matrix(const int n_row, const int n_column)
	//------------------------------------------------------------------------------
	/**
	 * @brief Constructor de matriz.
	 *
	 * @param [in] n_row numero de filas.
	 * @param [in] n_column numero de columnas.
	 * @return Matriz de tamaño n_row por n_column.
	 */
	//------------------------------------------------------------------------------
    Matrix(const int n_row, const int n_column);

	//------------------------------------------------------------------------------
	// Matrix(const int v_size)
	//------------------------------------------------------------------------------
	/**
	 * @brief Constructor de vector.
	 *
	 * @param [in] v_size tamaño.
	 * @return Vector de tamaño n.
	 */
	//------------------------------------------------------------------------------
	Matrix(const int v_size);

	//------------------------------------------------------------------------------
	// Matrix()
	//------------------------------------------------------------------------------
	/**
	 * @brief Constructor de matriz.
	 *
	 * @return Matriz vacia.
	 */
	//------------------------------------------------------------------------------
	Matrix();

	
	// Member operators

	//------------------------------------------------------------------------------
	// double& operator()(const int row, const int column)
	//------------------------------------------------------------------------------
	/**
	 * @brief Acceso a la componente de una matriz.
	 *
	 * @param [in] row numero de fila.
	 * @param [in] column numero de columna.
	 * @return Puntero a posicion row,column.
	 */
	//------------------------------------------------------------------------------
	double& operator () (const int row, const int column);

	//------------------------------------------------------------------------------
	// double& operator()(const int n)
	//------------------------------------------------------------------------------
	/**
	 * @brief Acceso a una componente de un vector.
	 *
	 * @param [in] n posicion.
	 * @return Puntero a posicion n.
	 */
	//------------------------------------------------------------------------------
	double& operator () (const int n);

	//------------------------------------------------------------------------------
	// Matrix& operator+(Matrix &m)
	//------------------------------------------------------------------------------
	/**
	 * @brief Suma de matrices.
	 *
	 * @param [in] m matriz a sumar.
	 * @return Resultado de la suma.
	 */
	//------------------------------------------------------------------------------
	Matrix& operator + (Matrix &m);

	//------------------------------------------------------------------------------
	// Matrix& operator-(Matrix &m)
	//------------------------------------------------------------------------------
	/**
	 * @brief Resta de matrices.
	 *
	 * @param [in] m matriz a restar.
	 * @return Resultado de la resta.
	 */
	//------------------------------------------------------------------------------
	Matrix& operator - (Matrix &m);

	//------------------------------------------------------------------------------
	// Matrix& operator*(Matrix &m)
	//------------------------------------------------------------------------------
	/**
	 * @brief Producto matricial.
	 *
	 * @param [in] m matriz a multiplicar.
	 * @return Resultado del producto.
	 */
	//------------------------------------------------------------------------------
	Matrix& operator * (Matrix &m); 

	//------------------------------------------------------------------------------
	// Matrix& operator/(Matrix &m)
	//------------------------------------------------------------------------------
	/**
	 * @brief División entre matrices.
	 *
	 * @param [in] m matriz dividendo.
	 * @return Resultado de la división.
	 */
	//------------------------------------------------------------------------------
    Matrix& operator / (Matrix &m);  

	//------------------------------------------------------------------------------
	// Matrix& operator=(Matrix &m)
	//------------------------------------------------------------------------------
	/**
	 * @brief Asignación de una matriz.
	 *
	 * @param [in] m matriz a asignar.
	 * @return Referencia a la matriz actual.
	 */
	//------------------------------------------------------------------------------
    Matrix& operator = (Matrix &m); 

	//------------------------------------------------------------------------------
	// Matrix& operator * (double scalar);
	//------------------------------------------------------------------------------
	/**
	 * @brief Multiplicación escalar de la matriz.
	 *
	 * @param [in] scalar valor escalar.
	 * @return Resultado de la multiplicación.
	 */
	//------------------------------------------------------------------------------
	Matrix& operator * (double scalar);

	//------------------------------------------------------------------------------
	// Matrix& operator + (double scalar);
	//------------------------------------------------------------------------------
	/**
	 * @brief Suma escalar a todos los elementos de la matriz.
	 *
	 * @param [in] scalar valor escalar.
	 * @return Resultado de la suma.
	 */
	//------------------------------------------------------------------------------
	Matrix& operator + (double scalar);

	//------------------------------------------------------------------------------
	// Matrix& operator - (double scalar);
	//------------------------------------------------------------------------------
	/**
	 * @brief Resta escalar a todos los elementos de la matriz.
	 *
	 * @param [in] scalar valor escalar.
	 * @return Resultado de la resta.
	 */
	//------------------------------------------------------------------------------
	Matrix& operator - (double scalar);

	//------------------------------------------------------------------------------
	// Matrix& operator / (double scalar); 
	//------------------------------------------------------------------------------
	/**
	 * @brief División escalar de la matriz.
	 *
	 * @param [in] scalar valor escalar.
	 * @return Resultado de la división.
	 */
	//------------------------------------------------------------------------------
	Matrix& operator / (double scalar);         
	
	// Non-member operators

	//------------------------------------------------------------------------------
	// friend ostream& operator << (ostream &o, Matrix &m)
	//------------------------------------------------------------------------------
	/**
	 * @brief Mostrar por salida una matriz.
	 *
	 * @param [in,out] o flujo de salida.
	 * @param [in] m matriz a mostrar.
	 * @return Flujo de salida modificado.
	 */
	//------------------------------------------------------------------------------
	friend ostream& operator << (ostream &o, Matrix &m);
};

// Operator overloading

//------------------------------------------------------------------------------
// ostream& operator << (ostream &o, Matrix &m);
//------------------------------------------------------------------------------
/**
 * @brief Sobrecarga del operador de salida para imprimir matrices.
 *
 * @param [in,out] o flujo de salida.
 * @param [in] m matriz a imprimir.
 * @return Referencia al flujo de salida modificado.
 */
//------------------------------------------------------------------------------
ostream& operator << (ostream &o, Matrix &m);

// Methods

//------------------------------------------------------------------------------
// Matrix& zeros(const int n_row, const int n_column)
//------------------------------------------------------------------------------
/**
 * @brief Crea una matriz de ceros.
 *
 * @param [in] n_row número de filas.
 * @param [in] n_column número de columnas.
 * @return Matriz con todos los elementos igual a cero.
 */
//------------------------------------------------------------------------------
Matrix& zeros(const int n_row, const int n_column);

//------------------------------------------------------------------------------
// Matrix& eye(const int n)
//------------------------------------------------------------------------------
/**
 * @brief Crea una matriz identidad de tamaño n x n.
 *
 * @param [in] n tamaño de la matriz.
 * @return Matriz identidad.
 */
//------------------------------------------------------------------------------
Matrix& eye(const int n); 

//------------------------------------------------------------------------------
// Matrix& transpose(Matrix &m)
//------------------------------------------------------------------------------
/**
 * @brief Calcula la transpuesta de una matriz.
 *
 * @param [in] m matriz a transponer.
 * @return Matriz transpuesta.
 */
//------------------------------------------------------------------------------
Matrix& transpose(Matrix &m);      

//------------------------------------------------------------------------------
// Matrix& inv(Matrix &m)
//------------------------------------------------------------------------------
/**
 * @brief Calcula la inversa de una matriz.
 *
 * @param [in] m matriz a invertir.
 * @return Matriz inversa.
 */
//------------------------------------------------------------------------------
Matrix& inv(Matrix &m);

//------------------------------------------------------------------------------
// Matrix& zeros(const int n)
//------------------------------------------------------------------------------
/**
 * @brief Crea un vector fila de ceros.
 *
 * @param [in] n tamaño del vector.
 * @return Vector fila con elementos cero.
 */
//------------------------------------------------------------------------------
Matrix& zeros(const int n);

// Vector operations

//------------------------------------------------------------------------------
// double norm(Matrix &v)
//------------------------------------------------------------------------------
/**
 * @brief Calcula la norma euclídea de un vector.
 *
 * @param [in] v vector del cual se obtiene la norma.
 * @return Valor de la norma.
 */
//------------------------------------------------------------------------------
double norm(Matrix &v);    

//------------------------------------------------------------------------------
// double dot(Matrix &a, Matrix &b)
//------------------------------------------------------------------------------
/**
 * @brief Producto escalar entre dos vectores.
 *
 * @param [in] a primer vector.
 * @param [in] b segundo vector.
 * @return Resultado del producto escalar.
 */
//------------------------------------------------------------------------------
double dot(Matrix &a, Matrix &b);   

//------------------------------------------------------------------------------
// Matrix &cross(Matrix &a, Matrix &b)
//------------------------------------------------------------------------------
/**
 * @brief Producto vectorial entre dos vectores de dimensión 3.
 *
 * @param [in] a primer vector.
 * @param [in] b segundo vector.
 * @return Vector resultante del producto vectorial.
 */
//------------------------------------------------------------------------------
Matrix &cross(Matrix &a, Matrix &b);

//------------------------------------------------------------------------------
// Matrix &extract_vector(Matrix &m, const int n, const int k)
//------------------------------------------------------------------------------
/**
 * @brief Extrae un subvector de tamaño k-n a partir de la posicion n de un vector.
 *
 * @param [in] m vector origen.
 * @param [in] n posicion inicial.
 * @param [in] k posicion final.
 * @return Vector extraído.
 */
//------------------------------------------------------------------------------
Matrix &extract_vector(Matrix &m, const int n, const int k);

//------------------------------------------------------------------------------
// Matrix &extract_row(Matrix &m, const int n)
//------------------------------------------------------------------------------
/**
 * @brief Extrae la fila n de la matriz.
 *
 * @param [in] m matriz origen.
 * @param [in] n índice de la fila.
 * @return Fila extraída como vector fila.
 */
//------------------------------------------------------------------------------
Matrix &extract_row(Matrix &m, const int n);

//------------------------------------------------------------------------------
// Matrix &extract_column(Matrix &m, const int n)
//------------------------------------------------------------------------------
/**
 * @brief Extrae la columna n de la matriz.
 *
 * @param [in] m matriz origen.
 * @param [in] n índice de la columna.
 * @return Columna extraída como vector fila.
 */
//------------------------------------------------------------------------------
Matrix &extract_column(Matrix &m, const int n);

//------------------------------------------------------------------------------
// Matrix &union_vector(Matrix &m, Matrix &k)
//------------------------------------------------------------------------------
/**
 * @brief Une dos vectores consecutivamente.
 *
 * @param [in] m primer vector.
 * @param [in] k segundo vector.
 * @return Vector combinado.
 */
//------------------------------------------------------------------------------
Matrix &union_vector(Matrix &m, Matrix &k);

//------------------------------------------------------------------------------
// Matrix &assign_column(Matrix &m, Matrix &k, const int n)
//------------------------------------------------------------------------------
/**
 * @brief Asigna un vector a la columna n de una matriz.
 *
 * @param [in,out] m matriz destino.
 * @param [in] k vector columna.
 * @param [in] n índice de la columna a asignar.
 * @return Matriz modificada.
 */
//------------------------------------------------------------------------------
Matrix &assign_column(Matrix &m, Matrix &k, const int n);

//------------------------------------------------------------------------------
// Matrix &assign_row(Matrix &m, Matrix &k, const int n)
//------------------------------------------------------------------------------
/**
 * @brief Asigna un vector a la fila n de una matriz.
 *
 * @param [in,out] m matriz destino.
 * @param [in] k vector fila.
 * @param [in] n índice de la fila a asignar.
 * @return Matriz modificada.
 */
//------------------------------------------------------------------------------
Matrix &assign_row(Matrix &m, Matrix &k, const int n);
#endif