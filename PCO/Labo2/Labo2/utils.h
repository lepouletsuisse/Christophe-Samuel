/* PCO Labo2
 * Samuel Darcey & Christophe Peretti
 * 14.03.16
 *
 */

#include <iostream>
#include <chrono>

#ifndef UTILS_H
#define UTILS_H


#define PRECISION_CHRONO 1000 // Précision des chronomètres exprimé en microsecondes*PRECISION_CHRONO (1 => μs, 1000 => ms, 1000000 => s)
bool prime = true;            // Variable globale utile pour qu'un thread avertisse les autres qu'il a trouvé un diviseur du nombre.

using namespace std;

// Teste la variable globale partagée entre les threads et affiche si le nombre est premier ou non
void printPrime(){
    if(!prime){
        cout << "NOT A PRIME NUMBER!!" << endl;
    }
    else{
        cout << "PRIME NUMBER!!" << endl;
    }
    cout << endl;
}

// Démarre un chronomètre grande précision
std::chrono::high_resolution_clock::time_point startChrono(){
    return std::chrono::high_resolution_clock::now();
}

// Arrête un chronomètre et retourne le total (unité dépendant de PRECISION_CHRONO)
double stopChrono(std::chrono::high_resolution_clock::time_point start){
    std::chrono::high_resolution_clock::duration temps = std::chrono::high_resolution_clock::now() - start;
    return (double)std::chrono::duration_cast<std::chrono::microseconds>(temps).count()/PRECISION_CHRONO;
}

#endif // UTILS_H
