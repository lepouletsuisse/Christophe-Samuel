/*
 * Laboratoire: 06
 * Fichier    : Tst.h
 * Auteurs    : Samuel Darcey et Christophe Peretti
 * Date       : 16 janvier 2016
 * But        :
 * Remarque(s):
 * Compilateur: MinGW-g++ 4.8.1
 */
#ifndef LABO6_TST_H
#define LABO6_TST_H


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include "Util.h"



class Tst {
private:
    struct Node* root;
public:
    Tst (std::string file);
    void insert(struct Node **root, const char *word, bool corr, Correction correct);

    Node* get(const char *word);

    Node* get(Node *current, const char *word);

    void correction(std::string wrongWord);

    std::vector<Correction> getCorrection(std::string word);

    void generateErrorMore(std::string word);

    void generateErrorWrong(std::string word);

    void generateErrorSwap(std::string word);

    void generateErrorForgetSpecialChar(std::string word);

    bool wrongWordAlreadyExist(std::string word, Correction cor);

    void insertOrUpdate(Correction cor, std::string word, std::string wrongWord);
};

#endif //LABO6_TST_H
