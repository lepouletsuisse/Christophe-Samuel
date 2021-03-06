/* PCO
 * ---------------------------------------------------------------------------
 * Labo:    05 labo_velo
 * Auteur:  Christophe Peretti & Samuel Darcey
 * Date:    30.05.2016
 * But :    Gérer un système de parcours d'habitants utilisant des vélos et
 *          se déplaçant entre plusieurs sites de manière aléatoire. Une
 *          camionnette est également présente, permettant de réguler les
 *          vélos à chaque site afin qu'il n'y ait pas de débordement ou de
 *          pénurie de vélo.
 *
 * Rapport:
 *      REMARQUE:
 *          L'application est principalement gérée par les sites. La logique
 *          de bloquage se trouve également dans les sites. Cela nous permet
 *          d'avoir un système centralisé et d'éviter de devoir passer des
 *          mutex à tous vas.
 *
 *          Les sites ont 2 fonctions principales: ajouterVelo() et enleverVelo()
 *          Ces fonctions permettent d'ajouter ou de supprimer un vélo dans
 *          un site de manière contrôlée. Malgrès cela, il y'a un système
 *          de bypass pour la camionette car elle ne devrait jamais se bloquer
 *          Il y'a également un bypass pour l'habitant NBHABITANT + 1 qui
 *          correspond a la console de l'application et permet les saisies
 *          et modifications utilisateur. De même, ce bypass n'est pas bloquant.
 *          Il aurait été possible de faire des fonctions à part pour ces
 *          entités là, mais là encore, nous avons préféré une approche plus
 *          unifiée.
 *
 *          L'algorithme pour la camionette a été légérement modifiée afin
 *          que l'on enlève les vélos de manière itérative (3 vélos à enlever
 *          = -1 -1 -1). Cela nous permet, une fois encore, de n'avoir
 *          qu'une seule fonction qui gère ceci. Nous avons donc une
 *          fonction de maintenance qui permet de mettre un site en maintenance
 *          et empèche les habitants de modifier un site. Bien sûr, le calcul
 *          du nombre de vélos à ajouter ou enlevé se fait au début de la
 *          maintenance, et non à chaque fois que la camionette pose ou enlève
 *          un vélo.
 *      TESTS:
 *          Nous avons effectué un maximum de tests possibles pour les
 *          fonctionnalités présentes dans notre programme mais certaines
 *          fonctionnalités n'on pas pu être tester (Maintenance de la
 *          camionette: Cela se déroule sur un laps de temps trop court pour
 *          être testé).
 *
 *      RESULTATS:
 *          Un étrange problème faisant crash l'application au démmarage selon
 *          le nombre d'habitant et de sites spécifié a été constaté mais comme
 *          le bug n'apparaissant pas toujours et la source n'ayant pas pu être
 *          identifier, nous n'avons pas résolu ce problème.
 *          Aucun autre soucis visible n'a été détecté malgrès certains comportements
 *          qui n'ont pas pu être testés.
 *
 * ---------------------------------------------------------------------------
*/

#include <QApplication>
#include "bikinginterface.h"
#include <deque>
#include <QWaitCondition>
#include <QMutex>
#include <QSemaphore>
#include <QThread>
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

QMutex* mutexDepot;
unsigned int nbVelosDepot;
unsigned int nbSites;
unsigned int nbHabitants;
unsigned int nbBornes;
unsigned int nbVelos;

/**
 Inteface pour l'envoi de commandes à l'interface graphique.
 Elle peut sans problème être partagée entre les différents threads.
 */
BikingInterface *gui_interface;

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
        tmpVelo = 0;
    }

    void ajouterVelo(unsigned int idHabitant){
        // La camionette à toujours l'id 0 et la console à l'ID NBHABITANT
        if(isMaintenance && idHabitant != 0){
            if(idHabitant == nbHabitants + 1){
                cout << "Il y a une maintenance! Veuillez réessayer plus tard..." << endl;
                return;
            }
            gui_interface->consoleAppendText(idHabitant, "La camionette est là! Attente...");
            maintenance->wait(maintenanceMutex);
            gui_interface->consoleAppendText(idHabitant, "La camionette a fini!");
        }
        mutex->lock();
        if(idHabitant == nbHabitants + 1){
            if(nbVelo < nbBorne) nbVelo++;
            mutex->unlock();
            return;
        }
        //Si les vélo sont plein, on met en attente l'habitant qui essaie d'ajouter un vélo
        if(nbVelo >= nbBorne){
            gui_interface->consoleAppendText(idHabitant, "Trop de vélos! Attente...");
            habitantEnAttente->push_back(idHabitant);

            //bloqué jusqu'au passage de la camionette (ou qu'un autre cycliste enlève un velo)
            moniteur->wait(mutex);

            while(habitantEnAttente->front() != idHabitant || nbVelo >= nbBorne){
                gui_interface->consoleAppendText(idHabitant,"Ce n'est pas mon tour! Tour de : " + QString::number(habitantEnAttente->front()));
                moniteur->wait(mutex);
            }
            habitantEnAttente->pop_front();
            gui_interface->consoleAppendText(idHabitant, "Placement du vélo!");
            nbVelo++;
        }
        //Si les vélo ne sont pas plein, on ajoute simplement le vélo
        else{
            nbVelo++;
        }
        //On wakeAll si il reste des places libre car si la camionette prends plusieurs vélo, il faut que plusieurs utilisateurs soient capable de prendre les vélos ensuite
        if(nbVelo < nbBorne && !isMaintenance){
            moniteur->wakeAll();
        }

        gui_interface->setBikes(getId(),getNbVelo());
        mutex->unlock();
    }

    void enleverVelo(unsigned int idHabitant){
        // La camionette à toujours l'id 0 et la console à l'ID NBHABITANT
        if(isMaintenance && idHabitant != 0){
            if(idHabitant == nbHabitants + 1){
                cout << "Il y a une maintenance! Veuillez réessayer plus tard..." << endl;
                return;
            }
            gui_interface->consoleAppendText(idHabitant, "La camionette est là! Attente...");
            maintenance->wait(maintenanceMutex);
            gui_interface->consoleAppendText(idHabitant, "La camionette a fini!");
        }
        mutex->lock();
        if(idHabitant == nbHabitants + 1){
            if(nbVelo > 0) {
                QString text = "Un vélo enlevé du site n°";
                text.append(QString::number(getId() + 1));
                gui_interface->consoleAppendText(idHabitant, text);
                nbVelo--;
            } else {
                gui_interface->consoleAppendText(idHabitant, "Il n'y a pas de vélo sur ce site!");
            }
            gui_interface->setBikes(getId(),getNbVelo());
            mutex->unlock();
            return;
        }
        //Si les vélo sont vide, on met en attente l'habitant qui essaie de prendre un vélo
        if(nbVelo <= 0){
            gui_interface->consoleAppendText(idHabitant, "Pas assez de vélos! Attente...");
            habitantEnAttente->push_back(idHabitant);
            moniteur->wait(mutex);
            while(habitantEnAttente->front() != idHabitant || nbVelo <= 0){
                gui_interface->consoleAppendText(idHabitant,"Ce n'est pas mon tour! Tour de : " + QString::number(habitantEnAttente->front()));
                moniteur->wait(mutex);
            }
            habitantEnAttente->pop_front();
            gui_interface->consoleAppendText(idHabitant, "Prise du vélo!");
            nbVelo--;

        }
        //Si les vélo ne sont pas vide, on réveille les potentiel habitant qui attendent d'ajouter un vélo
        else{
            nbVelo--;
        }
        //On wakeAll si il y reste des vélo car si la camionette ramene plusieurs vélo, il faut que plusieurs utilisateurs soit capable de laisser leur vélo.++
        if(nbVelo > 0 && !isMaintenance){
            moniteur->wakeAll();
        }
        gui_interface->setBikes(getId(),getNbVelo());
        mutex->unlock();
    }

    void debutMaintenance(){
        isMaintenance = true;
        tmpVelo = nbVelo;
    }

    void finMaintenance(){
        maintenanceMutex->lock();
        isMaintenance = false;
        maintenance->wakeAll();
        if(tmpVelo != nbVelo) moniteur->wakeAll();
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
    unsigned int tmpVelo;
};

vector<Site*> sites;

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
    unsigned int tempsTrajet;
    unsigned int tempsActivite;

    position = t;
    nbVelosCamionette = 0;
    nbVelosDepot = nbVelos - (nbSites * (nbBornes - 2));


    qsrand(t);

    arrivee = 1;
    if (t==0){
        position = nbSites;
        arrivee = 0;
    }


    while(1) {
        if (t==0) {     // La camionette a l'id
            gui_interface->setBikes(nbSites,nbVelosDepot);
            arrivee = (position + 1) % (nbSites + 1);
            unsigned int c;

            // Gestion du dépôt
            if (position == nbSites){
                mutexDepot->lock();
                nbVelosDepot += nbVelosCamionette;
                c = min((unsigned int)2,nbVelosDepot);
                nbVelosCamionette = c;
                nbVelosDepot -= c;
                gui_interface->setBikes(position,nbVelosDepot);
                mutexDepot->unlock();
            } else{
                sites.at(position)->debutMaintenance();
                // S'il y a trop de vélo sur le site
                if(sites.at(position)->getNbVelo() > nbBornes - 2){
                    c = min(sites.at(position)->getNbVelo() - (nbBornes - 2), 4 - nbVelosCamionette);
                    for(unsigned int i = 0; i < c; i++){
                        sites.at(position)->enleverVelo(id);
                    }
                    nbVelosCamionette += c;

                // S'il y en a pas assez
                } else if(sites.at(position)->getNbVelo() < nbBornes - 2){
                    c = min((nbBornes - 2) - sites.at(position)->getNbVelo(), nbVelosCamionette);
                    for(unsigned int i = 0; i < c; i++){
                        sites.at(position)->ajouterVelo(id);
                    }
                    nbVelosCamionette -= c;
                }

                sites.at(position)->finMaintenance();

            }
            // Messages
            gui_interface->consoleAppendText(t, "Velos dans la camionette :");
            gui_interface->consoleAppendText(t,QString::number(nbVelosCamionette));


            // Déplacement de la camionnette
            tempsTrajet = 1000 + (qrand() * 1000) % 2000;
            gui_interface->vanTravel(position,arrivee,tempsTrajet);
            position = arrivee;


        } else {
            // Affichage d'un message
            gui_interface->consoleAppendText(t, "Position du velo :");
            gui_interface->consoleAppendText(t,QString::number(position));

            do{
                arrivee = qrand() % nbSites;
            }while(position == arrivee);
            tempsTrajet = 1000 + (qrand() * 1000) % 2000;
            // Déplacement d'un vélo

            gui_interface->travel(t,             // ID de la personne
                                  position,      // Site de départ
                                  arrivee,       // site d'arrivée
                                  tempsTrajet);  // Temps en millisecondes
            position = arrivee;
            sites.at(position)->ajouterVelo(id);
            gui_interface->setBikes(sites.at(position)->getId(),sites.at(position)->getNbVelo());


        }


        if (t != 0){
            tempsActivite = 1000000 + (qrand() * 1000) % 3000000;
            QThread::usleep(tempsActivite);
            sites.at(position)->enleverVelo(id);
        } else {
            // La camionette fait une pause uniquement au dépôt
            if (position == nbSites){
                QThread::usleep(2000000);
            }

        }
    }
}

private:
    unsigned int id;
    unsigned int position;
    unsigned int arrivee;
    unsigned int nbVelosCamionette;
    unsigned int prochainSite;
};

class Console: public QThread
{
public:
void run() Q_DECL_OVERRIDE {
    while(1){
        cout << "Que voulez-vous faire?" << endl;
        cout << "1) Ajouter un velo au depot" << endl;
        cout << "2) Enlever un velo sur un site" << endl;

        cin >> choix1;
        c1 = atoi(choix1.c_str());
        if (c1 == 1){
            mutexDepot->lock();
            nbVelosDepot++;
            gui_interface->consoleAppendText(nbHabitants + 1, "Un vélo ajouté au dépôt");
            gui_interface->setBikes(nbSites,nbVelosDepot);
            mutexDepot->unlock();
        } else if(c1 == 2) {
            cout << endl << "Sur quel site voulez-vous enlever un velo? (1-" << nbSites << ")" << endl;
            do{
                cin.clear();
                cin >> choix2;
                c2 = atoi(choix2.c_str());
            } while ((c2 > nbSites || c2 == 0) && (cout << "Nombre invalide" << endl)); // 0 Si le caractère n'est pas un nombre

            sites.at(c2 - 1)->enleverVelo(nbHabitants + 1);
        } else{
            cout << "Choix invalide! veuillez réessayer!" << endl;
        }
    }
}
private:
string choix1, choix2;
unsigned int c1, c2;
};



int main(int argc, char *argv[])
{

    if(argc != 5){
        std::cout << "Pas le bon nombre d'argument! [nbSites][nbHabitants][nbBornes][nbVelos]" << std::endl;
        return 1;
    }
    nbSites = atoi(argv[1]);
    nbHabitants = atoi(argv[2]);
    nbBornes = atoi(argv[3]);
    nbVelos = atoi(argv[4]);
    if (nbSites < 2){
        cout << "Le nombre de site doit etre >= 2" << endl;
        return 1;
    }
    if (nbBornes < 4){
        cout << "Le nombre de bornes par site doit etre >= 4" << endl;
        return 1;
    }

    if( nbVelos < (nbSites * (nbBornes - 2) + 3)){
        cout << "Le nombre de velos doit etre >= S(B - 2) + 3" << endl;
        return 1;
    }

    QApplication a(argc, argv);


    unsigned int t;
    mutexDepot = new QMutex();

    std::cout << "sites:" << endl;
    for(t=0; t<nbSites; t++){
        cout << "Creation du Site "<< t << endl;
        sites.push_back(new Site(t, nbBornes));
    }
    std::cout << "sites ok" << endl;

    // Initialisation de la partie graphique de l'application
    BikingInterface::initialize(nbHabitants + 2,nbSites);   // + 2 car un pour la camionnette et un pour le God Mode
    // Création de l'interface pour les commandes à la partie graphique
    gui_interface=new BikingInterface();

    for(unsigned int i=0; i < nbSites; i++){
        gui_interface->setBikes(sites.at(i)->getId(),sites.at(i)->getNbVelo());
    }

    // Création de threads
    Habitant* threads[nbHabitants + 1];     // + 1 pour la camionette

    std::cout << "Threads :" << endl;
    for(t=0; t<=nbHabitants; t++){
        cout << "Creation du thread "<< t << endl;
        threads[t] = new Habitant(t);
        threads[t]->start();
    }
    std::cout << "Threads ok" << endl;

    Console* c = new Console();
    c->start();

    // Attention, il est obligatoire d'exécuter l'instruction suivante.
    // C'est elle qui permet la gestion de la boucle des évévements de
    // l'application graphique.
    return a.exec();
}


