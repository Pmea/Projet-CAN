#ifndef GESTION_LISTE_H
#define GESTION_LISTE_H

#include "can.h"


liste_zone creer_liste(zone * prem);
void detruire_liste(liste_zone liste);

zone* creer_zone(int id_noeud, int minX, int maxX, int minY, int maxY, zone * next);
// a utiliser que si l'element n'est pas dans une liste
void detruire_zone(zone * z);

//ajoute element en tete de la liste
void ajouter_entete_liste(liste_zone liste, zone* new_one);

//supprime element en tete de liste si null il ne se passe rien
void supprimer_entete_liste(liste_zone liste);

//supprime un element precis de la liste, si il n'existe pas il ne se passe rien
void supprimer_element_liste(liste_zone liste, zone* zone_supp);

// supprime la totalité de la liste
void vider_liste(liste_zone liste);

//true si l'element est dans la liste
bool est_dans_liste(liste_zone liste, zone* elem);

//true si les deux zones ont le même id
bool est_meme_element(zone* z1, zone* z2);



//* Debbug *//

void afficher_zone(zone* z);
void afficher_liste(liste_zone lz);

#endif /* GESTION_VOISIN_H */