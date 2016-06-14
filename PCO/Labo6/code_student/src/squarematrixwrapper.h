#ifndef SQUAREMATRIXWRAPPER_H
#define SQUAREMATRIXWRAPPER_H

#include "matrix.h"

template <class T>
class SquareMatrixWrapper{
public:
    SquareMatrix<T> *matrixA;
    SquareMatrix<T> *matrixB;
    SquareMatrix<T> *matrixC;
    int x;
    int y;

    SquareMatrixWrapper<T>(SquareMatrix<T> *matrixA, SquareMatrix<T> *matrixB, SquareMatrix<T> *matrixC, int x, int y){
        this->matrixA = matrixA;
        this->matrixB = matrixB;
        this->matrixC = matrixC;
        this->x = x;
        this->y = y;
    }
};

#endif // SQUAREMATRIXWRAPPER_H
