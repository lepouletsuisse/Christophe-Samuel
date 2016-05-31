#ifndef MULTIPLIERTESTER_H
#define MULTIPLIERTESTER_H

#include <iostream>
#include <QTime>

#include "matrix.h"
#include "simplematrixmultiplier.h"
#include "threadedmatrixmultiplier.h"



/**
 * This class implements a tester for the multiplier. It calls a simple
 * implementation of multiply and the multi-threaded one, compares the
 * result, and the time spent by both implementation.
 */
template<class T>
class MultiplierTester
{
public:

    MultiplierTester() {}

    void test(int matrixSize,int nbThreads, int nbBlocksPerRow)
    {

        SquareMatrix<T> A(matrixSize);
        SquareMatrix<T> B(matrixSize);
        SquareMatrix<T> C(matrixSize);
        SquareMatrix<T> C_ref(matrixSize);

        for(int i=0;i<matrixSize;i++) {
            for(int j=0;j<matrixSize;j++) {
                A.setElement(i,j,rand());
                B.setElement(i,j,rand());
                C.setElement(i,j,0);
                C_ref.setElement(i,j,0);
            }
        }

        SimpleMatrixMultiplier<T> multiplier;
        QTime t;
        t.start();
        multiplier.multiply(A,B,&C_ref);
        int timeSimple = t.elapsed();

        ThreadedMatrixMultiplier<T> threadedMultiplier(nbThreads, nbBlocksPerRow);
        t.start();
        threadedMultiplier.multiply(A,B,&C);
        int timeThreaded = t.elapsed();

        C.compare(C_ref);

        if (timeThreaded == 0) {
            std::cout << "Time too short, try with a bigger matrix size" << std::endl;
        }
        else {
            double gain = ((double) timeSimple) / ((double) timeThreaded) * 100.0 - 100.0;
            std::cout << "Time gain: " << gain << " % " << std::endl;
        }
    }
};

#endif // MULTIPLIERTESTER_H
