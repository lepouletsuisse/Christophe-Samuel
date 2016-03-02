/*
 * Laboratoire: 06
 * Fichier    : WordDictionnary.h
 * Auteurs    : Samuel Darcey et Christophe Peretti
 * Date       : 16 janvier 2016
 * But        :
 * Remarque(s):
 * Compilateur: MinGW-g++ 4.8.1
 */
#ifndef LABO6_BIS_WORDDICTIONNARY_H
#define LABO6_BIS_WORDDICTIONNARY_H

#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Util.h"




class WordDictionnary{
private:
    std::unordered_set<std::string> dic;
    std::unordered_multimap<std::string, Correction> wrongWords;
public:
    WordDictionnary(std::string file);
    bool isCorrect(std::string word);
    std::vector<Correction> getCorrection(std::string word);
    void generateErrorMore(std::string word);
    void generateErrorWrong(std::string word);
    void generateErrorSwap(std::string word);
    void generateErrorForgetSpecialChar(std::string word);
    bool wrongWordAlreadyExist(std::string word, Correction cor);
};



#endif //LABO6_BIS_WORDDICTIONNARY_H
