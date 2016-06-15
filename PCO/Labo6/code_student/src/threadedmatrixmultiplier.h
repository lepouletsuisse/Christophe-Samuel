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
        std::cout << "NbThread: " << nbThreads << " // nbBlocksPerRow: " << nbBlocksPerRow << std::endl;
        manager = new WorkerManager<T>();
        for(int i = 0 ; i < nbThreads ; i++){
            Worker<T> *worker = new Worker<T>(manager, i);
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
        if(nbBlocks == 0){
            nbBlocks = nbBlocksPerRow * nbBlocksPerRow;
        }
        std::cout << "nbBlocks: " << nbBlocks << std::endl;
        Barriere *barriere = new Barriere(nbBlocks);
        QList< SquareMatrixWrapper<T>* > *listMatrix = cutMatrix(&A, &B, C, nbBlocks, barriere);
        for(SquareMatrixWrapper<T> *matrix: *listMatrix){
            manager->addMatrix(matrix);
        }
        barriere->await();
    }

protected:
    int nbThreads;
    int nbBlocksPerRow;
    QList< Worker<T>* > listWorker;
    WorkerManager<T>* manager;

    QList< SquareMatrixWrapper<T>* > *cutMatrix(SquareMatrix<T> *matrixA, SquareMatrix<T> *matrixB, SquareMatrix<T> *matrixC, int nbBlocks, Barriere *barriere){
        QList< SquareMatrixWrapper<T>* > *result = new QList< SquareMatrixWrapper<T>* >();

        int blockSize = matrixA->size()/nbBlocksPerRow;
        for(int i = 0; i < nbBlocksPerRow; i++){
            for (int j = 0; j < nbBlocksPerRow; j++){
                SquareMatrixWrapper<T>* mat = new SquareMatrixWrapper<T>(matrixA, matrixB, matrixC, i * blockSize, j * blockSize, i * blockSize + blockSize, j * blockSize + blockSize, barriere);
                result->append(mat);
            }
        }
        return result;
    }
};




#endif // THREADEDMATRIXMULTIPLIER_H
