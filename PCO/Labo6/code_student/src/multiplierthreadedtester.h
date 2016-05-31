#ifndef MULTIPLIERTHREADEDTESTER_H
#define MULTIPLIERTHREADEDTESTER_H

#include <iostream>
#include <QTime>

#include "matrix.h"
#include "simplematrixmultiplier.h"
#include "threadedmatrixmultiplier.h"


/**
 * This class implements a tester for the multiplier that can launch a certain
 * number of threads that will call multiply in parallel. It allows to validate
 * the fact that multiply is reentrant.
 */
template<class T>
class MultiplierThreadedTester
{

public:

    MultiplierThreadedTester(int nbThreads) : nbThreads(nbThreads)
    {
        threadedMultiplier = new ThreadedMatrixMultiplier<T>(nbThreads);
    }

    ~MultiplierThreadedTester()
    {
        delete threadedMultiplier;
    }

    /**
     * This function is called to start the test. It will launch
     * nbThreads threads to challenge the multiplier in terms
     * of correct way to handle its reentrantness
     */
    void test(int matrixSize, int nbBlocksPerRow)
    {
        int nbT = 2;
        QVector<InsiderThread*> threads;
        for(int i=0;i<nbT;i++) {
            InsiderThread * t = new InsiderThread(this, matrixSize, nbBlocksPerRow);
            threads << t;
            t->start();
        }
        for(int i=0;i<nbT;i++) {
            threads[i]->wait();
        }

    }

protected:

    /**
     * This class represents a thread that will start a full test.
     * Many threads should be launched to kind of prove the
     * reentrantness of the design
     * */
    class InsiderThread : public QThread
    {
        MultiplierThreadedTester *tester;
        int matrixSize;
        int blocksPerRow;

    public:
        InsiderThread(MultiplierThreadedTester *tester, int matrixSize, int blocksPerRow) : tester(tester),
            matrixSize(matrixSize), blocksPerRow(blocksPerRow){}
        void run() Q_DECL_OVERRIDE
        {
            tester->test_int(matrixSize, blocksPerRow);
        }
    };


    int nbThreads;

    //! A single multiplier, used by all threads in parallel
    ThreadedMatrixMultiplier<T> *threadedMultiplier;

    /**
     * This function is quite similar to the one of the MultiplierTester.
     * It is called by each thread.
     */
    void test_int(int matrixSize, int nbBlocksPerRow)
    {

        SquareMatrix<T> A(matrixSize);
        SquareMatrix<T> B(matrixSize);
        SquareMatrix<T> C(matrixSize);
        SquareMatrix<T> C_ref(matrixSize);

        for(int i=0;i<matrixSize;i++) {
            for(int j=0;j<matrixSize;j++) {
                A.setElement(i,j,rand());
                B.setElement(i,j,rand());
                C.setElement(i,j,0);
                C_ref.setElement(i,j,0);
            }
        }

        SimpleMatrixMultiplier<T> multiplier;
        QTime t;
        t.start();
        multiplier.multiply(A,B,&C_ref);
        int timeSimple = t.elapsed();

        t.start();
        threadedMultiplier->multiply(A,B,&C, nbBlocksPerRow);
        int timeThreaded = t.elapsed();

        C.compare(C_ref);

        if (timeThreaded == 0) {
            std::cout << "Time too short, try with a bigger matrix size" << std::endl;
        }
        else {
            double gain = ((double) timeSimple) / ((double) timeThreaded) * 100.0 - 100.0;
            std::cout << "Time gain: " << gain << " % " << std::endl;
        }
    }
};

#endif // MULTIPLIERTHREADEDTESTER_H
