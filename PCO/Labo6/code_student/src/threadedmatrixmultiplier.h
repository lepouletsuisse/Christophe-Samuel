#ifndef THREADEDMATRIXMULTIPLIER_H
#define THREADEDMATRIXMULTIPLIER_H

#include <QThread>
#include <QSemaphore>
#include <QVector>
#include <QMutex>

#include "squarematrixwrapper.h"
#include "hoaremonitor.h"
#include "matrix.h"
#include "abstractmatrixmultiplier.h"
#include "worker.h"


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
    }

protected:
    int nbThreads;
    int nbBlocksPerRow;
    QVector< SquareMatrixWrapper<T> > listMatrix;
    QVector< Worker<T> > listWorker;
};




#endif // THREADEDMATRIXMULTIPLIER_H
