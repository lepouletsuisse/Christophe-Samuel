#include "barrieresynchronisation.h"

#include <QMutex>
#include <QWaitCondition>

class BarriereSynchronisation{
public:
    BarriereSynchronisation(int limite){
        lock = new QMutex();
        nbDone = 0;
        this->limite = limite;
    }

    void lock(){
        lock->lock();
        wait.wait(lock);
        lock->unlock();
    }

    void done(){
        lock->lock();
        nbDone++;
        if(nbDone >= limite){
            wait.wakeAll();
        }
        lock->unlock();
    }
private:
    QMutex *lock;
    QWaitCondition wait;
    int nbDone;
    int limite;
}
