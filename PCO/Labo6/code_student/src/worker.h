#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QSemaphore>
#include <QVector>
#include <QMutex>
#include <QWaitCondition>

#include "squarematrixwrapper.h"

template <class T>
class Worker : public QThread{
private:
    bool isNewlySet;
    QMutex lock;
    QWaitCondition wait;
    SquareMatrixWrapper<T> matrix;
    void run(){
        lock.lock();
        while(true){
            if(isNewlySet){
                //Caluler la matrix
                for(int i=0;i<matrix.matrixA->size();i++) {
                    for(int j=0;j<matrix.matrixA->size();j++) {
                        for(int k=0;k<matrix.matrixA->size();k++) {
                            matrix.matrixC->setElement(i,j, matrix.matrixC->element(i,j) + matrix.matrixA->element(k,j)*matrix.matrixB->element(i,k));
                        }
                    }
                }
                matrix.done = true;
                isNewlySet = false;
            }
            wait.wait(&lock);
        }
        lock.unlock();
    }
public:
    Woker(){
        isNewlySet = false;
    }

    bool giveMatrix(SquareMatrixWrapper<T> matrix){
        lock.lock();
        if(!isNewlySet){
            this->matrix = matrix;
            isNewlySet = true;
            wait.wakeOne();
            lock.unlock();
            return true;
        }
        lock.unlock();
        return false;
    }
};

#endif // WORKER_H
