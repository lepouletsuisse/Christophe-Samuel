/** \file banditmanchot_interface.h
* \brief Définition des fonctions offertes au développeur pour agir sur 
*        l'interface graphique.
* \author Yann Thoma
* \date 25.02.2009
*/

#include <QString>

#ifndef BANDITMANCHOT_INTERFACE_H_
#define BANDITMANCHOT_INTERFACE_H_

/**
* Cette fonction permet de donner la valeur d'un des rouleaux. Les rouleaux sont 
* numérotés de 0 à 2, et la valeur est un entier entre 0 et 9. L'affichage est
* alors modifié avec la nouvelle valeur.
* \param rouleau Le numéro du rouleau, entre 0 et 2
* \param valeur La valeur à afficher par le rouleau, entre 0 et 9
*/
void setValeurRouleau(int rouleau,int valeur);

/**
* Cette fonction affiche le message passé en paramètres. Il permet d'indiquer
* des informations pour l'utilisateur.
* \param mess Une chaîne de caractères à afficher
*/
void setMessage(const QString mess);

/**
* Cette fonction permet de définir le jackpot disponible. Il est alors
* affiché dans la fenêtre.
* \param jackpot Le jackpot courant
*/
void setJackpot(int jackpot);

#endif // BANDITMANCHOT_INTERFACE_H_
