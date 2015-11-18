/* 
 * File:   main.cpp
 * ASD 2 - Labo 3
 * Author: Olivier Cuisenaire
 *
 * Created on 18. novembre 2014, 14:58
 */

#include <stdlib.h>
#include <iostream>
#include <ctime>

#include "RoadNetwork.h"
#include "MinimumSpanningTree.h"
#include "ShortestPath.h"

#include "EdgeWeightedGraph.h"
#include "EdgeWeightedDiGraph.h"
#include "EdgeWeightedGraphCommon.h"
#include "RoadGraphWrapper.h"
#include "RoadDiGraphWrapper.h"

using namespace std;

const double VITESSE_AUTOROUTE = 120.; // en Km/h
const double VITESSE_ROUTE = 70.; // en Km/h
const double PRIX_AUTOROUTE = 15.; // en millions de CHF
const double PRIX_ROUTE = 7.; // en millions de CHF

// Calcule et affiche le plus court chemin de la ville depart a la ville arrivee
// en passant par le reseau routier rn. Le critere a optimiser est la distance.

void PlusCourtChemin(const string& depart, const string& arrivee, RoadNetwork& rn) {

    std::map<string,int>::iterator it;
    it = rn.cityIdx.find(depart);
    int ville1, ville2;

    if (it == rn.cityIdx.end()){
        std::cout << "Ville de depart non trouvee !\n";
        return;
    } else{
        std::map<string,int>::iterator it2;
        it2 = rn.cityIdx.find(arrivee);
        if (it2 == rn.cityIdx.end()){
            std::cout << "Ville d'arrivee non trouvee !\n";
            return;
        } else {
            ville1 = (*it).second;
            ville2 = (*it2).second;

            // On calcul le chemin le plus court entre les deux villes
            RoadDiGraphWrapper rdgw(rn, [&](int i) { return rn.roads.at(i).lenght; });
            DijkstraSP<RoadDiGraphWrapper> sp(rdgw, ville1);
            std::cout << sp.DistanceTo(ville2) << " Km" << std::endl;

            // On reparcoure la liste des routes pour connaitre les villes traversées
            vector<WeightedDirectedEdge<double>> listeRoute = sp.PathTo(ville2);
            std::cout << "Villes traversees : " << std::endl;
            for(WeightedDirectedEdge<double> e : listeRoute){
                for(int i = 0; i < rn.roads.size(); i++){
                    if (rn.roads.at(i).cities.first == e.v1 && rn.roads.at(i).cities.second == e.v2){
                        std::cout << rn.cities.at(rn.roads.at(i).cities.first).name << " - ";
                    }
                }
            }
            std::cout << arrivee << std::endl << std::endl;
        }
    }
}

// Calcule et affiche le plus rapide chemin de la ville depart a la ville arrivee via la ville "via"
// en passant par le reseau routier rn. Le critere a optimiser est le temps de parcours
// sachant que l'on roule a 120km/h sur autoroute et 70km/h sur route normale.

void PlusRapideChemin(const string& depart, const string& arrivee, const string& via, RoadNetwork& rn) {
    int ville1, ville2, ville3;
    double temps = 0;

    std::map<string,int>::iterator it;
    it = rn.cityIdx.find(depart);
    // On vérifie que les villes soient connues
    if (it == rn.cityIdx.end()){
        std::cout << "Ville de depart non trouvee !\n";
        return;
    } else{
        std::map<string,int>::iterator it2;
        it2 = rn.cityIdx.find(arrivee);
        if (it2 == rn.cityIdx.end()){
            std::cout << "Ville d'arrivee non trouvee !\n";
            return;
        } else {
            std::map<string,int>::iterator it3;
            it3 = rn.cityIdx.find(via);
            if (it3 == rn.cityIdx.end()){
                std::cout << "Ville via non trouvee !\n";
                return;
            } else {
                ville1 = (*it).second;
                ville2 = (*it3).second;
                ville3 = (*it2).second;

                //On calcule le chemin le plus court entre le départ et via
                RoadDiGraphWrapper rdgw(rn, [&](int i) { return rn.roads.at(i).lenght; });
                DijkstraSP<RoadDiGraphWrapper> sp(rdgw, ville1);
                vector<WeightedDirectedEdge<double>> listeRoute = sp.PathTo(ville2);

                std::cout << "Villes traversees : " << std::endl;

                // Pour chaque route sur le chemin on reparcoure toutes les routes pour connaitre le numéro de la route
                // et donc sa longueur, ses villes etc... le temps est incrémenté du temps nécessaire pour parcourir
                // chaque portion de route
                for(WeightedDirectedEdge<double> e : listeRoute){
                    for(int i = 0; i < rn.roads.size(); i++){
                        if (rn.roads.at(i).cities.first == e.v1 && rn.roads.at(i).cities.second == e.v2){
                            temps += (rn.roads.at(i).motorway.Value() * rn.roads.at(i).lenght) / VITESSE_AUTOROUTE * 60;
                            temps += ((1. - rn.roads.at(i).motorway.Value()) * rn.roads.at(i).lenght) / VITESSE_ROUTE * 60;
                            std::cout << rn.cities.at(rn.roads.at(i).cities.first).name << " - ";
                        }
                    }
                }
                //On calcule le chemin le plus court entre via et l'arrivée
                DijkstraSP<RoadDiGraphWrapper> sp2(rdgw, ville2);
                vector<WeightedDirectedEdge<double>> listeRoute2 = sp2.PathTo(ville3);
                for(WeightedDirectedEdge<double> e : listeRoute2){
                    for(int i = 0; i < rn.roads.size(); i++){
                        if (rn.roads.at(i).cities.first == e.v1 && rn.roads.at(i).cities.second == e.v2){
                            temps += (rn.roads.at(i).motorway.Value() * rn.roads.at(i).lenght) / VITESSE_AUTOROUTE * 60;
                            temps += ((1. - rn.roads.at(i).motorway.Value()) * rn.roads.at(i).lenght) / VITESSE_ROUTE * 60;
                            std::cout << rn.cities.at(rn.roads.at(i).cities.first).name << " - ";
                    }
                    }
                }
                std::cout << arrivee << std::endl;
                std::cout << (int)temps << " Min" << std::endl << std::endl;

            }
        }
    }
}

// Calcule et affiche le plus reseau a renover couvrant toutes les villes le moins
// cher, en sachant que renover 1km d'autoroute coute 15 MF, et renover 1km de route normale
// coute 7 MF.

void ReseauLeMoinsCher(RoadNetwork &rn) {
    double prixTotal = 0;

    // La fonction de cout prend en compte le prix du km d'autoroute et de route
    RoadGraphWrapper rgw(rn, [&](int i){
        double longueurAutoroute = rn.roads.at(i).motorway.Value() * rn.roads.at(i).lenght;
        double longueurRoute = (1 - rn.roads.at(i).motorway.Value()) * rn.roads.at(i).lenght;
        return longueurAutoroute * PRIX_AUTOROUTE + longueurRoute * PRIX_ROUTE;
    });


    auto mst = MinimumSpanningTree<RoadGraphWrapper>::Kruskal(rgw);
    std::cout << "Routes a renover : " << std::endl;
    for (const auto& e : mst){
        prixTotal += e.weight;
        std::cout << rn.cities.at(e.v1).name << " - "
        << rn.cities.at(e.v2).name << std::endl;
    }
    std::cout << "Cout Total des renovations : " << std::endl;
    std::cout << prixTotal << "M CHF" << std::endl;
}

// compare les algorithmes Dijkstra et BellmanFord pour calculer les plus courts chemins au
// sommet 0 dans le graphe defini par filename.
// a utiliser pour tester votre implementation de Dijkstra

void testShortestPath(string filename)
{
    cout << "Testing " << filename << endl;
    
    bool ok = true;
    
    typedef EdgeWeightedDiGraph<double> Graph;
    Graph ewd(filename);
    
    clock_t startTime = clock();

    BellmanFordSP<Graph> referenceSP(ewd,0);
    
    cout << "Bellman-Ford: " << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
    startTime = clock();

    DijkstraSP<Graph> testSP(ewd,0);
    
    cout << "Dijkstra:     " << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;

    for (int v=0; v<ewd.V(); ++v) {
        if (referenceSP.DistanceTo(v) != testSP.DistanceTo(v) ) {
            cout << "Oops: vertex" << v << " has " << referenceSP.DistanceTo(v) << " != " <<  testSP.DistanceTo(v) << endl;
            ok = false;
            break;
        }
    }
    
    if(ok) cout << " ... test succeeded " << endl << endl;
}

int main(int argc, const char * argv[]) {
    
    testShortestPath("tinyEWD.txt");
    testShortestPath("mediumEWD.txt");
    testShortestPath("1000EWD.txt");
    testShortestPath("10000EWD.txt");
    //testShortestPath("largeEWD.txt"); // disponible sur le moodle du cours
    
    RoadNetwork rn("reseau.txt");
    
    cout << "1. Chemin le plus court entre Geneve et Emmen" << endl;
    
    PlusCourtChemin("Geneve", "Emmen", rn);
    
    cout << "2. Chemin le plus court entre Lausanne et Bale" << endl;
    
    PlusCourtChemin("Lausanne", "Basel", rn);
  
    cout << "3. Chemin le plus rapide entre Geneve et Emmen en passant par Yverdon" << endl;
    
    PlusRapideChemin("Geneve", "Emmen", "Yverdon-Les-Bains", rn);
    
    cout << "4. Chemin le plus rapide entre Geneve et Emmen en passant par Vevey" << endl;
    
    PlusRapideChemin("Geneve", "Emmen", "Vevey", rn);

    cout << "5. Quelles routes doivent etre renovees ? Quel sera le cout de la renovation de ces routes ?" << endl;
    
    ReseauLeMoinsCher(rn);
    
    return EXIT_SUCCESS;
}
