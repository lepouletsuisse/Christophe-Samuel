/*
 * File:   ParcoursEnProfondeurRecursif.h
 * Author: Olivier Cuisenaire
 *
 * Created on 4. septembre 2014, 14:38
 */

#ifndef PARCOURSENPROFONDEURRECURSIF_H
#define	PARCOURSENPROFONDEURRECURSIF_H

#include <vector>
#include <queue>
#include <stack>

template<typename GraphType>
class BFS {
public:
    
    BFS(const GraphType& G) : g(G) {
    }
    
    template <typename Func> void visit(int v, Func f) {
        parent.assign(g.V(), -1);
        this->bfs(v, f);
    }
    
    int parentOf(int v) const {
        return this->parent[v];
    }
    
private:
    const GraphType& g;
    std::vector<int> parent;
    
    template<typename Func> void bfs(int v, Func f) {
        std::queue<int> pile;
        parent[v] = v;
        pile.push(v);

        while (!pile.empty()) {
            v = pile.front();
            pile.pop();
            for (int w : g.adjacent(v)) {
                if (parent[w] == -1) {
                    parent[w] = v;
                    pile.push(w);
                }
            }
            f(v);
        }
    }
};

#endif	/* PARCOURSENPROFONDEURRECURSIF_H */

