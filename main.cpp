#include <iostream>
#include <valarray>
#include <ctime>

using namespace std;

template<typename T>
class Matrix
{
    std::valarray<T> matrix;
    size_t rows;
    size_t cols;
public:
    Matrix(size_t numrows, size_t numcols) :
        matrix(numrows * numcols), rows(numrows), cols(numcols)
    {
        size_t ind;
        bool boolrnd;
        for (size_t i = 0; i < numrows; i++)
        {
            for (size_t j = 0; j < numcols; j++)
            {
                ind = i * numcols + j;
                boolrnd = ((rand() % 2) == 1);
                matrix[ind] = boolrnd;
            }
        }
    }

    T operator()(size_t row, size_t col) const
    {
        size_t ind = row + cols * col;
        return matrix[ind];
    }

    T& operator()(size_t row, size_t col)
    {
        size_t ind = row + cols * col;
        return matrix[ind];
    }

    Matrix& operator+=(const Matrix& other)
    {
        matrix += other.matrix;
        return *this;
    }

    Matrix& operator-=(const Matrix& other)
    {
        matrix -= other.matrix;
        return *this;
    }

    Matrix& operator*=(const Matrix& other)
    {
        matrix *= other.matrix;
        return *this;
    }

    Matrix& operator^=(const Matrix& other)
    {
        matrix ^= other.matrix;
        return *this;
    }

    Matrix& operator!(void)
    {
        matrix = !matrix;
        return *this;
    }

    size_t getRows(void) const
    {
        return rows;
    }

    size_t getcols(void) const
    {
        return cols;
    }

    friend ostream & operator<<(ostream & out, const Matrix & in)
    {
        for (size_t i = 0; i < in.getRows(); i++)
        {
            for (size_t j = 0; j < in.getcols(); j++)
            {
                out << in(i, j) << ' ';
            }
            out << endl;
        }
        return out;
    }
};

template<typename T>
Matrix<T> operator+(Matrix<T> lhs, const Matrix<T>& rhs)
{
    lhs += rhs;
    return lhs;
}

template<typename T>
Matrix<T> operator-(Matrix<T> lhs, const Matrix<T>& rhs)
{
    lhs -= rhs;
    return lhs;
}

template<typename T>
Matrix<T> operator*(Matrix<T> lhs, const Matrix<T>& rhs)
{
    lhs *= rhs;
    return lhs;
}

template<typename T>
Matrix<T> operator^(Matrix<T> lhs, const Matrix<T>& rhs)
{
    lhs ^= rhs;
    return lhs;
}

int main(void)
{
    size_t m = 10;
    size_t n = 10;

    Matrix<bool> matrix1(m, n);
    Matrix<bool> matrix2(m, n);
    Matrix<bool> mataddi(m, n);
    Matrix<bool> matsubt(m, n);
    Matrix<bool> matmuli(m, n);
    Matrix<bool> matXOR(m, n);
    Matrix<bool> matXNOR(m, n);

    mataddi = matrix1 + matrix2;
    matsubt = matrix1 - matrix2;
    matmuli = matrix1 * matrix2;
    matXOR = matrix1 ^ matrix2;
    matXNOR = !matXOR;

    cout << "first 10*10 boolean matrix" << endl;
    cout << matrix1 << endl;
    cout << "second 10*10 boolean matrix" << endl;
    cout << matrix2 << endl;
    cout << "coordinate-wise addition of these two matrices" << endl;
    cout << mataddi << endl;
    cout << "coordinate-wise subtraction of these two matrices" << endl;
    cout << matsubt << endl;
    cout << "coordinate-wise multiplication of these two matrices" << endl;
    cout << matmuli << endl;
    cout << "coordinate-wise XNOR of these two matrices" << endl;
    cout << matXNOR << endl;

    system("pause");

    return 0;
}
