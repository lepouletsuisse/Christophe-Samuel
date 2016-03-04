#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <math.h>
#include <cstdint> // include this header for uint64_t
#include <QThread>

bool notPrime = false;

class MyThread : public QThread{
private:
    uint64_t debut;
    uint64_t fin;
    uint64_t number;
    virtual void run() Q_DECL_OVERRIDE{
        for(int i = debut ; i < fin ; i++){
            if(notPrime) break;
            if(!(number % i)){
                notPrime = true;
            }
        }
    }

public:
    MyThread(uint64_t debut, uint64_t fin, uint64_t number): QThread(), debut(debut), fin(fin), number(number){}
};

#endif // MYTHREAD_H
