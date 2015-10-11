/*
 * File:   TopologicalSort.h
 * Author: Olivier Cuisenaire
 *
 * Created on 08. octobre 2014, 14:07
 *
 * Modifié par Samuel Darcey & Christophe Peretti
 *
 * Classe permettant le tri topologique d'un graphe oriente
 */

#ifndef ASD2_TopologicalSort_h
#define ASD2_TopologicalSort_h

#include "DirectedCycle.h"
#include "ParcoursEnProfondeur.h"

template < typename GraphType >
class TopologicalSort {
private:
    DirectedCycle<DiGraph> DG;
	std::vector<int> ordre;
public:
	//constructeur
	TopologicalSort(const GraphType & g) : DG(g){
		if(IsDAG()){

            //On effectue le parcours uniquement si aucun cycle n'a été trouvé
            DFSIter<DiGraph> DFS(g);
            //On visite le graphe en ne faisant aucune opération dans le pré-ordre, mais on rempli
            //un vecteur avec les sommets dans le post-ordre
			DFS.visitGraph([](int v) {}, [&](int v) { ordre.push_back(v); } );

        } else {
            //Si le graphe n'est pas un DAG, on récupère la liste des sommets
			ordre = DG.getListeCycle();
		}
	}
	
	//indique si le graphe est DAG (Directed Acyclic Graph))
	bool IsDAG() {
        return !DG.hasCycle();
	}
	
	//tableau contenant l'ordre de parcours des indexes des sommets dans le graphe
	const std::vector<int>& Order() {
		return ordre;
	}
};

#endif
