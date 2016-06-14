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

        int blockSize = matrixA->size()/nbBlocks;
        for(int i = 0; i < nbBlocks; i++){
            for (int j = 0; j < nbBlocks; j++){
                SquareMatrix<T>* blockA = new SquareMatrix<T>(blockSize);
                SquareMatrix<T>* blockB = new SquareMatrix<T>(blockSize);

                for (int k = 0; k < blockSize; k++){
                    for (int l = 0; l < blockSize; l++){
                        blockA->setElement(k,l,matrixA->element(k + i,l + j));
                        blockB->setElement(k,l,matrixB->element(k + i,l + j));

                    }
                }
                SquareMatrixWrapper<T>* mat = new SquareMatrixWrapper<T>(blockA, blockB, matrixC, i * blockSize, j * blockSize);
                result->append(mat);
            }
        }

        return result;
    }
};




#endif // THREADEDMATRIXMULTIPLIER_H
