#ifndef GESTION_LISTE_H
#define GESTION_LISTE_H

#include "can.h"

zone* creer_zone(int id_noeud, int minX, int maxX, int minY, int maxY, zone * next);
void detruire_zone(zone * z);

//ajoute element en tete de la liste
void ajouter_entete_liste(zone *liste, zone* new_one);

//supprime element en tete de liste si null il ne se passe rien
void supprimer_entete_liste(zone* liste);

//supprime un element precis de la liste, si il n'existe pas il ne se passe rien
void supprimer_element_liste(zone* liste, zone* zone_supp);

// detruire la totalité de la liste
void detruire_liste(zone* v);

//dit si l'element est dans la liste
bool element_dans_liste(zone* liste, zone*);


#endif /* GESTION_VOISIN_H */