/* PCO Labo2
 * Samuel Darcey & Christophe Peretti
 * 14.03.16
 *
 */

#include <iostream>
#include <vector>
#include <chrono>
#include "mythread.h"
#include "utils.h"


using namespace std;

int main(int argc, char *argv[])
{
    vector<MyThread*> threads;
    uint64_t nombre = stoull(argv[1]), debut, fin;
    int nombreThread = atoi(argv[2]);
    double totalMS;
    std::chrono::high_resolution_clock::time_point start;


    if(argc != 3){
        cerr << "Arguments error!" << endl;
        cerr << "Try : <Labo2.exe numberToTest numberOfThreads>" << endl;
        return 1;
    }

    cout << "Chosen number: " << nombre << endl << endl;


    /* Partie  1
     * Un seul thread qui doit parcourir tous les nombres inférieurs à la racine carrée du nombre choisi
     *
     */

    fin = sqrt(nombre);
    cout << "Part 1 :" << endl;
    start = startChrono();

    for(uint64_t i = 2 ; i < fin ; i++){
        if(!(nombre % i)){
            prime = false;
            break;
        }
    }

    totalMS = stopChrono(start);
    cout << "Done in " << totalMS << (PRECISION_CHRONO == 1? "μs" : PRECISION_CHRONO == 1000? "ms" : PRECISION_CHRONO == 1000000? "s" : "") << endl;
    printPrime();


     /* Partie  2
      * Plusieurs threads (à choix) sont lancés afin de paraléliser le traitement.
      */
    cout << "Part 2 : Multithreading" << endl;
    cout << nombreThread << " Thread" << (nombreThread > 1 ? "s" : "") << endl;

    /* Création des threads, avec calcul des bornes d'itération:
     * Chaque thread va parcourir certains nombres inférieurs à la racine carrée du nombre choisi. Chaque thread ne va s'occuper que d'une
     * partie des diviseurs (1/N, N étant le nombre de threads). Le calcul des bornes de chaque thread se fait avant de créer le thread
     */
    for(int i = 0 ; i < nombreThread ; i++){
        debut = floor(i * sqrt(nombre) / nombreThread + 2);
        fin = floor((i + 1) * sqrt(nombre) / nombreThread + 2);
        MyThread* thread = new MyThread(debut, fin, nombre);
        cout << "Thread number " << i << " starts at " << debut << " and stops at " << fin - 1 << endl;
        threads.push_back(thread);
    }

    // On démarre les threads une fois qu'ils sont tous créés
    start = startChrono();
    for(size_t i = 0 ; i < threads.size() ; i++){
        threads.at(i)->start();
    }

    // Attente des threads
    for(size_t i = 0 ; i < threads.size() ; i++){
        threads.at(i)->wait();
        cout << "Thread " << i << " finished!" << endl;
    }

    // Calcul des temps d'exécution
    totalMS = stopChrono(start);
    cout << "Done in " << totalMS << (PRECISION_CHRONO == 1? "μs" : PRECISION_CHRONO == 1000? "ms" : PRECISION_CHRONO == 1000000? "s" : "") << endl;
    printPrime();

    return 0;
}
