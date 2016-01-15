//
// Created by Christophe on 15.01.2016.
//

#ifndef LABO6_TST_H
#define LABO6_TST_H

#include <string>
#include <vector>

enum class ERROR_WORD{ CORRECT, ERROR_1, ERROR_2, ERROR_3, ERROR_4 };

class Word{
    ERROR_WORD e;
    std::string word;
};

class Node {
public:
    std::vector<Word> vw;
    char c;
    Node *left, *mid, *right;
    Node(char val){
        c = val;
        left = right = mid = nullptr;
    }
};

class TST {
private:
    Node* root;
public :
    void put(std::string key, Word val);
    Node* put(Node* x, std::string key, Word val, int d);

    bool contains(std::string key);

    Word get(std::string key);
    Node* get(Node* x, std::string key, int d);
};
#endif //LABO6_TST_H
