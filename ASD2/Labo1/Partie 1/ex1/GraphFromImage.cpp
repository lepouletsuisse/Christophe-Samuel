/*
 * File:   GraphFromImage.cpp
 * Author: Samuel Darcey & Christophe Peretti
 *
 * Created on 27. septembre 2015
 */
#include "GraphFromImage.h"

GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
}

GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
    Iterable listeTemp;
    unsigned char r,g,b;
    int pixelSup = v - image.width();
    int pixelDroite = v + 1;
    int pixelInf = v + image.width();
    int pixelGauche = v - 1;

    // On vérifie s'il y a un pixel au dessus
     if (v >= image.width()){
         image.get_pixel(x(pixelSup), y(pixelSup), r, g, b);
         if((int)r == 255 && (int)g == 255 && (int)b == 255){
             listeTemp.push_back(pixelSup);
         }
     }

    // On vérifie s'il y a u pixel à droite
    if ((v+1) % image.width() != 0){
        image.get_pixel(x(pixelDroite), y(pixelDroite), r, g, b);
        if((int)r == 255 && (int)g == 255 && (int)b == 255){
            listeTemp.push_back(pixelDroite);
        }
    }

    // On vérifie s'il y a un pixel au dessous
    if (v + image.width() < V()){
        image.get_pixel(x(pixelInf), y(pixelInf), r, g, b);
        if((int)r == 255 && (int)g == 255 && (int)b == 255){
            listeTemp.push_back(pixelInf);
        }
    }

    // On vérifie s'il y a un pixel à gauche
    if (v % image.width() != 0){
        image.get_pixel(x(pixelGauche), y(pixelGauche), r, g, b);
        if((int)r == 255 && (int)g == 255 && (int)b == 255){
            listeTemp.push_back(pixelGauche);
        }
    }

    return listeTemp;
}

int GraphFromImage::idx(int x, int y) const {
    return image.width() * y + x;
}

int GraphFromImage::x(int idx) const {
    return idx % (int)image.width();
}

int GraphFromImage::y(int idx) const {
    return (int)(idx / (int)image.width());
}

int GraphFromImage::V() const {
    return image.height() * image.width() - 1;
}
