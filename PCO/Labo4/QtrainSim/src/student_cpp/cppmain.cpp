#include "ctrain_handler.h"
#include "locomotive.h"

#include <QThread>
#include <QList>
#include <QPair>
#include <QSemaphore>
#include <QMutex>

int numTrain1 = 2;
int numTrain2 = 14;

int vitesseLoco1 = 3;
int vitesseLoco2 = 5;

//Sorte de sémaphore non bloquant
class ZoneCritique{
private:
    QMutex* mutex;
    QSemaphore* sem;
    bool libre;
    QPair<int, int> aiguillageCrit1;
    QPair<int, int> aiguillageCrit2;
    int nbLoco;
    bool derivation;
public:
    ZoneCritique(QPair<int, int> aiguillageCrit1, QPair<int, int> aiguillageCrit2, QSemaphore* sem){
        libre = true;
        derivation = false;
        mutex = new QMutex();
        nbLoco = 0;
        this->sem = sem;
        this->aiguillageCrit1 = aiguillageCrit1;
        this->aiguillageCrit2 = aiguillageCrit2;
    }

    bool peutEntrer(int numLocomotive){
        afficher_message(qPrintable(QString("Entering the critical Area!")));
        mutex->lock();
        bool resultat = false;
        if(libre){
            if(numLocomotive == numTrain1){
                diriger_aiguillage(aiguillageCrit1.first, DEVIE, 0);
                diriger_aiguillage(aiguillageCrit1.second, DEVIE, 0);
            }
            bloquer();
            libre = false;
            resultat = true;
        }
        else{
            if(numLocomotive == numTrain1){
                diriger_aiguillage(aiguillageCrit2.first, DEVIE, 0);
                diriger_aiguillage(aiguillageCrit2.second, DEVIE, 0);
                derivation = true;
            }
        }
        mutex->unlock();
        return resultat;
    }

    void sortir(int numLocomotive){
        if(numLocomotive == numTrain1){
            diriger_aiguillage(aiguillageCrit1.first, TOUT_DROIT, 0);
            diriger_aiguillage(aiguillageCrit1.second, TOUT_DROIT, 0);
            diriger_aiguillage(aiguillageCrit2.first, TOUT_DROIT, 0);
            diriger_aiguillage(aiguillageCrit2.second, TOUT_DROIT, 0);

            if(!derivation){
                liberer();
            }
            derivation = false;
        }
        if(numLocomotive == numTrain2){
            liberer();
        }
        afficher_message(qPrintable(QString("Exiting the critical Area!")));
        libre = true;
    }

    void bloquer(){
        sem->acquire();
    }

    void liberer(){
        sem->release();
    }
};

class LocomotiveThread : public QThread{
private:
    Locomotive* locomotive;
    QList<int> parcours;
    QPair<int, int> capteurCritique;
    ZoneCritique* zoneCritique;
    bool sens; //true = marche avant
    int nbTour;
public:

    //Initialisation de la locomotive
    LocomotiveThread(int id, int vitesse, QPair<int, int> departCapteur, bool phare, QList<int> parcours, QPair<int, int> capteurCritique, ZoneCritique* zoneCritique){
        locomotive = new Locomotive();
        locomotive->fixerNumero(id);
        locomotive->fixerVitesse(vitesse);
        locomotive->fixerPosition(departCapteur.first, departCapteur.second);
        if(phare) locomotive->allumerPhares();
        this->parcours = parcours;
        this->capteurCritique = capteurCritique;
        this->zoneCritique = zoneCritique;
        sens = true;
        nbTour = 0;
        locomotive->afficherMessage("Ready!");
    }

    void depart(){
        locomotive->demarrer();
        locomotive->afficherMessage(qPrintable(QString("The engine is starting!")));
    }
    void arreter(){
        locomotive->arreter();
        locomotive->afficherMessage(qPrintable(QString("The engine is stopping!")));
    }

    void run() Q_DECL_OVERRIDE{
        depart();

        //Attente du passage sur les contacts
        int pos = 0;
        while(true){
            contact(parcours.at(pos));
            if(parcours.at(pos) == capteurCritique.first || parcours.at(pos) == capteurCritique.second){
               //if(locomotive->numero() == 1) zoneCritique->essayerBloquer();
               if(!zoneCritique->peutEntrer(locomotive->numero()) && locomotive->numero() == numTrain2){
                   arreter();
                   zoneCritique->bloquer();
                   depart();
               }
               while(true){
                   pos = prochainePosition(pos);
                   if(parcours.at(pos) == capteurCritique.first || parcours.at(pos) == capteurCritique.second) break;
               }
               contact(parcours.at(pos));
               zoneCritique->sortir(locomotive->numero());
            }
            pos = prochainePosition(pos);
        }
        locomotive->afficherMessage(QString("Yeah, piece of cake for locomotive %1 !").arg(locomotive->numero()));
        arreter();
    }

    int prochainePosition(int pos){
        if(sens) pos++;
        else pos--;
        if(pos >= parcours.size()){
           pos = 0;
           nbTour++;
        }
        if(pos < 0){
           pos = parcours.size() - 1;
           nbTour++;
        }
        if(nbTour == 2){
            sens = (sens ? false : true);
            nbTour = 0;
            pos = (sens ? 0 : parcours.size() - 1);
            locomotive->inverserSens();
        }

        return pos;
    }

    void contact(int capteur){
        attendre_contact(capteur);
        afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.")
                                    .arg(locomotive->numero()).arg(capteur)));
        locomotive->afficherMessage(QString("I've reached contact no. %1.").arg(capteur));
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

    //Zone critique locomotives
    QPair<int, int> critique1 = QPair<int,int>(7, 32);
    QPair<int, int> critique2 = QPair<int,int>(3, 29);

    //Choix de la maquette
    selection_maquette(MAQUETTE_A);

    //Initialisation des parcours
    QList<int> parcours1, parcours2;
    parcours1 << 15 << 14 << 7 << 6 << 1 << 31 << 33 << 32 << 25 << 24;
    parcours2 << 12 << 10 << 3 << 2 << 1 << 31 << 30 << 29 << 28 << 21 << 20;

    //Zone critique partager
    ZoneCritique* zoneCritique = new ZoneCritique(QPair<int, int>(1, 22), QPair<int, int>(2, 21), new QSemaphore(1));

    //Initialisation des locomotives
    locomotives.append(new LocomotiveThread(numTrain1, vitesseLoco1, QPair<int,int>(16,23), true, parcours1, critique1, zoneCritique));
    locomotives.append(new LocomotiveThread(numTrain2, vitesseLoco2, QPair<int,int>(13,19), true, parcours2, critique2, zoneCritique));

    //Initialisation des aiguillages pour loco 1
    diriger_aiguillage(8,  DEVIE,       0);
    diriger_aiguillage(2,  TOUT_DROIT,  0);
    diriger_aiguillage(5,  TOUT_DROIT,  0);
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
