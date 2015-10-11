/*
 * File:   DirectedCycle.h
 * Author: Olivier Cuisenaire
 * Created on 08. octobre 2014, 10:46
 *
 * Modifié par Samuel Darcey & Christophe Peretti
 * Classe permettant la detection de cycle sur un graphe oriente
 */

#ifndef ASD2_DirectedCycle_h
#define ASD2_DirectedCycle_h

#include <vector>

template<typename GraphType>
class DirectedCycle {
private:
	const GraphType& graph;
	std::vector<bool> empiles;
	std::vector<bool> marques;
    bool trouveCycle = false;

    //Historique de tous les sommets parcourus
    //Contient la même chose que empiles, avec l'ordre en plus
    std::list<int> histoCycle;

    //Liste des sommets faisant un cycle
    std::vector<int>listeCycle;

    //Premier sommet d'un cycle
    int sommetCycle;

public:
	//constructeur
	DirectedCycle(const GraphType& g) : graph(g){
		empiles.resize(g.V());
		marques.resize(g.V());

        empiles.assign(empiles.size(), false);
        marques.assign(marques.size(), false);

        //Début de la détection de cycles
        Cycle();
	}
	
	//Indique la presence d'un cycle
	bool hasCycle() {
		return trouveCycle;
	}
	
	//liste les indexes des sommets formant une boucle
	void Cycle() {
        int i = 0;
        //On parcoure le graphe à partir de tous les sommets (ou jusqu'à ce qu'on ait trouvé un cycle
		do{
			detectCycle(i++);
		} while(!trouveCycle && i < graph.V());

        if(trouveCycle){

            //On reparcoure la liste de tous les sommets afin de créer un vector à partir de la liste
            for (std::list<int>::iterator pos = histoCycle.begin(); pos!= histoCycle.end(); ++pos) {
                listeCycle.push_back(*pos);
            }
        }
	}

    //Dans le cas où un cycle a été trouvé, ce vector contient la liste des sommets faisant un cycle
    std::vector<int> getListeCycle(){
        return listeCycle;
    }

	void detectCycle(int v){
		empiles.at(v) = true;
		marques.at(v) = true;
        histoCycle.push_back(v);
		for (int w : graph.adjacent(v)){
			if (trouveCycle){
				return;
			} else if (!marques.at(w)){
				detectCycle(w);
			} else if(empiles.at(w)){
                histoCycle.push_back(w);
                sommetCycle = w;
				trouveCycle = true;
			}
		}
        //Si on a trouve un cycle, on sort de la récursion sans dépiler le sommet
        if (trouveCycle) return;

        //Lorsqu'on dépile un sommet, on le retire aussi de la liste, afin de garder uniquement le chemin du cycle
        histoCycle.remove(v);
		empiles.at(v) = false;
		return;
	}
	
};

#endif
