#ifndef SQUAREMATRIXWRAPPER_H
#define SQUAREMATRIXWRAPPER_H

#include "matrix.h"
#include "barriere.h"

template <class T>
class SquareMatrixWrapper{
public:
    SquareMatrix<T> *matrixA;
    SquareMatrix<T> *matrixB;
    SquareMatrix<T> *matrixC;
    int xBegin;
    int yBegin;
    int xEnd;
    int yEnd;
    Barriere *barriere;

    SquareMatrixWrapper<T>(SquareMatrix<T> *matrixA, SquareMatrix<T> *matrixB, SquareMatrix<T> *matrixC, int xBegin, int yBegin, int xEnd, int yEnd, Barriere *barriere){
        this->matrixA = matrixA;
        this->matrixB = matrixB;
        this->matrixC = matrixC;
        this->xBegin = xBegin;
        this->yBegin = yBegin;
        this->xEnd = xEnd;
        this->yEnd = yEnd;
        this->barriere = barriere;
    }
};

#endif // SQUAREMATRIXWRAPPER_H
