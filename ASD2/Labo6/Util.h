/* 
 * Laboratoire: 06
 * Fichier    : Util.h
 * Auteurs    : Samuel Darcey et Christophe Peretti
 * Date       : 16 janvier 2016
 * But        :
 * Remarque(s):
 * Compilateur: MinGW-g++ 4.8.1
 */

#ifndef UTIL_H
#define	UTIL_H

enum ErrorCode{ERROR_MORE =1, ERROR_FORGET, ERROR_WRONG, ERROR_SWAP};

struct Correction{
    Correction(){};
    Correction(std::string s, ErrorCode e){
        word = s;
        error = e;
    };

    std::string word;
    ErrorCode error;
};

class Node {
public:
    char data;
    bool isCorrect;
    std::vector<Correction> vectCor;
    Node *left, *eq, *right;

    Node(char data, bool corr, bool complete, Correction correction){
        this->data = data;
        this->isCorrect = corr;
        // On insert la correction uniquement lorsque le mot est complet et que le mot vient du dico
        if (!corr && complete){
            this->vectCor.push_back(correction);
        }
        this->left = this->eq = this->right = NULL;
    }
};

#endif

