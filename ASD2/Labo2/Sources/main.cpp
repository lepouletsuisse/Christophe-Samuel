/*
 * File:   DFSOrder.h
 * Author: Cuisenaire
 * Labo 2
 * Created on 3. novembre 2014, 08:23
 * Modifié par Samuel Darcey & Christophe Peretti
 */


#include <stdlib.h>
#include <iostream>
#include "DiGraph.h"
#include "TopologicalSort.h"
#include "DirectedCycle.h"

// vous devez reutiliser celui du labo 1, ex 2 (cf. donnee)
#include "Util.h"
#include "SymbolGraph.h"
#include "ParcoursEnProfondeur.h"

using namespace std;

//methode permettant de verifier le graphe trie par rapport au fichier d'entree
bool checkOrder(const std::vector<int>& order,
                const SymbolGraph<DiGraph>& SG,
                const std::string& filename,
                char delim) {

    std::vector<int> positionInOrder(order.size());
    for( size_t i = 0; i < order.size(); ++i )
        positionInOrder[order[i]] = int(i);
    
    bool ok = true;
    
    std::string line;
    
    std::ifstream s(filename);
    while (std::getline(s, line))
    {
        auto names = split(line,delim);
        
        for(size_t i = 1; i < names.size(); ++i) {
         
            int v = SG.index(names[0]); // cours
            int w = SG.index(names[i]); // ieme prerequis
            
            if ( positionInOrder[ v ] < positionInOrder [ w ]) {
                cout << std::endl << "Erreur d'ordre : " << names[0] << " avant " << names[i] << endl;
                ok = false;
            }
        }
    }
    s.close();

    return ok;
}

int main(int argc, const char * argv[]) {

    string fichier("prerequis.txt");
    char delim(',');

    //On crée le graphe (orienté) à partir du fichier
    SymbolGraph<DiGraph> SG(fichier,delim);

    //La classe Topologicalsort se charge de vérifier si le graphe est un DAG ou non
    TopologicalSort<DiGraph> TS(SG.G());

    //Double fonction pour order : si le graphe est un DAG, order contient la liste des sommet du graphe
    //dans l'ordre topologique. Si ce n'est pas le cas, il contient les sommets faisant un cycle.

    std::vector<int> order = TS.Order();

    if (TS.IsDAG()){
        std::cout << fichier << " est un DAG" << std::endl;
        std::cout << "Ordre topologique :" << std::endl;

        for (int i = 0; i < order.size(); i++){
            std::cout << "<" << SG.name(order.at(i)) << ">";
        }

        //Vérification de l'ordre
        if (checkOrder(order, SG, fichier, delim)){
            std::cout << std::endl << "Verification reussie" << std:: endl;
        }
    } else {
        std::cout << fichier << " n'est pas un DAG" << std::endl;
        std::cout << "Cycle trouve :" << std::endl;
        for (int i = 0; i < order.size(); i++){
            std::cout << "<" << SG.name(order.at(i)) << ">";
        }
    }

    return EXIT_SUCCESS;
}
