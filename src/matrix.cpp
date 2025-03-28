#include "..\include\matrix.h"

Matrix::Matrix(const int n_row, const int n_column) {
    if (n_row <= 0 || n_column <= 0) {
		cout << "Matrix create: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	
	this->n_row = n_row;
	this->n_column = n_column;
	this->data = (double **) malloc(n_row*sizeof(double *));
	
    if (this->data == NULL) {
		cout << "Matrix create: error in data\n";
        exit(EXIT_FAILURE);
	}
	
	for(int i = 0; i < n_row; i++) {
		this->data[i] = (double *) malloc(n_column*sizeof(double));
	}
}

double& Matrix::operator () (const int row, const int column) {
	if (row <= 0 || row > this->n_row || column <= 0 || column > this->n_column) {
		cout << "Matrix get: error in row/column\n";
        exit(EXIT_FAILURE);
	}
	
	return this->data[row - 1][column - 1];
}

Matrix& Matrix::operator + (Matrix &m) {
	if (this->n_row != m.n_row || this->n_column != m.n_column) {
		cout << "Matrix sum: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	
	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	
    for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) + m(i,j);
		}
	}
	
	return *m_aux;
}

Matrix& Matrix::operator - (Matrix &m) {
	if (this->n_row != m.n_row || this->n_column != m.n_column) {
		cout << "Matrix sub: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	
	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	
    for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) - m(i,j);
		}
	}
	
	return *m_aux;
}

ostream& operator << (ostream &o, Matrix &m) {
	for (int i = 1; i <= m.n_row; i++) {
        for (int j = 1; j <= m.n_column; j++)
			printf("%5.20lf ", m(i,j));
        o << "\n";
    }
	
    return o;
}

Matrix& zeros(const int n_row, const int n_column) {
	Matrix *m_aux = new Matrix(n_row, n_column);
	
	for(int i = 1; i <= n_row; i++) {
		for(int j = 1; j <= n_column; j++) {
			(*m_aux)(i,j) = 0;
		}
	}
	
	return (*m_aux);
}

// Operador de multiplicación de matrices
Matrix& Matrix::operator * (Matrix &m) {
    if (this->n_column != m.n_row) {
        cout << "Matrix multiplication: error in dimensions\n";
        exit(EXIT_FAILURE);
    }

    Matrix *m_aux = new Matrix(this->n_row, m.n_column);

    for (int i = 1; i <= this->n_row; i++) {
        for (int j = 1; j <= m.n_column; j++) {
            (*m_aux)(i, j) = 0; // Inicializa el valor de la celda
            for (int k = 1; k <= this->n_column; k++) {
                (*m_aux)(i, j) += (*this)(i, k) * m(k, j);
            }
        }
    }

    return *m_aux;
}

// Operador de división de matrices (usando la inversa)
Matrix& Matrix::operator / (Matrix &m) {
    if (this->n_row != m.n_row || this->n_column != m.n_column) {
        cout << "Matrix division: error in dimensions\n";
        exit(EXIT_FAILURE);
    }

    Matrix m_inv = m.inv(); // Calculamos la inversa de la matriz m

    return *this * m_inv; // Multiplicamos por la inversa
}

// Operador de asignación
Matrix& Matrix::operator = (const Matrix &m) {
    if (this == &m) return *this; // Evitar asignación a sí misma

    // Liberar memoria actual
    for (int i = 0; i < this->n_row; i++) {
        free(this->data[i]);
    }
    free(this->data);

    // Asignar nuevas dimensiones y memoria
    this->n_row = m.n_row;
    this->n_column = m.n_column;
    this->data = (double **)malloc(this->n_row * sizeof(double *));
    
    if (this->data == NULL) {
        cout << "Matrix assignment: error in data allocation\n";
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < this->n_row; i++) {
        this->data[i] = (double *)malloc(this->n_column * sizeof(double));
        if (this->data[i] == NULL) {
            cout << "Matrix assignment: error in row allocation\n";
            exit(EXIT_FAILURE);
        }
    }

    // Copiar los datos de la matriz m
    for (int i = 1; i <= this->n_row; i++) {
        for (int j = 1; j <= this->n_column; j++) {
            (*this)(i, j) = m(i, j);
        }
    }

    return *this;
}

// Método para matriz identidad
Matrix& Matrix::eye(const int n) {
    Matrix *m_aux = new Matrix(n, n);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            (*m_aux)(i, j) = (i == j) ? 1 : 0;
        }
    }
    
    return *m_aux;
}

// Método para la traspuesta
Matrix& Matrix::transpose() {
    Matrix *m_aux = new Matrix(this->n_column, this->n_row);

    for (int i = 1; i <= this->n_row; i++) {
        for (int j = 1; j <= this->n_column; j++) {
            (*m_aux)(j, i) = (*this)(i, j);
        }
    }

    return *m_aux;
}

// Método para la inversa (usando el algoritmo de Gauss-Jordan)
Matrix& Matrix::inv() {
    if (this->n_row != this->n_column) {
        cout << "Matrix inverse: matrix must be square\n";
        exit(EXIT_FAILURE);
    }

    // Crear una copia de la matriz
    Matrix *m_aux = new Matrix(this->n_row, this->n_column);
    for (int i = 1; i <= this->n_row; i++) {
        for (int j = 1; j <= this->n_column; j++) {
            (*m_aux)(i, j) = (*this)(i, j);
        }
    }

    // Crear la matriz identidad
    Matrix *I = new Matrix(this->n_row, this->n_column);
    I->eye(this->n_row);

    // Gauss-Jordan
    for (int i = 1; i <= this->n_row; i++) {
        double pivot = (*m_aux)(i, i);
        if (fabs(pivot) < 1e-12) {
            cout << "Matrix inverse: matrix is singular\n";
            exit(EXIT_FAILURE);
        }

        // Dividir la fila por el pivote
        for (int j = 1; j <= this->n_column; j++) {
            (*m_aux)(i, j) /= pivot;
            (*I)(i, j) /= pivot;
        }

        // Hacer cero debajo del pivote
        for (int j = i + 1; j <= this->n_row; j++) {
            double factor = (*m_aux)(j, i);
            for (int k = 1; k <= this->n_column; k++) {
                (*m_aux)(j, k) -= factor * (*m_aux)(i, k);
                (*I)(j, k) -= factor * (*I)(i, k);
            }
        }
    }

    // Hacer cero encima del pivote
    for (int i = this->n_row; i >= 1; i--) {
        for (int j = i - 1; j >= 1; j--) {
            double factor = (*m_aux)(j, i);
            for (int k = 1; k <= this->n_column; k++) {
                (*m_aux)(j, k) -= factor * (*m_aux)(i, k);
                (*I)(j, k) -= factor * (*I)(i, k);
            }
        }
    }

    return *I;
}
