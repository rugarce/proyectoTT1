#include "..\include\matrix.h"

Matrix::Matrix(const int n_row, const int n_column)
{
    if (n_row <= 0 || n_column <= 0)
    {
        cout << "Matrix create: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
    }

    this->n_row = n_row;
    this->n_column = n_column;
    this->data = (double **)malloc(n_row * sizeof(double *));

    if (this->data == NULL)
    {
        cout << "Matrix create: error in data\n";
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n_row; i++)
    {
        this->data[i] = (double *)malloc(n_column * sizeof(double));
    }
}

double &Matrix::operator()(const int row, const int column)
{
    if (row <= 0 || row > this->n_row || column <= 0 || column > this->n_column)
    {
        cout << "Matrix get: error in row/column\n";
        exit(EXIT_FAILURE);
    }

    return this->data[row - 1][column - 1];
}

Matrix::Matrix(const int v_size)
{
    if (v_size < 0)
    {
        cout << "Vector create: error in v_size\n";
        exit(EXIT_FAILURE);
    }

    this->n_row = 1;
    this->n_column = v_size;
    this->data = (double **)malloc(n_row * sizeof(double *));

    if (this->data == NULL)
    {
        cout << "Vector create: error in data\n";
        exit(EXIT_FAILURE);
    }

    this->data[0] = (double *)calloc(n_column, sizeof(double));
}

double &Matrix::operator()(const int n)
{
    if (n <= 0 || n > this->n_row * this->n_column)
    {
        cout << "Vector get: error in n\n";
        exit(EXIT_FAILURE);
    }

    return this->data[(n - 1) / this->n_column][(n - 1) % this->n_column];
}

Matrix &Matrix::operator+(Matrix &m)
{
    if (this->n_row != m.n_row || this->n_column != m.n_column)
    {
        cout << "Matrix sum: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
    }

    Matrix *m_aux = new Matrix(this->n_row, this->n_column);

    for (int i = 1; i <= this->n_row; i++)
    {
        for (int j = 1; j <= this->n_column; j++)
        {
            (*m_aux)(i, j) = (*this)(i, j) + m(i, j);
        }
    }

    return *m_aux;
}

Matrix &Matrix::operator-(Matrix &m)
{
    if (this->n_row != m.n_row || this->n_column != m.n_column)
    {
        cout << "Matrix sub: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
    }

    Matrix *m_aux = new Matrix(this->n_row, this->n_column);

    for (int i = 1; i <= this->n_row; i++)
    {
        for (int j = 1; j <= this->n_column; j++)
        {
            (*m_aux)(i, j) = (*this)(i, j) - m(i, j);
        }
    }

    return *m_aux;
}

ostream &operator<<(ostream &o, Matrix &m)
{
    for (int i = 1; i <= m.n_row; i++)
    {
        for (int j = 1; j <= m.n_column; j++)
            printf("%5.20lf ", m(i, j));
        o << "\n";
    }

    return o;
}

Matrix &zeros(const int n_row, const int n_column)
{
    Matrix *m_aux = new Matrix(n_row, n_column);

    for (int i = 1; i <= n_row; i++)
    {
        for (int j = 1; j <= n_column; j++)
        {
            (*m_aux)(i, j) = 0;
        }
    }

    return (*m_aux);
}

Matrix &Matrix::operator*(Matrix &m)
{
    if (this->n_column != m.n_row)
    {
        cout << "Matrix multiplication: error in dimensions\n";
        exit(EXIT_FAILURE);
    }

    Matrix *m_aux = new Matrix(this->n_row, m.n_column);

    for (int i = 1; i <= this->n_row; i++)
    {
        for (int j = 1; j <= m.n_column; j++)
        {
            (*m_aux)(i, j) = 0;
            for (int k = 1; k <= this->n_column; k++)
            {
                (*m_aux)(i, j) += (*this)(i, k) * m(k, j);
            }
        }
    }

    return *m_aux;
}

Matrix &Matrix::operator/(Matrix &m)
{
    if (this->n_row != m.n_row || this->n_column != m.n_column)
    {
        cout << "Matrix division: error in dimensions\n";
        exit(EXIT_FAILURE);
    }

    Matrix m_inv = inv(m);

    return *this * m_inv;
}

Matrix &Matrix::operator=(Matrix &m)
{
    if (this == &m)
        return *this;

    for (int i = 0; i < this->n_row; i++)
    {
        free(this->data[i]);
    }
    free(this->data);

    this->n_row = m.n_row;
    this->n_column = m.n_column;
    this->data = (double **)malloc(this->n_row * sizeof(double *));

    if (this->data == NULL)
    {
        cout << "Matrix assignment: error in data allocation\n";
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < this->n_row; i++)
    {
        this->data[i] = (double *)malloc(this->n_column * sizeof(double));
        if (this->data[i] == NULL)
        {
            cout << "Matrix assignment: error in row allocation\n";
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 1; i <= this->n_row; i++)
    {
        for (int j = 1; j <= this->n_column; j++)
        {
            (*this)(i, j) = m(i, j);
        }
    }

    return *this;
}

Matrix &eye(const int n)
{
    Matrix *m_aux = new Matrix(n, n);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            (*m_aux)(i, j) = (i == j) ? 1 : 0;
        }
    }

    return *m_aux;
}

Matrix &transpose(Matrix &m)
{
    Matrix *m_aux = new Matrix(m.n_column, m.n_row);

    for (int i = 1; i <= m.n_row; i++)
    {
        for (int j = 1; j <= m.n_column; j++)
        {
            (*m_aux)(j, i) = m(i, j);
        }
    }

    return *m_aux;
}

Matrix &inv(Matrix &m)
{
    if (m.n_row != m.n_column)
    {
        cout << "Matrix inverse: matrix must be square\n";
        exit(EXIT_FAILURE);
    }

    // Crear una copia de la matriz
    Matrix *m_aux = new Matrix(m.n_row, m.n_column);
    for (int i = 1; i <= m.n_row; i++)
    {
        for (int j = 1; j <= m.n_column; j++)
        {
            (*m_aux)(i, j) = m(i, j);
        }
    }


    // Crear la matriz identidad
    Matrix I(m.n_row, m.n_column);
    I.eye(m.n_row);

    // Gauss-Jordan
    for (int i = 1; i <= m.n_row; i++)
    {
        double pivot = (*m_aux)(i, i);
        if (fabs(pivot) < 1e-12)
        {
            cout << "Matrix inverse: matrix is singular\n";
            exit(EXIT_FAILURE);
        }

        // Dividir la fila por el pivote
        for (int j = 1; j <= m.n_column; j++)
        {
            (*m_aux)(i, j) /= pivot;
            (*I)(i, j) /= pivot;
        }

        // Hacer cero debajo del pivote
        for (int j = i + 1; j <= m.n_row; j++)
        {
            double factor = (*m_aux)(j, i);
            for (int k = 1; k <= m.n_column; k++)
            {
                (*m_aux)(j, k) -= factor * (*m_aux)(i, k);
                (*I)(j, k) -= factor * (*I)(i, k);
            }
        }
    }

    // Hacer cero encima del pivote
    for (int i = m.n_row; i >= 1; i--)
    {
        for (int j = i - 1; j >= 1; j--)
        {
            double factor = (*m_aux)(j, i);
            for (int k = 1; k <= m.n_column; k++)
            {
                (*m_aux)(j, k) -= factor * (*m_aux)(i, k);
                (*I)(j, k) -= factor * (*I)(i, k);
            }
        }
    }

    return *I;
}

Matrix &Matrix::operator+(double scalar)
{
    Matrix *m_aux = new Matrix(this->n_row, this->n_column);

    for (int i = 1; i <= this->n_row; i++)
    {
        for (int j = 1; j <= this->n_column; j++)
        {
            (*m_aux)(i, j) = (*this)(i, j) + scalar;
        }
    }

    return *m_aux;
}

Matrix &Matrix::operator-(double scalar)
{
    Matrix *m_aux = new Matrix(this->n_row, this->n_column);

    for (int i = 1; i <= this->n_row; i++)
    {
        for (int j = 1; j <= this->n_column; j++)
        {
            (*m_aux)(i, j) = (*this)(i, j) - scalar;
        }
    }

    return *m_aux;
}

Matrix &Matrix::operator*(double scalar)
{
    Matrix *m_aux = new Matrix(this->n_row, this->n_column);

    for (int i = 1; i <= this->n_row; i++)
    {
        for (int j = 1; j <= this->n_column; j++)
        {
            (*m_aux)(i, j) = (*this)(i, j) * scalar;
        }
    }

    return *m_aux;
}

Matrix &Matrix::operator/(double scalar)
{
    if (fabs(scalar) < 1e-12)
    {
        cout << "Matrix division: division by zero error\n";
        exit(EXIT_FAILURE);
    }

    Matrix *m_aux = new Matrix(this->n_row, this->n_column);

    for (int i = 1; i <= this->n_row; i++)
    {
        for (int j = 1; j <= this->n_column; j++)
        {
            (*m_aux)(i, j) = (*this)(i, j) / scalar;
        }
    }

    return *m_aux;
}
