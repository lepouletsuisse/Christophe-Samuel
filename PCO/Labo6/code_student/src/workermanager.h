#ifndef WORKERMANAGER_H
#define WORKERMANAGER_H

#include "hoaremonitor.h"
#include "worker.h"

template<class T>
class WorkerManager : public HoareMonitor{
private:
    QList< SquareMatrixWrapper<T>* > *listMatrix;
    Condition condition;
public:
    WorkerManager() : HoareMonitor(){
        listMatrix = new QList< SquareMatrixWrapper<T>* >();
    }

    void addMatrix(SquareMatrixWrapper<T>* matrix){
        listMatrix->append(matrix);
        this->signal(condition);
    }

    SquareMatrixWrapper<T>* getMatrix(){
        monitorIn();
        while(listMatrix->size() <= 0){
            this->wait(condition);
        }
        SquareMatrixWrapper<T>* result = listMatrix->front();
        listMatrix->pop_front();
        monitorOut();
        return result;
    }
};


#endif // WORKERMANAGER_H
