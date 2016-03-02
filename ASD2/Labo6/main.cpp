/*
 * Laboratoire: 06
 * Fichier    : main.cpp
 * Auteurs    : Samuel Darcey et Christophe Peretti
 * Date       : 16 janvier 2016
 * But        :
 * Remarque(s):
 * Compilateur: MinGW-g++ 4.8.1
 */
#include "check.h"
using namespace std;

int main(){
    string inputFile, outputFile, choice;
    cout << "Quel est le nom du fichier que vous voulez corriger?" << endl;
    getline(cin, inputFile);
    cout << "Quel est le nom du fichier de sortie?" << endl;
    getline(cin, outputFile);
    cout << "Quelle methode voulez-vous utiliser? (1:STL, 2:TST)" << endl;
    getline(cin, choice);
    checkText(inputFile, outputFile, "dictionary.txt", choice);
    return 0;
}
