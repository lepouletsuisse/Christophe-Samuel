#include "DiGraph.h"

DiGraph::DiGraph(int V) 
{
	adjacencyLists.resize(V);
}

DiGraph::DiGraph(std::istream& s) {
	int V,E,v,w;
	
	s >> V;
	s >> E;

	adjacencyLists.resize(V);

	for (int i = 0; i < E; i++) {
		s >> v;
		s >> w;
		addEdge(v, w);
	}
}

void DiGraph::addEdge(int v, int w) {
	adjacencyLists.at(v).push_back(w);
}

DiGraph::Iterable DiGraph::adjacent(int v) const {
	return adjacencyLists.at(v);
}

int DiGraph::V() const {
	return (int)adjacencyLists.size();
}

DiGraph DiGraph::reverse() const {
	DiGraph dg(V());
	for(int v=0;v<V();++v)
		for(int w : adjacent(v))
			dg.addEdge(w,v);
	return dg;
}
