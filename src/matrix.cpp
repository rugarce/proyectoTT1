#include "..\include\matrix.hpp"

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

Matrix &zeros(const int n)
{
    Matrix *m_aux = new Matrix(n);

    for (int i = 1; i <= n; i++)
    {
        (*m_aux)(1, i) = 0;
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

Matrix inv(Matrix &m)
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
    Matrix I = eye(m.n_row);

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
            (I)(i, j) /= pivot;
        }

        // Hacer cero debajo del pivote
        for (int j = i + 1; j <= m.n_row; j++)
        {
            double factor = (*m_aux)(j, i);
            for (int k = 1; k <= m.n_column; k++)
            {
                (*m_aux)(j, k) -= factor * (*m_aux)(i, k);
                (I)(j, k) -= factor * (I)(i, k);
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
                (I)(j, k) -= factor * (I)(i, k);
            }
        }
    }

    return I;
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

double norm(Matrix &v)
{
    if (v.n_row != 1)
    {
        cout << "Norm: input is not a vector\n";
        exit(EXIT_FAILURE);
    }

    double sum = 0.0;
    for (int i = 1; i <= v.n_column; i++)
    {
        sum += v(i) * v(i);
    }

    return sqrt(sum);
}

double dot(Matrix &a, Matrix &b)
{
    if (a.n_row != 1 || b.n_row != 1 || a.n_column != b.n_column)
    {
        cout << "Dot: vectors incompatible\n";
        exit(EXIT_FAILURE);
    }

    double sum = 0.0;
    for (int i = 1; i <= a.n_column; i++)
    {
        sum += a(i) * b(i);
    }

    return sum;
}

Matrix &cross(Matrix &a, Matrix &b)
{
    if (a.n_row != 1 || b.n_row != 1 || a.n_column != 3 || b.n_column != 3)
    {
        cout << "Cross: only defined for 3D vectors\n";
        exit(EXIT_FAILURE);
    }

    Matrix *m_aux = new Matrix(3);

    (*m_aux)(1) = a(2) * b(3) - a(3) * b(2);
    (*m_aux)(2) = a(3) * b(1) - a(1) * b(3);
    (*m_aux)(3) = a(1) * b(2) - a(2) * b(1);

    return *m_aux;
}

Matrix& extract_vector(Matrix &m, const int n, const int k)
{
    if (m.n_row != 1 || n < 1 || k > m.n_column || n > k) 
    {
        cout << "extract_vector: Invalid indices\n";
        exit(EXIT_FAILURE);
    }

    Matrix *vector = new Matrix(k - n + 1);

    for (int i = n; i <= k; i++)
    {
        (*vector)(i - n + 1) = m(i);
    }

    return *vector;
}

Matrix& extract_row(Matrix &m, const int n)
{
    if (n < 1 || n > m.n_row)
    {
        cout << "extract_row: Invalid row index\n";
        exit(EXIT_FAILURE);
    }

    Matrix *row = new Matrix(m.n_column);

    // Copiar la fila
    for (int j = 1; j <= m.n_column; j++)
    {
        (*row)(j) = m(n, j);
    }

    return *row;
}

Matrix& extract_column(Matrix &m, const int n)
{
    if (n < 1 || n > m.n_column)
    {
        cout << "extract_column: Invalid column index\n";
        exit(EXIT_FAILURE);
    }

    Matrix *column = new Matrix(m.n_row);

    for (int i = 1; i <= m.n_row; i++)
    {
        (*column)(i) = m(i, n);
    }

    return *column;
}

Matrix& union_vector(Matrix &m, Matrix &k)
{
    if (m.n_row != 1 || k.n_row != 1)
    {
        cout << "union_vector: Both matrices must be row vectors\n";
        exit(EXIT_FAILURE);
    }

    Matrix *result = new Matrix(m.n_column + k.n_column);

    for (int i = 1; i <= m.n_column; i++)
    {
        (*result)(i) = m(i);
    }

    for (int i = 1; i <= k.n_column; i++)
    {
        (*result)(m.n_column + i) = k(i);
    }

    return *result;
}

Matrix& assign_column(Matrix &m, Matrix &k, const int n)
{
    if (k.n_column != m.n_row || k.n_row != 1)
    {
        cout << "assign_column: The input must be a column vector\n";
        exit(EXIT_FAILURE);
    }

    if (n < 1 || n > m.n_column)
    {
        cout << "assign_column: Invalid column index\n";
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= m.n_row; i++)
    {
        m(i, n) = k(i);
    }

    return m;
}

Matrix& assign_row(Matrix &m, Matrix &k, const int n)
{
    if (k.n_column != m.n_column || k.n_row != 1)
    {
        cout << "assign_row: The input must be a row vector\n";
        exit(EXIT_FAILURE);
    }

    if (n < 1 || n > m.n_row)
    {
        cout << "assign_row: Invalid row index\n";
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= m.n_column; i++)
    {
        m(n, i) = k(i);
    }

    return m;
}



