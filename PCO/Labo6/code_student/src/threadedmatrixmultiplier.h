#ifndef THREADEDMATRIXMULTIPLIER_H
#define THREADEDMATRIXMULTIPLIER_H

#include <QThread>
#include <QSemaphore>
#include <QList>
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
        manager = new WorkerManager<T>();
        for(int i = 0 ; i < nbThreads ; i++){
            Worker<T> *worker = new Worker<T>(manager);
            listWorker.append(worker);
            worker->start();
        }
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
        QList< SquareMatrixWrapper<T>* > *listMatrix = cutMatrix(&A, &B, C, nbBlocks);
        for(SquareMatrixWrapper<T> *matrix: *listMatrix){
            manager->addMatrix(matrix);
        }
    }

protected:
    int nbThreads;
    int nbBlocksPerRow;
    QList< Worker<T>* > listWorker;
    WorkerManager<T>* manager;

    QList< SquareMatrixWrapper<T>* > *cutMatrix(SquareMatrix<T> *matrixA, SquareMatrix<T> *matrixB, SquareMatrix<T> *matrixC, int nbBlocks){
        QList< SquareMatrixWrapper<T>* > *result = new QList< SquareMatrixWrapper<T>* >();

        for(int i = 0; i < nbBlocks; i++){
            for (int j = 0; j < nbblocks; j++){
                blockA = new SquareMatrix<T>();
                blockB = new SquareMatrix<T>();
                blockC = new SquareMatrix<T>();

            }
        }
        //Cut the matrix here

        return result;
    }
};




#endif // THREADEDMATRIXMULTIPLIER_H
