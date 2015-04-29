#ifndef GESTION_DONNEES_H
#define GESTION_DONNEES_H

#include "can.h"

donnee* get_donnee(liste_donnee liste, int x, int y);

liste_donnee creer_liste_donnee(donnee*  prem);
void detruire_liste_donnee(liste_donnee liste);

donnee* creer_donnee(int a, int b, int data, donnee* next);
// a t'utiliser que si l'element n'est pas dans une liste
void detruire_donnee(donnee *d);

//ajoute element en tete de la liste
void ajouter_entete_liste_donnee(liste_donnee liste, donnee* new_one);

//supprime element en tete de liste si null il ne se passe rien
void supprimer_entete_liste_donnee(liste_donnee liste);

//supprime un element precis de la liste, si il n'existe pas il ne se passe rien
void supprimer_element_liste_donnee(liste_donnee liste, donnee* d_supp);

// supprime la totalité de la liste
void vider_liste_donnee(liste_donnee liste);

//dit si l'element est dans la liste
bool est_dans_liste_donnee(liste_donnee liste, donnee* elem);

// return true si les deux zones ont le même id
bool est_meme_donnee(donnee* d1, donnee* d2);


/* DEBUG */

void afficher_donnee(donnee* d);
void afficher_liste_donnee(liste_donnee liste_d);

void afficher_liste_donnee_valeur(int id_noeud, liste_donnee liste_d);


#endif /* GESTION_DONNEES_H */
