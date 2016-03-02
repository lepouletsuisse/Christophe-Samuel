/*
 * Laboratoire: 06
 * Fichier    : check.cpp
 * Auteurs    : Samuel Darcey et Christophe Peretti
 * Date       : 16 janvier 2016
 * But        :
 * Remarque(s):
 * Compilateur: MinGW-g++ 4.8.1
 */
#include "check.h"

//Output the test in the console if 0, nothing otherwise
const char silentMode = 1;

void checkText(std::string inputFile, std::string outputFile, std::string dictionary, std::string choice) {
    std::ifstream inputF, outputF;
    std::string word;
    std::chrono::high_resolution_clock::duration time1;
    std::chrono::high_resolution_clock::time_point start2;

    //Open the input stream
    inputF.open(inputFile, std::ifstream::in);
    if (!inputF.is_open()) {
        std::cout << "Error while opening the input file! Abort" << std::endl;
        exit(1);
    }
    std::cout << "Input file opened!" << std::endl;

    //Open the output stream
    outputF.open(outputFile, std::ofstream::out | std::ofstream::trunc);
    if (!outputF.is_open()) {
        std::cout << "Error while opening the output file! Abort" << std::endl;
        exit(1);
    }
    std::cout << "Output file opened!" << std::endl;


    char c;
    std::chrono::high_resolution_clock::time_point start1 = std::chrono::high_resolution_clock::now();
    if (choice == "1"){
        WordDictionnary w(dictionary);
        time1 = std::chrono::high_resolution_clock::now() - start1;
        std::cout << "Start the treatment of the text..." << std::endl;
        start2 = std::chrono::high_resolution_clock::now();
        do {
            c = tolower(inputF.get());
            if (!isalpha(c) && c != '\'') {
                if (!silentMode) std::cout << "Testing: " << word << std::endl;
                if (!w.isCorrect(word) && word.size() > 1) {
                    std::vector<Correction> v = w.getCorrection(word);

                    //Redirect output buffer to output file
                    std::streambuf *coutBuffer = std::cout.rdbuf();
                    std::cout.rdbuf(outputF.rdbuf());

                    std::cout << "*" << word << std::endl;
                    for (Correction cor : v) {
                        std::cout << cor.error << ":" << cor.word << std::endl;
                    }
                    std::cout << std::endl;
                    //Redirect output buffer to output console
                    std::cout.rdbuf(coutBuffer);
                }
                word.clear();
            }
            else {
                word.append(1, c);
            }
        } while (c != -1);
    } else {
        Tst tst(dictionary);
        time1 = std::chrono::high_resolution_clock::now() - start1;
        std::cout << "Start the treatment of the text..." << std::endl;
        start2 = std::chrono::high_resolution_clock::now();
        do {
            c = tolower(inputF.get());
            if (!isalpha(c) && c != '\'') {
                if (!silentMode) std::cout << "Testing: " << word << std::endl;
                Node* ptr = tst.get(word.c_str());
                if ((!ptr || ptr && !(ptr->isCorrect)) && word.size() > 1) {
                    tst.correction(word);
                    std::vector<Correction> v;
                    ptr = tst.get(word.c_str());
                    if(ptr) {
                        v = tst.getCorrection(word);
                    }
                    //Redirect output buffer to output file
                    std::streambuf *coutBuffer = std::cout.rdbuf();
                    std::cout.rdbuf(outputF.rdbuf());

                    std::cout << "*" << word << std::endl;
                    for (Correction cor : v) {
                        std::cout << cor.error << ": " << cor.word << std::endl;
                    }
                    std::cout << std::endl;
                    //Redirect output buffer to output console
                    std::cout.rdbuf(coutBuffer);


                }
                word.clear();
            }
            else {
                word.append(1, c);
            }
        } while (c != -1);
    }
    std::chrono::high_resolution_clock::duration time2 = std::chrono::high_resolution_clock::now() - start2;
    double totalSeconds1 = (double)std::chrono::duration_cast<std::chrono::microseconds>(time1).count()/1000000;
    double totalSeconds2 = (double)std::chrono::duration_cast<std::chrono::microseconds>(time2).count()/1000000;

    std::cout << "Dictionary + pre-treating done in " << totalSeconds1 << " seconds." << std::endl;

    std::cout << "Treatment of the text done in " << totalSeconds2 << " seconds." << std::endl;
}