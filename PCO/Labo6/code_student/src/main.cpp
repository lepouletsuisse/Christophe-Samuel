#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define ITEMTYPE int

#define MATRIXSIZE 500
#define NBTHREADS  4
#define NBBLOCKSPERROW 10

#include "multipliertester.h"
#include "multiplierthreadedtester.h"

using namespace std;

int main (int /*argc*/, char **/**argv[]*/)
{

    char input;
    int choice = -1;

    while(choice == -1){
        cout << "Quel test voulez vous réalisez? 0 = Test simple, 1 = Test reentrant, 2 = Les 2 tests: ";
        cin >> input;
        if(input == '0'){
            choice = 0;
        }else if(input == '1'){
            choice = 1;
        }else if(input == '2'){
            choice = 2;
        }else{
            cout << "Mauvaise entree! Veuillez rechoisir..." << endl;
        }
    }

    if (choice == 1 || choice == 2)
    {
        MultiplierThreadedTester<ITEMTYPE> tester(NBTHREADS);

        tester.test(MATRIXSIZE,NBBLOCKSPERROW);
    }
    if (choice == 0 || choice == 2)
    {
        MultiplierTester<ITEMTYPE> tester;

        tester.test(MATRIXSIZE,NBTHREADS,NBBLOCKSPERROW);
    }

    return 0;
}
