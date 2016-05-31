#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define ITEMTYPE int

#define MATRIXSIZE 500
#define NBTHREADS  4
#define NBBLOCKSPERROW 5

#include "multipliertester.h"
#include "multiplierthreadedtester.h"


int main (int /*argc*/, char **/**argv[]*/)
{
    bool testReentrant = false;
    bool testSimple   = true;

    if (testReentrant)
    {
        MultiplierThreadedTester<ITEMTYPE> tester(NBTHREADS);

        tester.test(MATRIXSIZE,NBBLOCKSPERROW);
    }
    if (testSimple)
    {
        MultiplierTester<ITEMTYPE> tester;

        tester.test(MATRIXSIZE,NBTHREADS,NBBLOCKSPERROW);
    }

    return 0;
}
