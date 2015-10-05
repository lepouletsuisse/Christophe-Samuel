/* 
 * File:   SymbolGraph.h
 * Author: Samuel Darcey & Christophe Peretti
 *
 * Created on 27. septembre 2015
 */

#ifndef SYMBOLGRAPH_H
#define	SYMBOLGRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <list>

#include "Util.h"


template<typename GraphType>
class SymbolGraph
{
    typedef GraphType Graph; 
private:
    Graph* g;
    char delimiteur = ',';
    
public:
    
    ~SymbolGraph()
    {
        delete g; 
    }
    // map pour associer un numéro à chaque film/acteur
    std::map<std::string, int> indices;

    //creation du SymbolGraph a partir du fichier movies.txt
    SymbolGraph(const std::string& filename) {

        //lecture du fichier, ligne par ligne puis element par element (separe par des /)
        std::string line;
        int cnt=0;
        std::ifstream s(filename);

        while (std::getline(s, line)){
            auto names = split(line,delimiteur);
            for( auto name : names ) {
                //Remplie la map si le nom n'y apparait pas déjà
                if (!contains(name)) {
                    indices[name] = cnt++;
                }
            }
        }
        //Création du graphe
        g = new Graph(cnt);

        //Retour au début du fichier
        s.clear();
        s.seekg(0, s.beg);

        //Deuxième lecture du fichier
        while (std::getline(s, line)){
            auto names = split(line,delimiteur);
            for(int i = 1 ; i < names.size() ; i++){
                //On créée les arêtes entre le film et tous ses acteurs
                g->addEdge(index(names.at(0)),index(names.at(i)));
            }
        }
        s.close();
    }
    
    //verifie la presence d'un symbole
    bool contains(const std::string& name) {
        return indices.count(name);
    }
    
    //index du sommet correspondant au symbole
    int index(const std::string& name) {
        return indices[name];
    }
    
    //symbole correspondant au sommet
    std::string name(int idx) {
        for(auto pair : indices){
            if(pair.second == idx){
                return pair.first;
            }
        }
    }

    //symboles adjacents a un symbole
    std::vector<std::string> adjacent(const std::string & str) {
        std::vector<std::string> nomsAdjacents;
        //On va rechercher la liste d'adjacence (par numéro)
        std::list<int> numAdjacents = g->adjacent(index(str));
        std::string nom;

        for(auto i : numAdjacents){
            //On retrouve les noms des films/acteurs correspondant aux numéros et on rempli notre vecteur
            nomsAdjacents.push_back(name(i));
        }
        return nomsAdjacents;

    }
    
    const Graph& G() {
        return *g; 
    }
    
};


#endif	/* SYMBOLGRAPH_H */
