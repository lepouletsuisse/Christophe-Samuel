//
// Created by Christophe on 15.01.2016.
//

#include "TST.h"

    void TST::put(std::string key, Word val){
        root = put(root, key, val, 0);
    }
    Node* TST::put(Node** x, std::string key, Word val, int d){
            char c = key.charAt(d);
            if (x == nullptr) {
                x = new Node(); x->c = c;
            }
            if (c < x->c)
                x->left = put(x->left, key, val, d);
            else if (c > x->c)
                x->right = put(x->right, key, val, d);
            else if (d < key.length() - 1)
                x->mid = put(x->mid, key, val, d+1);
            else
                x->val = val;
            return x;
        }

    bool TST::contains(std::string key){
        return get(key) != nullptr;
    }

    Word TST::get(std::string key){
        Node x = get(root, key, 0);
        if (x == nullptr) return nullptr;
        return x.val;
    }
    Node* TST::get(Node* x, std::string key, int d){
        if (x == nullptr) return nullptr;
        char c = key.charAt(d);
        if (c < x->c) return get(x->left, key, d);
        else if (c > x->c) return get(x->right, key, d);
        else if (d < key.length() - 1) return get(x->mid, key, d+1);
        else return x;
    }
};