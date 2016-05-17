/******************************************************************************
  \file main.cpp
  \author Yann Thoma
  \date 05.05.2011

  Ce fichier propose un squelette pour l'application de gestion des vélos.
  Il est évident qu'il doit être grandement modifié pour respecter la donnée,
  mais vous y trouvez des exemples d'appels de fonctions de l'interface.
  ****************************************************************************/

#include <QApplication>
#include "bikinginterface.h"
#include <deque>
#include <QWaitCondition>
#include <QMutex>
#include <QSemaphore>


// Pour utiliser cout, cin
#include <iostream>
using namespace std;

#define NBSITES 8
#define NBHABITANTS 10


/**
 Inteface pour l'envoi de commandes à l'interface graphique.
 Elle peut sans problème être partagée entre les différents threads.
 */
BikingInterface *gui_interface;

#include <QThread>

class Site{
public:
    Site(unsigned int id, unsigned int nbBorne) : id(id), nbBorne(nbBorne) {
        habitantEnAttente = new deque<unsigned int>();
        moniteur = new QWaitCondition();
        mutex = new QMutex();
        maintenance = new QWaitCondition();
        maintenanceMutex = new QMutex();
        nbVelo = nbBorne - 2;
        isMaintenance = false;
    }

    void ajouterVelo(unsigned int idHabitant){
        // La camionette à toujours l'id 0
        if(isMaintenance && idHabitant != 0){
            maintenance->wait(maintenanceMutex);
        }
        mutex->lock();
        //Si les vélo sont plein, on met en attente l'habitant qui essaie d'ajouter un vélo
        if(nbVelo >= nbBorne){
            habitantEnAttente->push_back(idHabitant);
            moniteur->wait(mutex);
            while(habitantEnAttente->front() != idHabitant){
                moniteur->wait(mutex);
            }
            habitantEnAttente->pop_front();
            nbVelo++;
        }
        //Si les vélo ne sont pas plein, on ajoute simplement le vélo
        else{
            nbVelo++;
        }
        //On wakeAll si il reste des places libre car si la camionette prends plusieurs vélo, il faut que plusieurs utilisateurs soient capable de prendre les vélos ensuite
        if(nbVelo < nbBorne && !isMaintenance) moniteur->wakeAll();
        mutex->unlock();
    }

    void enleverVelo(unsigned int idHabitant){
        // La camionette à toujours l'id 0
        if(isMaintenance && idHabitant != 0){
            maintenance->wait(maintenanceMutex);
        }
        mutex->lock();
        //Si les vélo sont vide, on met en attente l'habitant qui essaie de prendre un vélo
        if(nbVelo <= 0){
            habitantEnAttente->push_back(idHabitant);
            moniteur->wait(mutex);
            while(habitantEnAttente->front() != idHabitant){
                moniteur->wait(mutex);
            }
            habitantEnAttente->pop_front();
            nbVelo--;
        }
        //Si les vélo ne sont pas vide, on réveille les potentiel habitant qui attendent d'ajouter un vélo
        else{
            nbVelo--;

        }
        //On wakeAll si il y reste des vélo car si la camionette ramene plusieurs vélo, il faut que plusieurs utilisateurs soit capable de laisser leur vélo.++
        if(nbVelo > 0 && !isMaintenance) moniteur->wakeAll();
        mutex->unlock();
    }

    void debutMaintenance(){
        isMaintenance = true;
    }

    void finMaintenance(){
        maintenanceMutex->lock();
        isMaintenance = false;
        maintenance->wakeAll();
        moniteur->wakeAll();
        maintenanceMutex->unlock();
    }

    unsigned int getId(){
        return id;
    }

    unsigned int getNbVelo(){
        return nbVelo;
    }

private:

    unsigned int id;
    unsigned int nbBorne;
    unsigned int nbVelo;
    std::deque<unsigned int>* habitantEnAttente;
    QWaitCondition* moniteur;
    QMutex* mutex;
    QWaitCondition* maintenance;
    QMutex* maintenanceMutex;
    bool isMaintenance;

};

/**
  Tâche illustrant les différents appels pouvant être faits à l'interface
  graphique.
  */
class Habitant: public QThread
{
public:
    Habitant(unsigned int id) : id(id) {}

void run() Q_DECL_OVERRIDE {
    unsigned int t = id;
    unsigned int sites[2];
    sites[0]=t%NBSITES;
    sites[1]=(t+1)%NBSITES;
    unsigned int curSite=0;
    qsrand(t);

    while(1) {
        // Affichage d'un message
        gui_interface->consoleAppendText(t,"Salut");
        if (t==0) {
            // Déplacement de la camionnette
            gui_interface->vanTravel(t,NBSITES,2000);
            gui_interface->setBikes(NBSITES,((float)qrand())*5.0/RAND_MAX);
        }
        else {
            // Déplacement d'un vélo
            gui_interface->travel(t,             // ID de la personne
                                  t,             // Site de départ
                                  (t+1)%NBSITES, // site d'arrivée
                                  (t+1)*1000);   // Temps en millisecondes
            // On définit aléatoirement le nombre de vélos sur un site
            gui_interface->setBikes((t+1)%NBSITES,((float)qrand())*5.0/RAND_MAX);
            // On définit aléatoirement le nombre de vélos sur un site
            gui_interface->setBikes(sites[1-curSite],((float)qrand())*5.0/RAND_MAX);
            curSite=1-curSite;
        }

        QThread::usleep(1000000);
    }
}

private:
    unsigned int id;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int nbHabitants=NBHABITANTS;
    int nbSites=NBSITES;

    // Initialisation de la partie graphique de l'application
    BikingInterface::initialize(nbHabitants,nbSites);
    // Création de l'interface pour les commandes à la partie graphique
    gui_interface=new BikingInterface();

    // Création de threads
    int NBTHREADS=nbHabitants;
    Habitant* threads[NBTHREADS];
    int t;
    for(t=0; t<NBTHREADS; t++){
        cout << "Création du thread "<< t << endl;
        threads[t] = new Habitant(t);
        threads[t]->start();
    }

    // Attention, il est obligatoire d'exécuter l'instruction suivante.
    // C'est elle qui permet la gestion de la boucle des évévements de
    // l'application graphique.
    return a.exec();
}


