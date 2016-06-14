#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QSemaphore>
#include <QList>
#include <QMutex>
#include <QWaitCondition>

#include "squarematrixwrapper.h"
#include "workermanager.h"

template <class T>
class Worker : public QThread{
private:
    WorkerManager<T> *manager;
    SquareMatrixWrapper<T> *currentMatrix;
    void run(){
        while(true){
            //Caluler la matrix
            currentMatrix = manager->getMatrix();
            for(int i=0;i<currentMatrix->matrixA->size();i++) {
                for(int j=0;j<currentMatrix->matrixA->size();j++) {
                    for(int k=0;k<currentMatrix->matrixA->size();k++) {
                        currentMatrix->matrixC->setElement(i,j, currentMatrix->matrixC->element(i,j) + currentMatrix->matrixA->element(k,j)*currentMatrix->matrixB->element(i,k));
                    }
                }
            }
        }
    }
public:
    Worker(WorkerManager<T> *manager){
        this->manager = manager;
    }
};

#endif // WORKER_H
