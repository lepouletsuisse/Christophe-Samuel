/* 
 * File:   GraphFromImage.h
 * Author: Olivier Cuisenaire
 *
 * Created on 2. octobre 2014, 12:09
 */

#ifndef GRAPHFROMIMAGE_H
#define	GRAPHFROMIMAGE_H

#include <list>

#include "bitmap_image.hpp"

class GraphFromImage {
public:

    GraphFromImage(const bitmap_image& i);

    typedef std::list<int> Iterable;

    Iterable adjacent(int v) const; //sommets adjacents
    int V() const;                  //nombre de sommets

    int idx(int x, int y) const;    //index du sommet représentant le pixel a la position x, y
    int x(int idx) const;           //coordonnee x du sommet idx
    int y(int idx) const;           //coordonnee y du sommet idx
    
private:
    const bitmap_image& image;
};

#endif	/* GRAPHFROMIMAGE_H */
