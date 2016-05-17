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
#define NBVELOSDEPOT 3
#define NBBORNES 4
#define NBVELOS 19
/**
 Inteface pour l'envoi de commandes à l'interface graphique.
 Elle peut sans problème être partagée entre les différents threads.
 */
BikingInterface *gui_interface;
unsigned int sites[NBSITES];

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
    position = t;
    nbVelosCamionette = 0;
    nbVelosDepot = NBVELOSDEPOT;

    qsrand(t);
    if (t==0){
        position = NBSITES;
        arrivee = 0;
        prochainSite = 0;
    }



    while(1) {

        if (t==0) {

            gui_interface->setBikes(NBSITES,nbVelosDepot);

            arrivee = (position + 1) % NBSITES;

            unsigned int c;

            // Gestion du dépôt
            if (position == NBSITES){
                nbVelosDepot += nbVelosCamionette;
                c = min((unsigned int)2,nbVelosDepot);
                nbVelosCamionette = c;
                nbVelosDepot -= c;
                gui_interface->setBikes(position,nbVelosDepot);

            } else{
                // S'il y a trop de vélo sur le site
                if(sites[position]->getNbVelo() > NBBORNES - 2){

                    sites[position]->debutMaintenance();
                    c = min(sites[position]->getNbVelo() - (NBBORNES - 2), 4 - nbVelosCamionette);
                    for(int i = 0; i < c; i++){
                        sites[position]->enleverVelo(id);
                    }
                    sites[position]->finMaintenance();
                    nbVelosCamionette += c;

                // S'il y en a pas assez
                } else if(sites[position]->getNbVelo() < NBBORNES - 2){

                    sites[position]->debutMaintenance();
                    c = min((NBBORNES - 2) - sites[position]->getNbVelo(), nbVelosCamionette);
                    for(int i = 0; i < c; i++){
                        sites[position]->ajouterVelo(id);
                    }
                    sites[position]->finMaintenance();
                    nbVelosCamionette -= c;
                }
            }
            // Messages
            gui_interface->consoleAppendText(t, "Velos dans la camionette :");
            gui_interface->consoleAppendText(t,QString::number(nbVelosCamionette));


            // Déplacement de la camionnette

            gui_interface->vanTravel(position,arrivee,500);
            position = arrivee;


        }
        else {
            // Affichage d'un message
            gui_interface->consoleAppendText(t, "Position du velo :");
            gui_interface->consoleAppendText(t,QString::number(position));

            arrivee = (position + 1) % NBSITES;
            // Déplacement d'un vélo

            gui_interface->travel(t,             // ID de la personne
                                  position,             // Site de départ
                                  arrivee, // site d'arrivée
                                  (t+1)*1000);   // Temps en millisecondes

            position = ++position % NBSITES;
        }

        QThread::usleep(1000000);
    }
}

private:
    unsigned int id;
    unsigned int position;
    unsigned int arrivee;
    unsigned int nbVelosCamionette;
    unsigned int nbVelosDepot;
    unsigned int prochainSite;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int nbHabitants=NBHABITANTS;
    int nbSites=NBSITES;
    int t;

    for(t=0; t<nbSites; t++){
        cout << "Création du Site "<< t << endl;
        sites[t] = new Site(NBBORNES);
    }

    // Initialisation de la partie graphique de l'application
    BikingInterface::initialize(nbHabitants,nbSites);
    // Création de l'interface pour les commandes à la partie graphique
    gui_interface=new BikingInterface();

    for(int i=0; i < NBSITES; i++){
        gui_interface->setBikes(site[i]->getId(),site[i]->getNbVelo());
    }

    // Création de threads
    int NBTHREADS=nbHabitants;
    Habitant* threads[NBTHREADS];

    for(t=0; t<NBTHREADS; t++){
        cout << "Création du thread "<< t << endl;
        threads[t] = new Habitant(t);
        threads[t]->start();
    }
    while(1){
        gui_interface->setBikes(site[i]->getId(),site[i]->getNbVelo());
        QThread::usleep(1000000);
    }

    // Attention, il est obligatoire d'exécuter l'instruction suivante.
    // C'est elle qui permet la gestion de la boucle des évévements de
    // l'application graphique.
    return a.exec();
}


