//
//  AVLTree_labo5.h
//  SearchTrees
//
//  Created by Olivier Cuisenaire on 25.11.14.
//  Copyright (c) 2014 Olivier Cuisenaire. All rights reserved.
//  Modifié par Samuel Darcey et Christophe Peretti
//

#ifndef SearchTrees_AVLTree_h
#define SearchTrees_AVLTree_h

#include <algorithm>
#include <stack>

template < typename KeyType, typename ValueType >
class AVLTree {
private:
    
    //
    // Noeuds de l'arbre. contient une cle, une valeur, et les liens vers les
    // sous-arbres droit et gauche.
    //
    struct Node {
    public:
        KeyType key;
        ValueType value;
        Node* right; // sous arbre avec des cles plus grandes
        Node* left;  // sous arbre avec des cles plus petites
        int nodeSize; // taille du sous-arbre dont ce noeud est la racine.
        int nodeHeight; // hauteur du sous-arbre dont ce noeud est la racine.
        Node(KeyType key, ValueType value) : key(key),value(value), right(nullptr), left(nullptr), nodeSize(1), nodeHeight(0) { }
    };
    
    //
    // Racine de l'arbre.
    //
    Node* root;
    
    // HELPER: Methode aide pour le methodes d'effacement. Efface del et retourne ret.
    Node* deleteAndReturn( Node* del, Node* ret) {
        delete del;
        return ret;
    }
    // HELPER: Mise à jour de la taille d'un sous-arbre à partir des taille de ses enfants
    void updateNodeSize(Node* x) {
        x->nodeSize = size(x->right) + size(x->left) + 1;
    }
    // HELPER: Mise à jour de la hauteur d'un sous-arbre à partir des hauteurs de ses enfants
    void updateNodeHeight(Node* x) {
        x->nodeHeight = std::max(height(x->right),height(x->left)) + 1;
    }
    
private:
    //
    // AVL: rotation droite avec mise à jour des tailles et hauteurs
    //
    Node* rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        
        y->nodeSize = x->nodeSize;
        updateNodeSize(x);
        
        updateNodeHeight(x);
        updateNodeHeight(y);
        return y;
    }
    
    //
    // AVL: rotation gauche avec mise à jour des tailles et hauteurs
    //
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        
        y->nodeSize = x->nodeSize;
        updateNodeSize(x);
        
        updateNodeHeight(x);
        updateNodeHeight(y);
        return y;
    }
    
    
    //
    // Constructeur. La racine est vide
    //
public:
    AVLTree() : root(nullptr) { }
    
    
    //
    // Destructeur.
    //
public:
    ~AVLTree() {
        deleteSubTree( root );
    }
private:
    void deleteSubTree(Node* x) {
        if( x == nullptr) return;
        deleteSubTree( x->right );
        deleteSubTree( x->left );
        delete x;
    }
    
    //
    // Nombre d'elements
    //
public:
    int size() {
        return size(root);
    }
private:
    int size(Node* x) {
        return ( x == nullptr ) ? 0 : x->nodeSize;
    }
    
    //
    // Insertion d'une paire cle / valeur.
    //
public:
    void put( const KeyType& key, const ValueType& value) {
        root = put(root,key,value);
    }
    
private:
    Node* put(Node* x, const KeyType& key, const ValueType& value) {
        std::stack<Node**> pileNoeuds;
        Node ** ptrActuel = &x;     // double pointeur pour avoir une longueur d'avance sur le noeud

        // On boucle tant que l'on ne se trouve pas sur un pointeur nul (ou qu'on a trouvé la valeur, voir dans la boucle)
        while (*ptrActuel) {
            // On empile les noeuds pour garder la trace de tous les noeuds parcourus (pour pouvoir rééquilibrer)
            pileNoeuds.push(ptrActuel);
            if (key < (*ptrActuel)->key) {
                ptrActuel = &(*ptrActuel)->left;
            } else if (key > (*ptrActuel)->key){
                ptrActuel = &(*ptrActuel)->right;
            } else {
                // Si la clé était déjà présente, on remplace juste la valeur
                (*ptrActuel)->value = value;
                break;
            }
        }
        // Dans le cas où la clé n'était pas présente, on créé le noeud
        if (*ptrActuel == nullptr){
            *ptrActuel = new Node(key,value);
        }

        // On parcoure la pile pour rééquilibrer l'arbre
        while(!pileNoeuds.empty()){
            ptrActuel = pileNoeuds.top();
            pileNoeuds.pop();
            updateNodeSize(*ptrActuel);
            *ptrActuel = restoreBalance(*ptrActuel);
        }
        return x;
    }
    
    //
    // AVL: calcul et restoration de l'équilibre d'un noeud.
    //
    int balance(Node* x) {
        if(x==nullptr) return 0;
        return height(x->left) - height(x->right);
    }
    Node* restoreBalance(Node* x) {
        
        if(balance(x) < -1) // left < right-1
        {
            if (balance(x->right)>0)
                x->right = rotateRight( x->right );
            x = rotateLeft(x);
        }
        else if( balance(x) > 1) // left > right+1
        {
            if ( balance(x->left) < 0 )
                x->left = rotateLeft( x->left );
            x = rotateRight(x);
        }
        else updateNodeHeight(x);
        return x;
    }
    
    //
    // Recherche d'une cle. Renvoie true et modifie
    // value si la cle est trouvee. Renvoie false et
    // ne modifie pas value sinon.
    //
public:
    bool get( const KeyType& key, ValueType& value ) {
        Node* x = root;
        while ( x != nullptr ) {
            if ( key < x->key )
                x = x->left;
            else if ( key > x->key)
                x = x->right;
            else // x->key == key.
            {
                value = x->value;
                return true;
            }
        }
        return false;
    }
    
    //
    // idem précédent, mais sans retour de la valeur
    //
    bool contains( const KeyType& key ) {
        Node* x = root;
        while ( x != nullptr ) {
            if ( key < x->key )
                x = x->left;
            else if ( key > x->key)
                x = x->right;
            else // x->key == key.
                return true;
        }
        return false;
    }
    
    
    //
    // Profondeur de l'arbre.
    //
public:
    int height()
    {
        return height(root);
    }
private:
    int height(Node* x) {
        if ( x == nullptr )
            return -1;
        return x->nodeHeight;
    }
    
    
    //
    // Efface le plus petit element de l'arbre.
    //
public:
    void deleteMin() {
        if (root != nullptr) {
            root = deleteMin(root);
        }
    }
private:
    Node* deleteMin(Node* x) {
        if (x->left == nullptr)
            return deleteAndReturn( x, x->right );
        x->left = deleteMin(x->left);
        x->nodeSize--;
        return restoreBalance(x);
    }
    
    
    //
    // Efface le plus grand element de l'arbre.
    //
public:
    void deleteMax() {
        if (root != nullptr) {
            root = deleteMin(root);
        }
    }
private:
    Node* deleteMax(Node* x) {
        if (x->right == nullptr)
            return deleteAndReturn( x, x->left );
        x->left = deleteMin(x->right);
        x->nodeSize--;
        return restoreBalance(x);
    }
    
    
    //
    // Efface l'element de cle key
    //
public:
    void deleteElement( const KeyType& key) {
        root = deleteElement( root, key );
    }
private:
    Node* deleteElement( Node* x, const KeyType& key) {
        std::stack<Node**> pileNoeuds;
        Node ** ptrActuel = &x;

        while (*ptrActuel) {
            // On empile les noeuds pour garder la trace de tous les noeuds parcourus (pour pouvoir rééquilibrer)
            pileNoeuds.push(ptrActuel);
            if (key < (*ptrActuel)->key) {
                ptrActuel = &(*ptrActuel)->left;
            } else if (key > (*ptrActuel)->key){
                ptrActuel = &(*ptrActuel)->right;
            } else {
                if ((*ptrActuel)->right == nullptr ){
                    if ((*ptrActuel)->left == nullptr ){
                        // Cas où les deux enfants sont nuls
                        delete (*ptrActuel);
                        (*ptrActuel) = nullptr;
                        // On dépile le dernier élément qui est désormais nul et ne nécessite pas de rééquilibrage
                        pileNoeuds.pop();
                        break;
                    } else {
                        // S'il y a un enfant à droite, on va supprimer le plus petit et
                        // mettre sa clé et sa valeur à la place de notre noeud
                        Node* y = max((*ptrActuel)->left);
                        (*ptrActuel)->key = y->key;
                        (*ptrActuel)->value = y->value;
                        (*ptrActuel)->left = deleteMax((*ptrActuel)->left);
                        break;
                    }
                } else {
                    // Sinon, s'il y a un enfant à gauche, on va supprimer le plus grand et
                    // mettre sa clé et sa valeur à la place de notre noeud
                    Node* y = min((*ptrActuel)->right);
                    (*ptrActuel)->key = y->key;
                    (*ptrActuel)->value = y->value;
                    (*ptrActuel)->right = deleteMin((*ptrActuel)->right);
                    break;
                }
            }
        }

        // On parcoure la pile pour rééquilibrer l'arbre
        while(!pileNoeuds.empty()){
            ptrActuel = pileNoeuds.top();
            pileNoeuds.pop();
            updateNodeSize(*ptrActuel);
            *ptrActuel = restoreBalance(*ptrActuel);
        }
        return x;
    }
    
    //
    // Visite de l'arbre par ordre croissant de cle
    //
public:
    template < typename Fn >
    void visitInOrder ( Fn f) {
        if ( root != nullptr)
            visitInOrder(root,f);
    }
private:
    template < typename Fn >
    void visitInOrder ( Node* x, Fn f) {
        if ( x->left != nullptr)
            visitInOrder(x->left,f);
        
        f( x->key, x->value );
        
        if ( x->right != nullptr)
            visitInOrder(x->right,f);
    }
    
    
    //
    // Renvoie la cle la plus petite de l'arbre
    //
public:
    KeyType min() {
        return min(root)->key;
    }
private:
    Node* min(Node* x) {
        if( x->left == nullptr )
            return x;
        return min(x->left);
    }
    
    //
    // Renvoie la cle la plus grande de l'arbre
    //
public:
    KeyType max() {
        return max(root)->key;
    }
private:
    Node* max(Node* x) {
        if( x->right == nullptr )
            return x;
        return max(x->right);
    }
    
    
    //
    // Renvoie le rang (nombre de cles plus petites) d'une cle
    //
public:
    int rank(const KeyType& key) {
        return rank(root, key);
    }
private:
    int rank(Node* x, const KeyType& key) {
        if ( x == nullptr ) return 0;
        
        if ( key < x->key )
            return rank( x->left, key);
        else if ( key > x->key )
            return 1 + size(x->left) + rank( x->right, key);
        else return size(x->left);
    }
};


#endif
