//
//  labo5.cpp
//  AVLTrees
//
//  Created by Olivier Cuisenaire on 24.11.14.
//  Modified by Eric Henchoz on 27.11.15.
//  Copyright (c) 2014 Olivier Cuisenaire. All rights reserved.
//

#include <iostream>
#include <vector>

#include "AVLTree.h"

#include <cmath>
#include <ctime>

using namespace std;

void simpleTest() {
    AVLTree<char, int> bst;
    
    bst.put( 'f', 6 );
    bst.put( 'g', 7 );
    bst.put( 'b', 2 );
    bst.put( 'h', 8 );
    bst.put( 'c', 3 );
    bst.put( 'd', 4 );
    bst.put( 'i', 9 );
    bst.put( 'a', 1 );
    bst.put( 'e', 5 );
    
    cout << "height: " << bst.height() << endl;
    
    bst.visitInOrder([](char k, int v) {
        cout << k << ": " << v << endl;
    });
    
    int minval;
    bst.get( bst.min(), minval);
    
    int maxval;
    bst.get( bst.max(), maxval);
    
    cout << "min key ... " << bst.min() << ": " << minval << endl;
    cout << "max key ... " << bst.max() << ": " << maxval << endl;
    
    cout << "deleteElement('h')" << endl;
    bst.deleteElement('h');
    bst.visitInOrder([](char k, int v) {
        cout << k << ": " << v << endl;
    });
        
    cout << "bst.put( 'a', 1 )" << endl;
    bst.put( 'a', 1 );
    bst.visitInOrder([](char k, int v) {
        cout << k << ": " << v << endl;
    });
    
    cout << "bst.put( 'a', 4 )" << endl;
    bst.put( 'a', 4 );
    bst.visitInOrder([](char k, int v) {
        cout << k << ": " << v << endl;
    });
}

void randomTest() {
    
    clock_t start = clock();
    
    AVLTree<int,int> bst;
    
    const int N = 10000;
    
    for (int i=0; i<N; ++i) {
        bst.put( i , i );
    }
    
    cout << "height after adding " << N << " elements: " << bst.height() << endl;
    cout << "Size after adding " << N << " elements: " << bst.size() << endl;
    
    for (int i=0; i<N / 2; ++i) {
        bst.deleteElement( i );
    }
    
    cout << "height after adding " << N << " elements and removing half: " << bst.height() << endl;
    cout << "Size after adding " << N << " elements and removing half: " << bst.size() << endl;
    
    for (int i=0; i<N; ++i) {
        bst.put( rand() % N , i );
    }
    
    cout << "height after adding " << N << " elements: " << bst.height() << endl;
    cout << "Size after adding " << N << " elements: " << bst.size() << endl;
    
    cout << "Time: " << ( clock()-start ) * 1.0 / CLOCKS_PER_SEC << " sec " << endl;
    
    
    int maxdepth = bst.height();
    
    const int M = 500000;
    
    for( int i = 0; i < M; ++i ) {
        
        
        int el = rand() % N ;
        int val;
        
        if ( bst.get(el,val) )
            bst.deleteElement( el );
        
        bst.put( rand() % N , i );
        
        if( i % (M/20)== 0 ) {
            
            cout << i << "\t" << bst.size() << "\t" << bst.height() << endl;
            
            int height = bst.height();
            if( maxdepth < height) {
                maxdepth = height;
            }
        }
    }
    
    cout << "height after " << M << " delete / put elements: " << bst.height() << endl;
    cout << "Time: " << ( clock()-start ) * 1.0 / CLOCKS_PER_SEC << " sec " << endl;
}

void searchTest() {
    
    clock_t start = clock();
    
    AVLTree<int,int> bst;
    
    const int N = 1000000;
    
    for (int i=0; i<N; ++i) {
        bst.put( rand() % N , i );
    }
    
    cout << "height after adding " << N << " elements: " << bst.height() << endl;
    cout << "Size after adding " << N << " elements: " << bst.size() << endl;
    
    cout << "Time: " << ( clock()-start ) * 1.0 / CLOCKS_PER_SEC << " sec " << endl;
    start = clock();
    
    const int M = 1000000;
    int dummy;
    
    int cnt = 0;
    for( int i = 0; i < M; ++i ) {
        bool test = bst.get(rand() % N , dummy);
        if(test) ++cnt;
    }
    cout << cnt << endl; ;
    
    cout << "Time: for " << M << " searches: " << ( clock()-start ) * 1.0 / CLOCKS_PER_SEC << " sec " << endl;
}

int main() {
    
    simpleTest();
    
    randomTest();
    
    searchTest();
    
    return EXIT_SUCCESS;
}
