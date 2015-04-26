#ifndef GESTION_VOISIN_H
#define GESTION_VOISIN_H

#include "can.h"


// retourne dequel coté devrait etre la zone
direction dequel_cote(zone* notre_zone, zone* a_placer);

// retourn la liste où doit se trouver la zone_cible (get_liste_zone risque d'appeler get_list_zone_par_coor)
liste_zone get_liste_zone(zone* zone_cible);

// retourn la liste où doit se trouver la zone_cible (par id et coordonné)
liste_zone get_liste_zone_par_coor(int minX, int maxX, int minY, int maxY);

// adjacent, regarde si z1 et z2 son adjacente
bool est_adjacent(zone* z1, zone* z2);

// supprime la zone de la liste, la zone est detruite car un pointeur par zone
void supprimer_zone(liste_zone liste, zone* e_supp);

void supprimer_voisin_non_adjacent(zone* curs_voisin, zone* my_zone);

// cherche dans liste et retourn la zone qui a l'id, NULL sinon
zone* get_zone_par_id(liste_zone liste, int id);


#endif /* GESTION_VOISIN_H */
