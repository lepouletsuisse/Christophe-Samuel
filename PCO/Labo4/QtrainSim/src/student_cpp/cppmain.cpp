/* PCO
 * ---------------------------------------------------------------------------
 * Labo:    04 QtrainSim
 * Auteur:  Christophe Peretti & Samuel Darcey
 * Date:    03.05.2016
 * But :    Définir les comportements des locomotives dans la simulation
 *          de train. Gérer la configuration initiale de la maquette, les
 *          parcours des locomotives, ainsi que la zone critique commune
 *          entre les loco.
 * Rapport:
 *      REMARQUE:
 *          Nous avons utilisé la maquette A, le choix des parcours ne peuvent
 *          jouer qu'avec cette maquette.
 *          Dans la version testée sur la maquette, tout fonctionnait excepté
 *          le changement de sens. Celui-ci ne fonctionnait pas bien car les
 *          locomotives avaient très peu d'inertie. Lors du changement de sens
 *          après un capteur, la loco devait repasser par le même capteur et
 *          elle s'arrêtait sur celui-ci. Dans la version actuelle, la mise à
 *          jour du trajet se fait de façon plus optimisée: la loco attend de
 *          rejoindre le capteur suivant et non plus le même.
 *      TESTS:
 *        - L'arrêt d'urgence a été testé et fonctionne bien dans la simulation
 *          ainsi que sur la maquette.
 *        - Pour les vitesses, dans la simulation, celles-ci peuvent prendre
 *          n'importe quelle valeur (testé jusqu'à 300), tant que l'inertie est
 *          désactivée. En effet, lors d'un arrêt d'une loco celle-ci effectue
 *          encore des kilomètres avant de s'arrêter si l'inertie est activée.
 *          Sur la maquette, des vitesses entre 3 et 7 ont été testées. En
 *          dessous, il y a un risque qu'une loco s'arrête sur un aiguillage
 *          à cause du frottement. En dessus, un risque d'abîmer le matériel
 *          est non-négligeable.
 *        - La simulation a été testée pendant 45 minutes non-stop.
 *      RESULTATS:
 *        - Aucune collision intempestive n'a été détectée.
 *        - Le changement d'aiguillage se fait correctement, toujours commandé
 *          par la loco 1.
 *        - La loco 1 prend la déviation lorsque la loco 2 est dans la zone critique.
 *        - La loco 2 s'arrête lorsque la loco 1 est dans la zone critique.
 *
 * ---------------------------------------------------------------------------
*/

#include "ctrain_handler.h"
#include "locomotive.h"
#include <QThread>
#include <QList>
#include <QPair>
#include <QSemaphore>
#include <QMutex>

/* Les numéros des trains doivent correspondre aux numéros des vraies
 * locomotives dans la maquette, afin que les capteurs reconnaissent
 * bien les loco. Pour la simulation, deux numéros différents suffisent.
 *
 * Utilisé uniquement en lecture
 */
int numTrain1 = 2;
int numTrain2 = 14;

/* La vitesse des locomotives peuvent valoir n'importe quelle valeur
 * dans la simulation (tant que l'inertie est désactivée). Lors de
 * l'utilisation de la maquette, celles-ci ne devraient pas dépasser
 * 10, pour des raisons mécaniques.
 *
 * Utilisé uniquement en lecture
 */
int vitesseLoco1 = 26;
int vitesseLoco2 = 28;

/* Classe gérant la zone critique de la maquette
 *
 * Les deux loco avertissent quand la zone est occupée, mais elles
 * ont un comportement différent dans celle-ci. Si la zone est libre
 * lorsque la loco 1 arrive, elle entre normalement et empêche la 2
 * d'y entrer. Dans l'autre situation, si la 2 entre dans la zone critique
 * avant la 1, cela ne bloque pas la 1, mais active la dérivation, donc la
 * mise en parallèle des deux loco.
 *
 * A la sortie de la zone critique, la loco 2 remet la zone comme étant
 * libre (dans tous les cas) et pour la loco 1, elle le fait uniquement
 * si elle n'a pas été déviée. Donc pas de problème de concurrence sur la
 * variable libre lorsque les deux loco sont en parallèle dans la zone critique
 *
 * Si la loco 2 a été arrêtée, elle met la zone comme non-libre seulement après
 * être repartie, donc après que la loco 1 ait libéré la zone. Il n'y a donc
 * ici non plus de problème de concurrence sur la variable libre.
 *
 *
 */
class ZoneCritique{
private:
    QMutex* mutex;
    QSemaphore* sem;
    bool libre;
    QPair<int, int> aiguillageCrit1;
    QPair<int, int> aiguillageCrit2;
    bool derivation;
public:
    ZoneCritique(QPair<int, int> aiguillageCrit1,
                 QPair<int, int> aiguillageCrit2, QSemaphore* sem){
        libre = true;
        derivation = false;
        mutex = new QMutex();
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
                libre = true;
                liberer();
            }
            derivation = false;
        }
        if(numLocomotive == numTrain2){
            libre = true;
            liberer();

        }
        afficher_message(qPrintable(QString("Exiting the critical Area!")));
    }

    void setLibre(bool val){
        libre = val;
    }

    void bloquer(){
        sem->acquire();
    }

    void liberer(){
        sem->release();
    }
};

/* Classe gérant les thread des locomotives. Ces thread ont une référence sur
 * la même instance de la zone critique et font appel à ses méthodes.
 *
 * Les méthodes départ() et arreter() sont utiles car le fait d'arrêter ou non
 * un thread n'a pas de conséquence "physique" sur les locomotives.
 *
 *
 * */
class LocomotiveThread : public QThread{
private:
    Locomotive* locomotive;
    QList<int> parcours;
    QPair<int, int> capteurCritique;
    ZoneCritique* zoneCritique;
    bool sens; //true = marche avant
    int nbTour; // Utile pour changer de sens après 2 tours
public:

    //Initialisation de la locomotive
    LocomotiveThread(int id, int vitesse, QPair<int, int> departCapteur,
                     bool phare, QList<int> parcours,
                     QPair<int, int> capteurCritique,
                     ZoneCritique* zoneCritique){
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

        /* Attente du passage sur les contacts. La zone critique n'a pas de début
         * ou de fin, mais des bornes (utile pour gérer les deux sens).
         *
         */
        int pos = 0;
        while(true){
            contact(parcours.at(pos));
            // Action à l'entrée de la zone critique
            if(parcours.at(pos) == capteurCritique.first ||
                    parcours.at(pos) == capteurCritique.second){
                // Action spéciale pour la loco 2 si la zone est occupée:
                // elle s'arrête et attend que l'autre sorte de la zone
               if(!zoneCritique->peutEntrer(locomotive->numero()) &&
                       locomotive->numero() == numTrain2){
                   arreter();
                   zoneCritique->bloquer();
                   // Avant de repartir, la loco 2 indique qu'elle entre dans la zone critique
                   zoneCritique->setLibre(false);
                   depart();
               }
               while(true){
                   pos = prochainePosition(pos);
                   if(parcours.at(pos) == capteurCritique.first ||
                           parcours.at(pos) == capteurCritique.second) break;
               }
               contact(parcours.at(pos));
               zoneCritique->sortir(locomotive->numero());
            }
            pos = prochainePosition(pos);
        }
        locomotive->afficherMessage(QString("Yeah, piece of cake for locomotive %1 !")
                                    .arg(locomotive->numero()));
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
            sens = !sens;
            nbTour = 0;
            // On saute un capteur lors du changement de sens, pour ne pas rester bloqué
            pos = (sens ? 1 : parcours.size() - 2);
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
    ZoneCritique* zoneCritique = new ZoneCritique(QPair<int, int>(1, 22),
                                                  QPair<int, int>(2, 21),
                                                  new QSemaphore(1));

    //Initialisation des locomotives
    locomotives.append(new LocomotiveThread(numTrain1, vitesseLoco1,
                                            QPair<int,int>(16,23), true,
                                            parcours1, critique1, zoneCritique));
    locomotives.append(new LocomotiveThread(numTrain2, vitesseLoco2,
                                            QPair<int,int>(13,19), true,
                                            parcours2, critique2, zoneCritique));

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
