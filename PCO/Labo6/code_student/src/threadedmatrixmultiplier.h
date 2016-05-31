#ifndef THREADEDMATRIXMULTIPLIER_H
#define THREADEDMATRIXMULTIPLIER_H

#include <QThread>
#include <QSemaphore>
#include <QVector>
#include <QMutex>

#include "hoaremonitor.h"
#include "matrix.h"
#include "abstractmatrixmultiplier.h"


/**
 * A multi-threaded multiplicator to be implemented.
 */
template <class T>
class ThreadedMatrixMultiplier : public AbstractMatrixMultiplier<T>
{

public:
    ThreadedMatrixMultiplier(int nbThreads, int nbBlocksPerRow = 0) : nbThreads(nbThreads), nbBlocksPerRow(nbBlocksPerRow)
    {
    }

    ~ThreadedMatrixMultiplier()
    {
    }

    void multiply( SquareMatrix<T> &A,  SquareMatrix<T> &B, SquareMatrix<T> *C)
    {
        multiply(A, B, C, 0);
    }

    void multiply( SquareMatrix<T> &A,  SquareMatrix<T> &B, SquareMatrix<T> *C, int nbBlocks)
    {
        for(int i=0;i<A.size();i++) {
            for(int j=0;j<A.size();j++) {
                for(int k=0;k<A.size();k++) {
                    C->setElement(i,j, C->element(i,j) + A.element(k,j)*B.element(i,k));
                }
            }
        }
    }

protected:
    int nbThreads;
    int nbBlocksPerRow;
};




#endif // THREADEDMATRIXMULTIPLIER_H
