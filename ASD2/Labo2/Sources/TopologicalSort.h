/*
 * File:   TopologicalSort.h
 * Author: Olivier Cuisenaire
 *
 * Created on 08. octobre 2014, 14:07
 *
 * A implementer
 * Classe permettant le tri topologique d'un graphe oriente
 */

#ifndef ASD2_TopologicalSort_h
#define ASD2_TopologicalSort_h

#include "DirectedCycle.h"

template < typename GraphType >
class TopologicalSort {
private:
	/* A DEFINIR */

public:
	//constructeur
	TopologicalSort(const GraphType & g) {
		/* A IMPLEMENTER */
		/* vous devez verifier la presence d'un cycle */
	}
	
	//indique si le graphe est DAG (Directed Acyclic Graph))
	bool IsDAG() {
		/* A IMPLEMENTER */
		//return ...
	}
	
	//tableau contenant l'ordre de parcours des indexes des sommets dans le graphe
	const std::vector<int>& Order() {
		/* A IMPLEMENTER */
		//return ...
	}
};

#endif
