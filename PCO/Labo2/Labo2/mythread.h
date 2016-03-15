/* PCO Labo2
 * Samuel Darcey & Christophe Peretti
 * 14.03.16
 *
 */

#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <math.h>
#include <cstdint> // include this header for uint64_t
#include <QThread>
#include "utils.h"


/* Classe permettant de créer un thread qui va déterminer si un nombre est premier ou non.
 * Le constructeur a besoin des bornes inférieures et supérieures du parcours, ainsi que le nombre à tester.
 * Dès qu'un thread a trouvé un diviseur, il informe les autres qu'ils peuvent arrêter les calculs.
 *
 */
class MyThread : public QThread{
private:
    uint64_t debut;
    uint64_t fin;
    uint64_t number;
    virtual void run() Q_DECL_OVERRIDE{
        for(uint64_t i = debut ; i < fin ; i++){

            // Chaque thread vérifie si le nombre a été trouvé comme non-premier
            if (!prime) break;
            if(!(number % i)){
                prime = false;
            }
        }
    }

public:
    MyThread(uint64_t debut, uint64_t fin, uint64_t number): QThread(), debut(debut), fin(fin), number(number){}
};

#endif // MYTHREAD_H
