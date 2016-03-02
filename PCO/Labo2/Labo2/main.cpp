#include <iostream>
#include <vector>
#include "mythread.h"
#include <ctime>
#include <chrono>

using namespace std;
int main(int argc, char *argv[])
{
    if(argc != 3){
        cout << "Erreur d'argument!" << endl;
        return 1;
    }

    std::chrono::high_resolution_clock::duration temps;
    vector<MyThread*> threads;
    uint64_t nombre = stoull(argv[1]);
    int nombreThread = atoi(argv[2]);
    for(int i = 0 ; i < nombreThread ; i++){
        uint64_t debut = floor(i * sqrt(nombre) / nombreThread + 2);
        uint64_t fin = floor((i + 1) * sqrt(nombre) / nombreThread + 2);
        MyThread* thread = new MyThread(debut, fin, nombre);
        cout << "Thread number " << i << " start at " << debut << " and stop at " << fin << endl;
        threads.push_back(thread);
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(int i = 0 ; i < threads.size() ; i++){
        threads.at(i)->start();
    }

    for(int i = 0 ; i < threads.size() ; i++){
        threads.at(i)->wait();
        cout << "Thread " << i << " finished!" << endl;
    }

    temps = std::chrono::high_resolution_clock::now() - start;

    if(notPrime){
        cout << "NOT A PRIME NUMBER!!" << endl;
    }
    else{
        cout << "PRIME NUMBER!!" << endl;
    }
    double totalMS = (double)std::chrono::duration_cast<std::chrono::microseconds>(temps).count()/1000;
    cout << "Done in " << totalMS << "ms" << endl;
    /*Partie  1*/
    /*
    uint64_t nombre;
    nombre = stoull(argv[1]);
    cout << "Vous avez entre " << nombre << endl;
    for(int i = 2 ; i < sqrt(nombre) ; i++){
        if(!(nombre % i)){
            cout << "NOT A PRIME NUMBER!!" << endl;
            return 0;
        }
    }
    cout << "PRIME NUMBER!!" << endl;*/

    /*Partie  2*/

    return 0;
}
