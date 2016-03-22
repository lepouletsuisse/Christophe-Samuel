#include <QString>
#include <QThread>
#include <cmath>
#include <QTimer>
#include <QSemaphore>


#include "bmmanager.h"
#include "banditmanchot_interface.h"
#include <sstream>

const int nbThread = 3;
const int incrJackpot = 5;
int pressedStop = nbThread;
int jackpotValue = 100;
bool finished = true;
QTimer* timer;


// En microsecondes
#define DelaiLocal  4000000

class RouleauThread : public QThread
{
private:
    int numRouleau;
    QSemaphore sem;
    bool running = true;
    bool valeurSet = false;
    int valeur = 0;

public:
    RouleauThread(int num) : sem(0){
        numRouleau = num;
    }

    void run() Q_DECL_OVERRIDE {
        setValeurRouleau(numRouleau,valeur);
        while(!isInterruptionRequested()){
            sem.acquire();
            valeurSet = false;
            while(running){
                usleep(10000);
                valeur = (valeur + 1) % 10;
                setValeurRouleau(numRouleau,valeur);
            }
            valeurSet = true;
        }

    }

    void requestStop(){
        running = false;
    }

    void requestStart(){
        running = true;
        sem.release();
    }

    int getValeur(){
        return valeur;
    }

    bool canRead(){
        return valeurSet;
    }
};

RouleauThread* thread[nbThread];

void BmManager::start()
{
    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [&](){
        boutonStop();
    });
    setJackpot(jackpotValue);
    for(int i = 0 ; i < nbThread ; i++){
        thread[i] = new RouleauThread(i);
        thread[i]->start();
    }

}

void BmManager::end()
{
    for(int i = 0 ; i < nbThread ; i++){
        thread[i]->requestInterruption();
    }
}

void BmManager::pieceIntroduite()
{
    if(pressedStop == nbThread){
        pressedStop = 0;
        finished = false;
        setMessage("");
        jackpotValue += incrJackpot;
        setJackpot(jackpotValue);
        for(int i = 0 ; i < nbThread ; i++){
            thread[i]->requestStart();
        }
        timer->start(DelaiLocal / 1000);
    }
}

void BmManager::boutonStop()
{
    if(!finished) timer->stop();
    if(pressedStop < nbThread){
        thread[pressedStop++]->requestStop();
        timer->start(DelaiLocal / 1000);
    }
    if(pressedStop == nbThread && !finished){
        std::stringstream stream;
        while(!thread[0]->canRead() || !thread[1]->canRead() || !thread[2]->canRead());
        if(thread[0]->getValeur() == thread[1]->getValeur() && thread[0]->getValeur() == thread[2]->getValeur()){
            stream << "You have won half the jackpot! this is " << ceil(jackpotValue / 2) << "!" << std::endl;
            jackpotValue -= ceil(jackpotValue / 2);
            setJackpot(jackpotValue);
            finished = true;
        }
        else if(thread[0]->getValeur() == thread[1]->getValeur() || thread[0]->getValeur() == thread[2]->getValeur() || thread[1]->getValeur() == thread[2]->getValeur()){
            stream << "You have won a quarter of the jackpot! this is " << ceil(jackpotValue / 4) << "!" << std::endl;
            jackpotValue -= ceil(jackpotValue / 4);
            setJackpot(jackpotValue);
            finished = true;
        }
        else{
            stream << "You have won nothing!!! Try again :)" << std::endl;
            finished = true;
        }
        setMessage(QString(stream.str().c_str()));
    }
}

