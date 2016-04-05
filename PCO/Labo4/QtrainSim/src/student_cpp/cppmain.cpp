#include "ctrain_handler.h"
#include "locomotive.h"

#include <QThread>
#include <QList>
#include <QPair>
#include <QSemaphore>
#include <QMutex>

class LocomotiveThread : public QThread{
private:
    Locomotive* locomotive;
    QList<int> parcours;
    QSemaphore* sem;
public:

    //Initialisation de la locomotive
    LocomotiveThread(int id, int vitesse, QPair<int, int> departCapteur, bool phare, QList<int> parc, QSemaphore* s){
        sem = s;
        locomotive = new Locomotive();
        locomotive->fixerNumero(id);
        locomotive->fixerVitesse(vitesse);
        locomotive->fixerPosition(departCapteur.first, departCapteur.second);
        if(phare) locomotive->allumerPhares();
        parcours = parc;
        locomotive->afficherMessage("Ready!");
    }

    void depart(){
        locomotive->demarrer();
    }
    void arreter(){
        locomotive->arreter();
        locomotive->afficherMessage(QString("Yeah, piece of cake for locomotive %1 !").arg(locomotive->numero()));
    }

    void run() Q_DECL_OVERRIDE{
        depart();

        //Attente du passage sur les contacts
        int i = 0;
        while(true){
            attendre_contact(parcours.at(i));
            afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.")
                                        .arg(locomotive->numero()).arg(parcours.at(i))));
            locomotive->afficherMessage(QString("I've reached contact no. %1.").arg(parcours.at(i)));
            if(parcours.at(i) == 3){
                if(sem->available() >= 1) sem->acquire();
                else{
                    arreter();
                    while(sem->available() == 0);
                    sem->acquire();
                    depart();
                }
                diriger_aiguillage(1, TOUT_DROIT,  0);
            }
            else if(parcours.at(i) == 6){
                if(sem->available() >= 1) sem->acquire();
                else{
                    arreter();
                    while(sem->available() == 0);
                    sem->acquire();
                    depart();
                }
                diriger_aiguillage(1, DEVIE, 0);
            }
            else if(parcours.at(i) == 31){
                if(locomotive->numero() == 1){
                    diriger_aiguillage(22, DEVIE, 0);
                }
                else if(locomotive->numero() == 2){
                    diriger_aiguillage(22, TOUT_DROIT, 0);
                }
                sem->release();
            }
            i++;
            if(i == parcours.size()) i = 0;
        }

        arreter();
    }

};


//Creation des locomotive
QList<LocomotiveThread*> locomotives;



//Arret d'urgence
void emergency_stop()
{
    for(LocomotiveThread* loco : locomotives){
        loco->arreter();
    }
    afficher_message("\nSTOP!");
}

//Fonction principale
int cmain()
{
    afficher_message("Hit play to start the simulation...");

    //Genere la semaphore
    QSemaphore* sem = new QSemaphore(1);

    //Choix de la maquette
    selection_maquette(MAQUETTE_A);

    //Initialisation d'un parcours
    QList<int> parcours1, parcours2;
    parcours1 << 15 << 14 << 7 << 6 << 1 << 31 << 33 << 32 << 25 << 24;
    parcours2 << 12 << 10 << 3 << 2 << 1 << 31 << 30 << 28 << 21 << 20;

    //Initialisation de la locomotive
    locomotives.append(new LocomotiveThread(1, 10, QPair<int,int>(16,23), true, parcours1, sem));
    locomotives.append(new LocomotiveThread(2, 12, QPair<int,int>(13,19), true, parcours2, sem));

    //Initialisation des aiguillages pour loco 1
    diriger_aiguillage(8,  DEVIE,       0);
    diriger_aiguillage(2,  TOUT_DROIT,  0);
    diriger_aiguillage(20, DEVIE,       0);
    diriger_aiguillage(14, DEVIE,       0);
    diriger_aiguillage(11, TOUT_DROIT,  0);
    diriger_aiguillage(17, TOUT_DROIT,  0);
    diriger_aiguillage(23, TOUT_DROIT,  0);
    diriger_aiguillage(21, TOUT_DROIT,  0);


    //Initialisation des aiguillages pour loco 2
    diriger_aiguillage(10, TOUT_DROIT,  0);
    diriger_aiguillage(7,  TOUT_DROIT,  0);
    diriger_aiguillage(4,  TOUT_DROIT,  0);
    diriger_aiguillage(1,  TOUT_DROIT,  0);
    diriger_aiguillage(22, TOUT_DROIT,  0);
    diriger_aiguillage(19, TOUT_DROIT,  0);
    diriger_aiguillage(16, TOUT_DROIT,  0);
    diriger_aiguillage(13, TOUT_DROIT,  0);

    //Lancement de la locomotive
    locomotives.at(0)->start();
    locomotives.at(1)->start();

    locomotives.at(0)->wait();
    locomotives.at(1)->wait();

    //Fin de la simulation
    mettre_maquette_hors_service();

    //Exemple de commande
    afficher_message("Enter a command in the input field at the top of the window.");
    QString commande = getCommand();
    afficher_message(qPrintable(QString("Your command is: ") + commande));

    return EXIT_SUCCESS;
}
