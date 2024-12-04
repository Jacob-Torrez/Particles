#include "Matrices.h"

namespace Matrices{

    Matrix::Matrix(int _rows, int _cols){
        rows = _rows;
        cols = _cols;
        a.resize(rows, vector<double>(cols, 0));
    }

    Matrix operator+(const Matrix& a, const Matrix& b){
        Matrix c(a.getRows(), a.getCols());
        
        if ((a.getRows() == b.getRows()) && (a.getCols() == b.getCols())){
            for (int i = 0; i < a.getRows(); i++){
                for (int j = 0; j < a.getCols(); j++){
                    c(i, j) = a(i, j) + b(i, j);
                }
            }
        }
        else{
            throw runtime_error("Error: dimensions must agree");
        }

        return c;
    }

    Matrix operator*(const Matrix& a, const Matrix& b){
        Matrix c(a.getRows(), b.getCols());
        if (a.getCols() != b.getRows()){
            throw runtime_error("Error: dimensions must agree");
        }
        else{
            for (int k = 0; k < b.getCols(); k++){
                for (int i = 0; i < a.getRows(); i++){
                    double sum = 0;
                    for (int j = 0; j < a.getCols(); j++){
                        sum += a(i, j) * b(j, k);
                    }
                    c(i, k) = sum;
                }
            }
        }

        return c;
    }

    bool operator==(const Matrix& a, const Matrix& b){
        bool equal = true;

        if (a.getRows() != b.getRows() || a.getCols() != b.getCols()){
            equal = false;
        }
        else{
            for (int i = 0; i < a.getRows() && equal; i++){
                for (int j = 0; j < a.getCols() && equal; j++){
                    if (abs(a(i, j) - b(i, j)) > 0.001){
                        equal = false;
                    }
                }
            }
        }

        return equal;
    }

    bool operator!=(const Matrix& a, const Matrix& b){
        return !(a == b);
    }

    ostream& operator<<(ostream& os, const Matrix& a){
        for (int i = 0; i < a.getRows(); i++){
            for (int j = 0; j < a.getCols(); j++){
                os << setw(10) << a(i, j) << " ";
            }
            os << endl;
        }

        return os;
    }

    RotationMatrix::RotationMatrix(double theta) : Matrix(2,2){
        (*this)(0, 0) = cos(theta);
        (*this)(0, 1) = -sin(theta);
        (*this)(1, 0) = sin(theta);
        (*this)(1, 1) = cos(theta);
    }

    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2,2){
        (*this)(0, 0) = scale;
        (*this)(0, 1) = 0;
        (*this)(1, 0) = 0;
        (*this)(1, 1) = scale;
    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols){
        for (int j = 0; j < nCols; j++){
            (*this)(0, j) = xShift;
            (*this)(1, j) = yShift;
        }
    }
}