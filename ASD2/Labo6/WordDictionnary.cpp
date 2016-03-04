/*
 * Laboratoire: 06
 * Fichier    : WordDictionnary.cpp
 * Auteurs    : Samuel Darcey et Christophe Peretti
 * Date       : 16 janvier 2016
 * But        :
 * Remarque(s):
 * Compilateur: MinGW-g++ 4.8.1
 */
#include "WordDictionnary.h"

WordDictionnary::WordDictionnary(std::string file) {
    std::ifstream f;
    std::string word;

    //Open the stream
    f.open(file, std::ifstream::in);
    if (!f.is_open()) {
        std::cout << "Error while opening the dictionnary! Abort" << std::endl;
        exit(1);
    }

    //Load the dictionary
    std::cout << "Loading dictionary..." << std::endl;
    while (std::getline(f, word)) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        this->dic.insert(word);
    }
    std::cout << "Dictionary loaded!" << std::endl;

    //Create all the ERROR_FORGET for optimisations
    std::cout << "Creating ERROR_FORGET words..." << std::endl;
    for (std::string s : this->dic) {
        for (unsigned int i = 0; i < s.size(); i++) {
            this->wrongWords.insert({std::string(s).erase(i, 1), Correction(s, ErrorCode::ERROR_FORGET)});
        }
    }
    std::cout << "ERROR_FORGET words created!" << std::endl;
};

bool WordDictionnary::isCorrect(std::string word) {
    if (dic.find(word) == dic.end()) {
        return false;
    };
    return true;
}

std::vector<Correction> WordDictionnary::getCorrection(std::string word) {
    std::vector<Correction> resultat;
    char generation[] = {1, 1, 1};
    if (isCorrect(word)) return resultat;

    //Test if we already generate this kind of error (There will be some undetected case)
    auto rang = wrongWords.equal_range(word);
    for (auto it = rang.first; it != rang.second; it++) {
        if (it->second.error == ErrorCode::ERROR_MORE) generation[0] = 0;
        else if (it->second.error == ErrorCode::ERROR_WRONG) generation[1] = 0;
        else if (it->second.error == ErrorCode::ERROR_SWAP) generation[2] = 0;
    }
    if (generation[0]) generateErrorMore(word);
    if (generation[1]) generateErrorWrong(word);
    if (generation[2]) generateErrorSwap(word);
    generateErrorForgetSpecialChar(word);

    rang = wrongWords.equal_range(word);
    for (auto it = rang.first; it != rang.second; it++) {
        resultat.push_back(it->second);
    }
    return resultat;
}

//Generate the error when ther is a extra letter
void WordDictionnary::generateErrorMore(std::string word) {
    for (int i = 0; i < word.size(); i++) {
        if (isCorrect(std::string(word).erase(i, 1))) {
            std::string correctWord(word);
            correctWord.erase(i, 1);
            Correction cor(correctWord, ErrorCode::ERROR_MORE);
            if (!wrongWordAlreadyExist(word, cor))this->wrongWords.insert({word, cor});
        }
    }
}

//Generate the error when a letter is wrong
void WordDictionnary::generateErrorWrong(std::string word) {
    for (unsigned int i = 0; i < word.size(); i++) {
        std::string tmpWord(word);
        for (char c = 'a'; c <= 'z'; c++) {
            tmpWord.replace(i, 1, 1, c);
            if (isCorrect(tmpWord)) {
                Correction cor(tmpWord, ErrorCode::ERROR_WRONG);
                if (!wrongWordAlreadyExist(word, cor))this->wrongWords.insert({word, cor});
            }
        }
        if (isCorrect(tmpWord.replace(i, 1, 1, '\''))) {
            Correction cor(tmpWord, ErrorCode::ERROR_WRONG);
            if (!wrongWordAlreadyExist(word, cor))this->wrongWords.insert({word, cor});
        }
    }
}

//Generate the error when 2 letters has been swapped
void WordDictionnary::generateErrorSwap(std::string word) {
    for (unsigned int i = 1; i < word.size() - 1; i++) {
        std::string tmpWord(word);
        char c = tmpWord.at(i);
        if (isCorrect(tmpWord.replace(i, 1, 1, tmpWord.at(i + 1)).replace(i + 1, 1, 1, c))) {
            Correction cor(tmpWord, ErrorCode::ERROR_SWAP);
            if (!wrongWordAlreadyExist(word, cor)) this->wrongWords.insert({word, cor});
        }
        tmpWord.replace(i + 1, 1, 1, tmpWord.at(i)).replace(i, 1, 1, c);
        if (isCorrect(tmpWord.replace(i, 1, 1, tmpWord.at(i - 1)).replace(i - 1, 1, 1, c))) {
            Correction cor(tmpWord, ErrorCode::ERROR_SWAP);
            if (!wrongWordAlreadyExist(word, cor))this->wrongWords.insert({word, cor});
        }
    }
}

//Generate special Error like missing a space between 2 words
void WordDictionnary::generateErrorForgetSpecialChar(std::string word) {
    for (unsigned int i = 0; i < word.size(); i++) {
        std::string tmpWord(word);
        std::string subTmpFirst(word.substr(0, i + 1));
        std::string subTmpSecond(word.substr(i + 1));
        if(isCorrect(subTmpFirst) && isCorrect(subTmpSecond)){
            Correction cor(std::string(subTmpFirst + " " + subTmpSecond), ErrorCode::ERROR_FORGET);
            if (!wrongWordAlreadyExist(word, cor))this->wrongWords.insert({word, cor});
        }
    }
}

//Test if the wrong word already exist with the Correction cor
bool WordDictionnary::wrongWordAlreadyExist(std::string word, Correction cor) {
    auto rang = wrongWords.equal_range(word);
    for (auto it = rang.first; it != rang.second; it++) {
        if (it->second.word == cor.word && it->second.error == cor.error) return true;
    }
    return false;
}
