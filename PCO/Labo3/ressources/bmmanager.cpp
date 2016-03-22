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
    //running is use to setermine if the thread has to run or not
    bool running = true;
    //valeurSet is used to determine if the value has already been set
    bool valeurSet = false;
    //valeur is the value of the current thread
    int valeur = 0;

public:
    RouleauThread(int num) : sem(0){
        numRouleau = num;
    }

    void run() Q_DECL_OVERRIDE {
        setValeurRouleau(numRouleau,valeur);
        //Exit the big loop if requested
        while(!isInterruptionRequested()){
            //Stop at the beggining
            sem.acquire();
            valeurSet = false;
            //Inner loop determine if the thread is currently running (But not if it has been stopped)
            while(running){
                usleep(10000);
                valeur = (valeur + 1) % 10;
                setValeurRouleau(numRouleau,valeur);
            }
            valeurSet = true;
        }

    }

    //Request the thread to stop
    void requestStop(){
        running = false;
    }

    //Request the thread to start
    void requestStart(){
        running = true;
        sem.release();
    }

    int getValeur(){
        return valeur;
    }

    //Determine if the principal thread can read the value
    bool canRead(){
        return valeurSet;
    }
};

RouleauThread* thread[nbThread];

void BmManager::start()
{
    //Create a timer and when it overflow, it will simply press the stop button
    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [&](){
        boutonStop();
    });
    setJackpot(jackpotValue);
    //Create the threads
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
    //The new game button can only be pressed if all the thread has been stopped
    if(pressedStop == nbThread){
        pressedStop = 0;
        finished = false;
        setMessage("");
        //Each time you start a new game, you increase the jackpot
        jackpotValue += incrJackpot;
        setJackpot(jackpotValue);
        //Restart all the threads
        for(int i = 0 ; i < nbThread ; i++){
            thread[i]->requestStart();
        }
        //Restart the timer
        timer->start(DelaiLocal / 1000);
    }
}

void BmManager::boutonStop()
{
    //if the game has been finished, stop the timer
    if(!finished) timer->stop();

    //We can only pressed the button if not all the threads are done
    if(pressedStop < nbThread){
        thread[pressedStop++]->requestStop();
        timer->start(DelaiLocal / 1000);
    }
    //If all threads are done, get the value of each thread and determine if we won something
    if(pressedStop == nbThread && !finished){
        std::stringstream stream;
        //Start the read of the value only when all the threads has setted there values
        while(!thread[0]->canRead() || !thread[1]->canRead() || !thread[2]->canRead());
        //3 matches
        if(thread[0]->getValeur() == thread[1]->getValeur() && thread[0]->getValeur() == thread[2]->getValeur()){
            stream << "You have won half the jackpot! this is " << ceil(jackpotValue / 2) << "!" << std::endl;
            jackpotValue -= ceil(jackpotValue / 2);
            setJackpot(jackpotValue);
            finished = true;
        }
        //2 matches
        else if(thread[0]->getValeur() == thread[1]->getValeur() || thread[0]->getValeur() == thread[2]->getValeur() || thread[1]->getValeur() == thread[2]->getValeur()){
            stream << "You have won a quarter of the jackpot! this is " << ceil(jackpotValue / 4) << "!" << std::endl;
            jackpotValue -= ceil(jackpotValue / 4);
            setJackpot(jackpotValue);
            finished = true;
        }
        //No matches
        else{
            stream << "You have won nothing!!! Try again :)" << std::endl;
            finished = true;
        }
        setMessage(QString(stream.str().c_str()));
    }
}

