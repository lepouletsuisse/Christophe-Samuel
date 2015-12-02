//
//  HashTableTester.h
//  ASD2_2015
//
//  Created by Fabien Dutoit on 24.09.15.
//  Copyright © 2015 IICT, HEIG-VD. All rights reserved.
//

#ifndef HashTableTester_h
#define HashTableTester_h

#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <chrono>
#include <list>
#include <unordered_set>

#include "Util.h"

template <typename ElementType>
class HashTableTester {
private:
    std::string filename;
    std::unordered_set<ElementType> set;
    std::list<std::chrono::high_resolution_clock::duration> insertionTimes;
    std::list<std::chrono::high_resolution_clock::duration> searchTimes;
    size_t searchElements;
    size_t foundElements;
    
public:
    
    HashTableTester(const std::string& filename) : filename(filename) {
        
        //we configure the load factor before resizing
        this->set.max_load_factor(MAX_LOAD_FACTOR);
        
        std::string line;
        
        std::ifstream s(this->filename);
        while (std::getline(s, line)) {
            line = trim(line);
            std::vector<std::string> elements = split(line, ';');
            
            //element instantiation
            ElementType dirElement(elements[0], elements[1], elements[2], elements[3], elements[4]);
            
            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
            set.insert(dirElement);
            std::chrono::high_resolution_clock::duration time = std::chrono::high_resolution_clock::now() - start;
            
            //we store the insertion durations
            insertionTimes.push_back(time);
        }
        s.close();
    }
    
    void displayInsertionStats() {
        std::chrono::high_resolution_clock::duration total = std::chrono::high_resolution_clock::duration::zero();
        for(auto duration : this->insertionTimes) {
            total += duration;
        }
        long totalMicroSeconds = std::chrono::duration_cast<std::chrono::microseconds>(total).count();
        double average = ((double) totalMicroSeconds) / this->insertionTimes.size();
        std::cout << "Insertion total:                  " << this->insertionTimes.size() << std::endl;
        std::cout << "Insertion duration total   time:  " << totalMicroSeconds << " microseconds" << std::endl;
        std::cout << "Insertion duration average time:  " << average << " microseconds" << std::endl;
    }
    
    void displayDistributionStats() {
        
        unsigned long nbrElements       = this->set.size();
        unsigned long nbrBucket         = this->set.bucket_count();
        unsigned long nbrCollisions     = 0L;
        unsigned long nbrEmptyBuckets   = 0L;
        unsigned long maxNbrElements    = std::numeric_limits<unsigned long>::min();
        unsigned long minNbrElements    = std::numeric_limits<unsigned long>::max();
        
        for(unsigned long i = 0; i < nbrBucket; ++i) {
            unsigned long bucketSize = this->set.bucket_size(i);
            if(bucketSize > 1)
                nbrCollisions += (bucketSize -1); // more than 1 element in bucket = hash collision
            if(bucketSize == 0)
                ++nbrEmptyBuckets;
            if(bucketSize > maxNbrElements)
                maxNbrElements = bucketSize;
            if(bucketSize < minNbrElements)
                minNbrElements = bucketSize;
            
        }
        
        double percentCollision = 100.0 * ((double)(nbrCollisions)   / nbrElements);
        double percentEmpty     = 100.0 * ((double)(nbrEmptyBuckets) / nbrBucket);
        
        std::cout << "Number of buckets:                " << nbrBucket << std::endl;
        std::cout << "Number of collisions:             " << nbrCollisions << " (" << percentCollision << "%)" << std::endl;
        std::cout << "Number of empty buckets:          " << nbrEmptyBuckets << " (" << percentEmpty << "%)" << std::endl;
        std::cout << "Largest bucket:                   " << maxNbrElements << std::endl;
        std::cout << "Smallest bucket:                  " << minNbrElements << std::endl;
        
    }
    
    void performSearch() {
        
        this->searchElements = 0;
        this->foundElements  = 0;
        
        std::string line;
        
        std::ifstream s(this->filename);
        while (std::getline(s, line)) {
            line = trim(line);
            std::vector<std::string> elements = split(line, ';');
            
            //element instantiation
            ElementType dirElement(elements[0], elements[1], elements[2], elements[3], elements[4]);
            
            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
            bool found = set.find(dirElement) != set.end();
            std::chrono::high_resolution_clock::duration time = std::chrono::high_resolution_clock::now() - start;
            
            //we count the number of elements we found (it should be able to find all of them)
            ++this->searchElements;
            if(found) ++this->foundElements;
            
            //we store the search durations
            searchTimes.push_back(time);
        }
        s.close();
        
    }
   
    void displaySearchStats() {
        std::chrono::high_resolution_clock::duration total = std::chrono::high_resolution_clock::duration::zero();
        for(auto duration : this->searchTimes) {
            total += duration;
        }
        long totalMicroSeconds = std::chrono::duration_cast<std::chrono::microseconds>(total).count();
        double average = ((double) totalMicroSeconds) / this->searchElements;
        double percentFound = 100.0 * ((double)(this->foundElements)   / this->searchElements);
        std::cout << "Search total:                     " << this->searchElements << std::endl;
        std::cout << "Found total:                      " << this->foundElements << " (" << percentFound << "%)"<< std::endl;
        std::cout << "Search duration total   time:     " << totalMicroSeconds << " microseconds" << std::endl;
        std::cout << "Search duration average time:     " << average << " microseconds" << std::endl;
    }
    
};

#endif /* HashTableTester_h */
