/* 
 * File:   DiGraph.h
 * Author: Cuisenaire
 *
 * Created on 7. octobre 2014, 16:54
 * 
 * Implementation d'un graphe oriente par liste d'adjacence
 */

#ifndef DIGRAPH_H
#define	DIGRAPH_H

#include <iostream>
#include <list>
#include <vector>

class DiGraph {
public:      
	typedef const std::list<int> & Iterable;

	DiGraph(std::istream& stream); 
	DiGraph(int V);

	void addEdge(int v, int w);              // ajoute une arête
	Iterable adjacent(int v) const;          // voisins du sommet v
	int V() const;                           // ordre du graphe
	
	DiGraph reverse() const;                 // graphe inversé
   
private:        
	std::vector<std::list<int>> adjacencyLists; 
};

#endif	/* DIGRAPH_H */
