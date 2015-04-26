#include "gestion_voisin.h"

/* Attention, si la cible n'est pas un voisin, le résultat peut être incohérent
   : si la cible est en bas à gauche, elle renverra 'gauche' */

direction dequel_cote(zone* notre_zone, zone* a_placer) {
  if (a_placer->maxX < my_zone.minX) {
    return GAUCHE;
  } else if (a_placer->minX > my_zone.maxX) {
    return DROITE;
  } else if (a_placer->maxY < my_zone.minY) {
    return BAS;
  } else {
    return HAUT;
  }
}

liste_zone get_liste_zone(zone* zone_cible) {
  if (zone_cible->maxX < my_zone.minX) {
    return gauche;
  } else if (zone_cible->minX > my_zone.maxX) {
    return droite;
  } else if (zone_cible->maxY < my_zone.minY) {
    return bas;
  } else {
    return haut;
  }
}

liste_zone get_list_zone_par_coor(int minX, int maxX, int minY, int maxY) {
  if (maxX < my_zone.minX) {
    return gauche;
  } else if (minX > my_zone.maxX) {
    return droite;
  } else if (maxY < my_zone.minY) {
    return bas;
  } else {
    return haut;
  }
}

bool est_adjacent(zone* z1, zone* z2) {
  if((z1->maxX == z2->minX -1 ) && (z1->minY < z2->maxY && z1->maxY > z2->minY) ||
     (z2->maxX == z1->minX -1 && (z1->minY < z2->maxY && z1->maxY > z2->minY)) || 
     (z1->maxY == z2->minY -1 && (z1->minX < z2->maxX && z1->maxX > z2->minX)) ||
     (z2->maxY == z1->minY -1 && (z1->minX < z2->maxX && z1->maxX > z2->minX))) {
    return true;
  }
  return false;
}

void supprimer_zone(liste_zone liste, zone* e_supp) {
  zone *toFree = NULL, *elt;

  if(liste->prem->id_noeud == e_supp->id_noeud) {
    /* cas premier elt de la liste */
    toFree = liste->prem;
    liste->prem = liste->prem->next;
    detruire_zone(toFree);
    return;
  } else {
    for(elt = liste->prem; elt; elt = elt->next) {
      if(elt->next->id_noeud == e_supp->id_noeud) {
        toFree = elt->next;
        elt->next = elt->next->next;
        detruire_zone(toFree);
        return;
      }
    }
  }
  /* Si e_supp ne fait pas partie de la liste ??? */
  detruire_zone(e_supp);
}

void supprimer_voisin_non_adjacent(zone* curs_voisin, zone* my_zone) {
  if(!est_adjacent(curs_voisin, my_zone)) {
    detruire_zone(curs_voisin);
  }
}

zone* get_zone_par_id(liste_zone liste, int id) {
  zone *elt;
  
  for(elt = gauche->prem; elt; elt = elt->next)
    if(elt->id_noeud == id) return elt;

  for(elt = droite->prem; elt; elt = elt->next)
    if(elt->id_noeud == id) return elt;

  for(elt = bas->prem; elt; elt = elt->next)
    if(elt->id_noeud == id) return elt;

  for(elt = haut->prem; elt; elt = elt->next)
    if(elt->id_noeud == id) return elt;

  return NULL;
}


