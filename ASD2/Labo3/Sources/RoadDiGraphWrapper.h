//
// Created by Christophe on 15.11.2015.
//

#ifndef LABO3_ROADDIGRAPHWRAPPER_H
#define LABO3_ROADDIGRAPHWRAPPER_H

#include "RoadNetwork.h"
#include "EdgeWeightedDiGraph.h"
#include <list>
#include <functional>

class RoadDiGraphWrapper {
public:
    // Type des arcs/arêtes.
    typedef WeightedDirectedEdge<double> Edge;

    //typedef double WeightType;
    // Type de donnée pour les poids
    typedef typename Edge::WeightType WeightType;

    // Type pour une liste d'arcs/arêtes
    typedef std::vector<Edge> EdgeList;
private:

    RoadNetwork rn;
    std::function<WeightType (int)> weightFunc;

public:

    RoadDiGraphWrapper(const RoadNetwork& roadNetwork, std::function<WeightType (int)> func):rn(roadNetwork), weightFunc(func) { }

    // Renvoie le nombre de sommets V
    int V() const{
        return int(rn.cities.size());
    }

    // Parcours de toutes les arêtes du graphe.
    // la fonction f doit prendre un seul argument de type
    // EdgeWeightedGraph::Edge
    template<typename Func>
    void forEachEdge(Func f) const  {
        int v1, v2, v3;
        for(int v = 0; v < this->V(); ++v)
            for(int road : rn.cities.at(v).roads){
                v1 = rn.roads.at(road).cities.first;
                v2 = rn.roads.at(road).cities.second;
                v3  = (v1 == v ? v2 : v1);
                if(v3 >= v)
                    f(Edge(v1,v2,weightFunc(road)));
            }
    }

    // Parcours des arcs/arêtes adjacentes au sommet v.
    // la fonction f doit prendre un seul argument de type
    // EdgeWeightedGraphCommon::Edge
    template<typename Func>
    void forEachAdjacentEdge(int v, Func f) const  {
        int v1, v2;
        for(int road : rn.cities.at(v).roads){
            v1 = rn.roads.at(road).cities.first;
            v2 = rn.roads.at(road).cities.second;
            f(Edge(v1,v2,weightFunc(road)));
        }
    }
};
#endif //LABO3_ROADDIGRAPHWRAPPER_H
