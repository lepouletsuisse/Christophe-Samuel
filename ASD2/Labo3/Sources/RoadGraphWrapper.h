//
// Created by Christophe on 14.11.2015.
//

#ifndef LABO3_ROADGRAPHWRAPPER_H
#define LABO3_ROADGRAPHWRAPPER_H


#include "RoadNetwork.h"
#include "EdgeWeightedGraph.h"
#include <list>
#include <functional>

class RoadGraphWrapper {
public:
    // Type des arcs/ar�tes.
    typedef WeightedEdge<double> Edge;

    //typedef double WeightType;
    // Type de donn�e pour les poids
    typedef typename Edge::WeightType WeightType;

    // Type pour une liste d'arcs/ar�tes
    typedef std::vector<Edge> EdgeList;
private:

    RoadNetwork rn;
    std::function<WeightType (int)> weightFunc;

public:

    RoadGraphWrapper(const RoadNetwork& roadNetwork, std::function<WeightType (int)> func):rn(roadNetwork), weightFunc(func) { }

    // Renvoie le nombre de sommets V
    int V() const{
        return int(rn.cities.size());
    }

    // Parcours de toutes les ar�tes du graphe.
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
};

#endif //LABO3_ROADGRAPHWRAPPER_H
