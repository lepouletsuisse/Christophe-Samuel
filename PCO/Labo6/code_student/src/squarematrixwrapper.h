#ifndef SQUAREMATRIXWRAPPER_H
#define SQUAREMATRIXWRAPPER_H

#include "matrix.h"

template <class T>
class SquareMatrixWrapper{
public:
    int id;
    SquareMatrix<T>* matrixA;
    SquareMatrix<T>* matrixB;
    SquareMatrix<T>* matrixC;
    bool done;
    int x;
    int y;
    int blocSize;

    SquareMatrixWrapper<T>(int id, SquareMatrixWrapper<T>* matrixA, SquareMatrix<T>* matrixB, int x, int y, int blocSize){
        this->id = id;
        this->matrixA = matrixA;
        this->matrixB = matrixB;
        this->matrixC = new SquareMatrix<T>();
        this->x = x;
        this->y = y;
        this->blocSize = blocSize;
        this->done = false;
    }
};

#endif // SQUAREMATRIXWRAPPER_H
