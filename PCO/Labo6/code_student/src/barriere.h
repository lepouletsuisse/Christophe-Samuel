#ifndef BARRIERE_H
#define BARRIERE_H

#include <QMutex>
#include <QWaitCondition>

class Barriere{
private:
    QMutex *mutex;
    QWaitCondition *wait;
    int nbDone;
    int limite;

public:
    Barriere(int limite){
        mutex = new QMutex();
        wait = new QWaitCondition();
        nbDone = 0;
        this->limite = limite;
    }

    void await(){
        mutex->lock();
        std::cout << "Waiting..." << std::endl;
        wait->wait(mutex);
        mutex->unlock();
    }

    void done(){
        mutex->lock();
        nbDone++;
        if(nbDone >= limite){
            wait->wakeAll();
            std::cout << "All work done!" << std::endl;
        }
        mutex->unlock();
    }
};


#endif // BARRIERE_H
