/* 
 * File:   ex1.cpp
 * Author: Olivier Cuisenaire
 *
 * Created on 2 oct. 2014, 11:19:03
 */

#include <stdlib.h>
#include <iostream>

#include "GraphFromImage.h"
#include "ParcoursEnProfondeur.h"

int main(int argc, char** argv) {
    
    std::string filename("input.bmp");
    bitmap_image image(filename);
    
	if (!image) {
		std::cout << "test1 : Failed to open " << filename << ") \n";
		return (EXIT_FAILURE);
	}
    
    std::cout << "image size: " << image.width() << " x " << image.height() << "\n";
    
    GraphFromImage G(image);
    DFS<GraphFromImage> dfs(G);

    //Question BONUS: Pourquoi n'utilisons-nous pas la methode visite pour parcourir l'image ?
    //C'est une fonction récursive et vu que l'image est très grande., la fonction recréerait des variables à chaque
    //appel et donc prendrait trop de place en mémoire, alors que iterativeVisit() écrase les variables

    //on colore la carotte
    int x = 250, y = 400;

    dfs.iterativeVisit( G.idx(x,y), [&G, &image] (int v) {
        image.set_pixel( G.x(v), G.y(v), 224, 128, 64);
    });


    //on ajoute une couleur de fond
    dfs.iterativeVisit( G.idx(0,0), [&G, &image] (int v) {
        image.set_pixel( G.x(v), G.y(v), 0, 255, 64);
    });

    //on sauve l'image modifiee
    image.save_image("output.bmp");
    
    
    //on charge l'image temoin pour verifier notre code
    bitmap_image image_gold("goal.bmp");
    
    if(image.psnr(image_gold) < 1000000)
        std::cout  << "test failed - psnr = " << image.psnr(image_gold)  << ") \n";
    else
        std::cout << "test succeeded - image is identical to goal.bmp\n";
    
    return (EXIT_SUCCESS);
    
}

