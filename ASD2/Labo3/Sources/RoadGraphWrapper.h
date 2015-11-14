//
// Created by Christophe on 14.11.2015.
//

#ifndef LABO3_ROADGRAPHWRAPPER_H
#define LABO3_ROADGRAPHWRAPPER_H
//
// Created by Christophe on 13.11.2015.
//

#include "RoadNetwork.h"
#include "EdgeWeightedGraphCommon.h"
#include <list>

template< typename T>  // type des edges, par exemple DirectedEdge<double> ou Edge<int> ou ...
// T doit définir le type T::WeightType
class RoadGraphWrapper {
public:
    // Type des arcs/arêtes.
    typedef T Edge;

    // Type de donnée pour les poids
    typedef typename Edge::WeightType WeightType;

    // Type pour une liste d'arcs/arêtes
    typedef std::list<Edge> EdgeList;
private:

    RoadNetwork rn;

public:

    RoadGraphWrapper(const RoadNetwork& roadNetwork):rn(roadNetwork) { }

    // Renvoie le nombre de sommets V
    int V(){
        return int(rn.cities.size());
    }

    // Parcours des arcs/arêtes adjacentes au sommet v.
    // la fonction f doit prendre un seul argument de type
    // EdgeWeightedGraphCommon::Edge
    template<typename Func>
    void forEachAdjacentEdge(int v, Func f) const  {
        for(const Edge& e : adjacentEdges(v))
            f(e);
    }

    // Parcours de tous les sommets du graphe.
    // la fonction f doit prendre un seul argument de type int
    template<typename Func>
    void forEachVertex(Func f) const  {
        for(int v = 0; v < V(); ++v)
            f(v);
    }

    // Renvoie une const reference a la list d'arcs/aretes
    // adjacent-es au sommet v
    const EdgeList& adjacentEdges(int v) const {
        EdgeList tmp;
        for(int v : rn.cities.at(v).roads){
            tmp.push_back((T)v);
        }
        return tmp;
    }
};

#endif //LABO3_ROADGRAPHWRAPPER_H
