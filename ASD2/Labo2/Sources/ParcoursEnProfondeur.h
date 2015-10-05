/* 
 * File:   ParcoursEnProfondeur.h
 * Author: Olivier Cuisenaire
 *
 * Created on 18. septembre 2014, 10:46
 */

#ifndef PARCOURSENPROFONDEUR_H
#define	PARCOURSENPROFONDEUR_H


#include <vector>
#include <stack>
#include <utility>

template<typename GraphType> class DFSIter {
private:
    const GraphType& g;
    std::vector<bool> preMarked;
    std::vector<bool> postMarked;
    
public:
    DFSIter(const GraphType& G) : g(G) {
    }
    
    template <typename FuncPre, typename FuncPost>
    void visitGraph(FuncPre fpre, FuncPost fpost) { // visit the whole graph
        if(g.V()>0)
            visit(0,fpre,fpost);
        for(int v=1;v<g.V();++v)
            if(!preMarked[v])
                visit(v,fpre,fpost,false);
    }
    
    template <typename FuncPre, typename FuncPost>
    void visit(int v, FuncPre fpre, FuncPost fpost, bool reset=true) {
        
        if(reset) {
            preMarked.assign(g.V(), false);
            postMarked.assign(g.V(),false);
        }
        
        std::stack<int> pile;
        pile.push(v);
        
        while (!pile.empty()) {
            v = pile.top();
            pile.pop();
            
            if(postMarked[v]) continue;
            
            if(preMarked[v]) {
                postMarked[v] = true;
                fpost(v);
                continue;
            }
            
            preMarked[v] = true;
            fpre(v);
            pile.push(v);
            
            decltype(g.adjacent(v)) adj = g.adjacent(v);
                // auto ferait une copie des listes rendues en référence.
                // utiliser decltype(...) évite cette copie inutile.
            
            std::for_each( adj.crbegin(), adj.crend(), [&](int w) {
                // parcours à l'envers pour obtenir un ordre identique
                // à l'implantation récursive. 
                if(!preMarked[w])
                    pile.push(w);
            });
        }
    }
};

template<typename GraphType> class DFS {
private:
    const GraphType& g;
    std::vector<bool> marked;

public:
    DFS(const GraphType& G) : g(G) {
    }
    
    template <typename FuncPre, typename FuncPost>
    void visitGraph(FuncPre fpre, FuncPost fpost) {         // visit the whole graph
        marked.assign(g.V(), false);
        for(int v=0;v<g.V();++v)
            if(!marked[v])
                recursion(v,fpre,fpost);
    }
    
    template <typename FuncPre, typename FuncPost>
    void visit(int v, FuncPre fpre, FuncPost fpost, bool reset=true) {
        if(reset)
            marked.assign(g.V(), false);
        recursion(v, fpre, fpost);
    }
    
private:
    template <typename FuncPre, typename FuncPost>
    void recursion(int v, FuncPre fpre, FuncPost fpost) {
        fpre(v);
        marked[v] = true;
        
        for (int w : g.adjacent(v))
            if (!marked[w])
                recursion(w, fpre, fpost);
        fpost(v);
    }
};

#endif	/* PARCOURSENPROFONDEUR_H */

