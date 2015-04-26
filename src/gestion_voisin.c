#include "gestion_voisin.h"

/* Attention, si la cible n'est pas un voisin, le résultat peut être incohérent
   : si la cible est en bas à gauche, elle renverra 'gauche' */

direction dequel_cote(zone* notre_zone, zone* a_placer) {
  if (zone_cible->maxX < my_zone.minX) {
    return GAUCHE;
  } else if (zone_cible->minX > my_zone.maxX) {
    return DROITE;
  } else if (zone_cible->maxY < my_zone.minY) {
    return BAS;
  } else {
    return HAUT;
  }
}

zone* get_liste_zone(zone* zone_cible) {
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

zone* get_list_zone_par_coor(int minX, int maxX, int minY, int maxY) {
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
  if((z->maxX == z2->minX -1 ) && (z->minY < z2->maxY && z->maxY > z2->minY) ||
     (z2->maxX == z->minX -1 && (z->minY < z2->maxY && z->maxY > z2->minY)) || 
     (z->maxY == z2->minY -1 && (z->minX < z2->maxX && z->maxX > z2->minX)) ||
     (z2->maxY == z->minY -1 && (z->minX < z2->maxX && z->maxX > z2->minX))) {
    return true;
  }
  return false;
}

void supprimer_zone(liste* liste, zone* e_supp) {
  
  if(liste->prem->id == e_supp->id) {
    liste->prem = liste->prem->next;
  }

}

