#ifndef SQUAREMATRIXWRAPPER_H
#define SQUAREMATRIXWRAPPER_H

#include "matrix.h"

template <class T>
class SquareMatrixWrapper{
public:
    SquareMatrix<T> *matrixA;
    SquareMatrix<T> *matrixB;
    SquareMatrix<T> *matrixC;

    SquareMatrixWrapper<T>(SquareMatrixWrapper<T> *matrixA, SquareMatrix<T> *matrixB, SquareMatrix<T> *matrixC){
        this->matrixA = matrixA;
        this->matrixB = matrixB;
        this->matrixC = matrixC;
    }
};

#endif // SQUAREMATRIXWRAPPER_H
