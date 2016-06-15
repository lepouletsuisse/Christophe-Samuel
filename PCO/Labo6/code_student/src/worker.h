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
    int id;
    WorkerManager<T> *manager;
    SquareMatrixWrapper<T> *currentMatrix;
    void run(){
        while(true){
            //Caluler la matrix
            currentMatrix = manager->getMatrix();
            std::cout << id << ": Working from " << currentMatrix->xBegin << "," << currentMatrix->yBegin << " to " << currentMatrix->xEnd << "," << currentMatrix->yEnd << std::endl;
            for(int i=currentMatrix->xBegin;i<currentMatrix->xEnd;i++) {
                for(int j=currentMatrix->yBegin;j<currentMatrix->yEnd;j++) {
                    for(int k=0;k<currentMatrix->matrixA->size();k++) {
                        currentMatrix->matrixC->setElement(i,j, currentMatrix->matrixC->element(i,j) + currentMatrix->matrixA->element(k,j)*currentMatrix->matrixB->element(i,k));
                    }
                }
            }
            currentMatrix->barriere->done();
        }
    }
public:
    Worker(WorkerManager<T> *manager, int id){
        this->manager = manager;
        this->id = id;
    }
};

#endif // WORKER_H
