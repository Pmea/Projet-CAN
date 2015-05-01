#include "gestion_voisin.h"

direction dequel_cote(zone* notre_zone, zone* a_placer) {
  if (a_placer->maxX < notre_zone->minX) {
    return GAUCHE;
  } else if (a_placer->minX > notre_zone->maxX) {
    return DROITE;
  } else if (a_placer->maxY < notre_zone->minY) {
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

liste_zone get_liste_zone_par_coor(int minX, int maxX, int minY, int maxY) {
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
  if((z1->maxX == z2->minX -1 && (z1->minY <= z2->maxY && z1->maxY >= z2->minY)) ||
     (z2->maxX == z1->minX -1 && (z1->minY <= z2->maxY && z1->maxY >= z2->minY)) || 
     (z1->maxY == z2->minY -1 && (z1->minX <= z2->maxX && z1->maxX >= z2->minX)) ||
     (z2->maxY == z1->minY -1 && (z1->minX <= z2->maxX && z1->maxX >= z2->minX))) {
    return true;
  }
  return false;
}

void supprimer_zone(liste_zone liste, zone* e_supp) {
  supprimer_element_liste(liste, e_supp);
}

 void supprimer_voisin_non_adjacent(liste_zone liste, zone* z_ref ) { 
   zone *curs;
   zone* tmp;
   curs = liste->prem;
   while(curs != NULL){
     if(!est_adjacent(z_ref, curs)){
       tmp= curs->next;
       supprimer_element_liste(liste, curs);
       curs= tmp;
     }
     else{
       curs= curs->next;
     }  
   }
  }  


zone* get_zone_par_id(liste_zone liste, int id) {
  zone *elt;

  for(elt = liste->prem; elt; elt = elt->next)
    if(elt->id_noeud == id) return elt;

  return NULL;
}

zone* get_zone_par_id_total(int id){
	zone* curs= haut->prem;
	while(curs != NULL){
		if(curs->id_noeud== id)
			return curs;
		curs=curs->next;
	}
	
	curs= droite->prem;
	while(curs != NULL){
		if(curs->id_noeud== id)
			return curs;
		curs=curs->next;
	}

	curs= bas->prem;
	while(curs != NULL){
		if(curs->id_noeud== id)
			return curs;
		curs=curs->next;
	}
	curs= gauche->prem;
	while(curs != NULL){
		if(curs->id_noeud== id)
			return curs;
		curs=curs->next;
	}
	return NULL;
}

bool x_dans_zone(int x){
  return my_zone.minX <= x &&  my_zone.maxX >= x;
}
bool y_dans_zone(int y){
  return my_zone.minY <= y &&  my_zone.maxY >= y;
}

bool point_dans_zone(int x, int y){
  return x_dans_zone(x) && y_dans_zone(y);
}
