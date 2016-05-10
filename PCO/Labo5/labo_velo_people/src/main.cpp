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


