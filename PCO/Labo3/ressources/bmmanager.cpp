#include <QString>
#include <QThread>


#include "bmmanager.h"
#include "banditmanchot_interface.h"



// En microsecondes
#define DelaiLocal  4000000

class RouleauThread : public QThread
{
public:
    void run() Q_DECL_OVERRIDE {
        int valeur;
        valeur = 0;
        setValeurRouleau(0,valeur);
        for(;;){
            usleep(10000);
            valeur = (valeur + 1) % 10;
            setValeurRouleau(0,valeur);
        }
    }
};

RouleauThread thread;

void BmManager::start()
{
    thread.start();
}

void BmManager::end()
{
    thread.terminate();
}

void BmManager::pieceIntroduite()
{
}

void BmManager::boutonStop()
{
}

