/*
 * File:   DirectedCycle.h
 * Author: Olivier Cuisenaire
 * Created on 08. octobre 2014, 10:46
 *
 * A implementer
 * Classe permettant la detection de cycle sur un graphe oriente
 */

#ifndef ASD2_DirectedCycle_h
#define ASD2_DirectedCycle_h

#include <vector>

template<typename GraphType>
class DirectedCycle {
private:
	GraphType graph;
	std::vector<bool> empiles;
	std::vector<bool> marques;

	std::list<int> listeCycles;

public:
	//constructeur
	DirectedCycle(const GraphType& g) {
		graph = g;
		empiles.resize(g.V());
		marques.resize(g.V());
		empiles.assign(empiles.size(), false);
		marques.assign(marques.size(), false);
		listeCycles = Cycle();

	}
	
	//indique la presence d'un cycle
	bool HasCycle() {
		return !listeCycles.empty();
	}
	
	//liste les indexes des sommets formant une boucle
	std::list<int> Cycle() {

	}

	bool detectCycle(int v){
		std::list<int> static histoCycle;
		histoCycle.push_back(v);
		bool trouveCycle = false;
		empiles.at(v) = true;
		marques.at(v) = true;
		for (int w : graph->adjacent(v)){
			if (trouveCycle){
				return true;
			}
			else if (!marques.at(w)){
				detectCycle(w);
			}
			else if(empiles.at(w)){
				trouveCycle = true;
			}
		}
		empiles.at(v) = false;
		return false;
	}
	
};

#endif
