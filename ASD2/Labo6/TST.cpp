/*
 * Laboratoire: 06
 * Fichier    : TST.cpp
 * Auteurs    : Samuel Darcey et Christophe Peretti
 * Date       : 16 janvier 2016
 * But        :
 * Remarque(s):
 * Compilateur: MinGW-g++ 4.8.1
 */
#include "TST.h"

Tst::Tst (std::string file){
    std::ifstream f;
    std::string word;

    root = nullptr;

    //Open the stream
    f.open(file, std::ifstream::in);
    if (!f.is_open()) {
        std::cout << "Error while opening the dictionnary! Abort" << std::endl;
        exit(1);
    }


    //Load the dictionary
    std::cout << "Loading dictionary..." << std::endl;

    //Create all the ERROR_FORGET for optimisations
    std::cout << "...And creating ERROR_FORGET words..." << std::endl;

    while (std::getline(f, word)) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        Node* ptr = get(word.c_str());
        if (!ptr){
            insert(&root, word.c_str(), true, Correction());
        } else {
            ptr->isCorrect = true;
        }

        // On créé directement les mots faux à partir du mot courant du dico, car on a pas de liste
        // des mots corrects pour le faire plus tard
        for (unsigned int i = 0; i < word.size(); i++) {
            std::string wrongWord(word);
            wrongWord = wrongWord.erase(i, 1);
            Correction cor(word, ErrorCode::ERROR_FORGET);
            if (wrongWord == "'and")
            std::cout << "mot : " << word << std::endl;
            insertOrUpdate(cor, word, wrongWord);
        }
    }

    std::cout << "Dictionary loaded! " << std::endl;
}
void Tst::insert(Node **root, const char *word, bool corr, Correction correct) {
    if (!(*root)){
        if(*(word + 1)){
            // Si le Noeud n'existe pas et qu'on est pas encore à la fin du mot, on créé le Noeud du mot partiel (donc faux)
            *root = new Node(*word, false, false, correct);
        } else {
            // Mot complet (peut être correct ou non)
            *root = new Node(*word, corr, true, correct);
        }
    }

    if ((*word) < (*root)->data)
        insert(&((*root)->left), word, corr, correct);

    else if ((*word) > (*root)->data)
        insert(&((*root)->right), word, corr, correct);

    else {
        if (*(word + 1)){
            insert(&((*root)->eq), word + 1, corr, correct);
        }
    }
}

Node* Tst::get(const char *word){
    return get(root, word);
}
Node* Tst::get(Node *current, const char *word){
    if (!current){
        return nullptr;
    }
    if (*word < current->data){
        return get(current->left, word);
    } else if (*word > current->data){
        return get(current->right, word);
    } else {
        if (*(word + 1) == '\0'){
            return current;
        }
        return get(current->eq, word + 1);
    }
}
// On génère toutes les erreurs possible à partir du mot faux, pour voir si on tombe sur un mot du dico
void Tst::correction(std::string wrongWord){
    generateErrorMore(wrongWord);
    generateErrorWrong(wrongWord);
    generateErrorSwap(wrongWord);
    generateErrorForgetSpecialChar(wrongWord);
}

std::vector<Correction> Tst::getCorrection(std::string wrongWord) {
    return get(wrongWord.c_str())->vectCor;
}

// Génère les erreurs avec une lettre en moins
void Tst::generateErrorMore(std::string wrongWord) {
    std::string word;
    for (unsigned int i = 0; i < wrongWord.size(); i++) {
        word = wrongWord;
        word = word.erase(i, 1);
        Node* ptr1 = get(word.c_str());
        if(ptr1 && ptr1->isCorrect){
            Correction cor(word, ErrorCode::ERROR_MORE);
            insertOrUpdate(cor, word, wrongWord);
        }
    }
}

// Génère les erreurs avec une lettre à la place d'une autre
void Tst::generateErrorWrong(std::string wrongWord) {
    for (unsigned int i = 0; i < wrongWord.size(); i++) {
        std::string word(wrongWord);
        for (char c = 'a'; c <= 'z'; c++) {
            word.replace(i, 1, 1, c);
            Node* ptr1 = get(word.c_str());
            if (ptr1 && ptr1->isCorrect) {
                Correction cor(word, ErrorCode::ERROR_WRONG);
                insertOrUpdate(cor, word, wrongWord);
            }
        }
        word.replace(i, 1, 1, '\'');
        Node* ptr1 = get(word.c_str());
        if (ptr1 && ptr1->isCorrect) {
            Correction cor(word, ErrorCode::ERROR_WRONG);
            insertOrUpdate(cor, word, wrongWord);
        }
    }
}

// Génère les erreurs avec deux lettres inversées
void Tst::generateErrorSwap(std::string wrongWord) {
    for (unsigned int i = 1; i < wrongWord.size(); i++) {
        std::string word(wrongWord);
        char c = word.at(i);
        word.replace(i, 1, 1, word.at(i - 1)).replace(i - 1, 1, 1, c);
        Node* ptr1 = get(word.c_str());
        if (ptr1 && ptr1->isCorrect) {
            Correction cor(word, ErrorCode::ERROR_SWAP);
            insertOrUpdate(cor, word, wrongWord);
        }
    }
}

// Génère les erreurs avec un espace manquant
void Tst::generateErrorForgetSpecialChar(std::string wrongWord) {
    for (unsigned int i = 0; i < wrongWord.size(); i++) {
        std::string subTmpFirst(wrongWord.substr(0, i + 1));
        std::string subTmpSecond(wrongWord.substr(i + 1));

        Node* ptr1 = get(subTmpFirst.c_str());
        Node* ptr2 = get(subTmpSecond.c_str());

        if (ptr1 && ptr2 && ptr1->isCorrect && ptr2->isCorrect) {
            std::string word = std::string(subTmpFirst + " " + subTmpSecond);
            Correction cor(word, ErrorCode::ERROR_FORGET);
            insertOrUpdate(cor, word, wrongWord);
        }
    }
}

// Vérifie si le mot faux est déjà dans la structure, si c'est le cas on ajoute la correction, sinon on l'insert
void Tst::insertOrUpdate(Correction cor, std::string word, std::string wrongWord){
    Node* ptr2 = get(wrongWord.c_str());
    if(!ptr2){
        insert(&root, wrongWord.c_str(), false, cor);
    } else if(!(ptr2->isCorrect)){
        for(Correction cor: ptr2->vectCor){
            if (cor.word == word){
                return;
            }
        }
        ptr2->vectCor.push_back(cor);
    }
}

