#include "gestion_voisin.h"



/* Attention, si la cible n'est pas un voisin, le résultat peut être incohérent
   : si la cible est en bas à gauche, elle renverra 'gauche' */

direction dequel_cote(zone* notre_zone, zone* a_placer) {
  if (a_placer->maxX < notre_zone->minX) {
    /* printf("gauche\n"); */
    return GAUCHE;
  } else if (a_placer->minX > notre_zone->maxX) {
    /* printf("droite\n"); */
    return DROITE;
  } else if (a_placer->maxY < notre_zone->minY) {
    /* printf("bas\n"); */
    return BAS;
  } else {
    /* printf("haut\n"); */
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
  if((z1->maxX == z2->minX -1 && (z1->minY < z2->maxY && z1->maxY > z2->minY)) ||
     (z2->maxX == z1->minX -1 && (z1->minY < z2->maxY && z1->maxY > z2->minY)) || 
     (z1->maxY == z2->minY -1 && (z1->minX < z2->maxX && z1->maxX > z2->minX)) ||
     (z2->maxY == z1->minY -1 && (z1->minX < z2->maxX && z1->maxX > z2->minX))) {
    return true;
  }
  return false;
}

void supprimer_zone(liste_zone liste, zone* e_supp) {
  zone *toFree = NULL, *elt;

  supprimer_element_liste(liste, e_supp);

  /* if(liste->prem->id_noeud == e_supp->id_noeud) { */
  /*   /\* cas premier elt de la liste *\/ */
  /*   toFree = liste->prem; */
  /*   liste->prem = liste->prem->next; */
  /*   detruire_zone(toFree); */
  /*   return; */
  /* } else { */
  /*   for(elt = liste->prem; elt; elt = elt->next) { */
  /*     if(elt->next->id_noeud == e_supp->id_noeud) { */
  /*       toFree = elt->next; */
  /*       elt->next = elt->next->next; */
  /*       detruire_zone(toFree); */
  /*       return; */
  /*     } */
  /*   } */
  /* } */
  /* Si e_supp ne fait pas partie de la liste ??? */
  /*   => on le supprime ! */
  /* detruire_zone(e_supp); */
}

/* void supprimer_voisin_non_adjacent(liste_zonel liste/\* , zone* e_supp *\/) { */
/*   zone *toFree = NULL, *elt; */

/*   while(liste->prem &&  */
/*         !est_adjacent(liste->prem, &my_zone) ) { */
/*     /\* cas premier elt de la liste *\/ */
/*     toFree = liste->prem; */
/*     liste->prem = liste->prem->next; */
/*     detruire_zone(toFree); */
/*   }  */
/*   elt = liste->prem; */
/*   while (elt) { */
/*     while(elt && !est_adjacent(elt->next, &my_zone)) { */
/*       toFree = elt->next; */
/*       elt->next = elt->next->next; */
/*       detruire_zone(toFree); */
/*     } */
/*     elt = elt->next; */
/*   } */
/* } */

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

/* liste_zone gauche; */
/* liste_zone droite; */
/* liste_zone bas; */
/* liste_zone haut; */

/* zone *z1, *z2, *z3, *z4, *z5, my_zone; */

/* int main() { */

/*   gauche = creer_liste(NULL); */
/*   droite = creer_liste(NULL); */
/*   bas = creer_liste(NULL); */
/*   haut = creer_liste(NULL); */

/*   my_zone.id_noeud = 6; */
/*   my_zone.minX = 101; */
/*   my_zone.maxX = 300; */
/*   my_zone.minY = 201; */
/*   my_zone.maxY = 250; */
/*   my_zone.next = NULL; */

/*   z1 = creer_zone(1, 91, 100, 221, 240, NULL); */
/*   z2 = creer_zone(2, 301, 500, 0, 300, NULL); */
/*   z3 = creer_zone(3, 101, 300, 0, 200, NULL); */
/*   z4 = creer_zone(4, 91, 100, 201, 220, NULL); */
/*   z5 = creer_zone(5, 0, 300, 251, 300, NULL); */


/*   if(dequel_cote(&my_zone, z1) != GAUCHE) */
/*     fprintf(stderr, "Erreur z1 mauvais coté dequel_cote\n"); */
/*   if(dequel_cote(&my_zone, z2) != DROITE) */
/*     fprintf(stderr, "Erreur z2 mauvais coté dequel_cote\n"); */
/*   if(dequel_cote(&my_zone, z3) != BAS) */
/*     fprintf(stderr, "Erreur z3 mauvais coté dequel_cote\n"); */
/*   if(dequel_cote(&my_zone, z4) != GAUCHE) */
/*     fprintf(stderr, "Erreur z4 mauvais coté dequel_cote\n"); */
/*   if(dequel_cote(&my_zone, z5) != HAUT) */
/*     fprintf(stderr, "Erreur z5 mauvais coté dequel_cote\n"); */

/*   if(get_liste_zone(z1) != gauche) */
/*     fprintf(stderr, "Erreur z1 mauvais coté get liste zone\n"); */
/*   if(get_liste_zone(z2) != droite) */
/*     fprintf(stderr, "Erreur z2 mauvais coté get liste zone\n"); */
/*   if(get_liste_zone(z3) != bas) */
/*     fprintf(stderr, "Erreur z3 mauvais coté get liste zone\n"); */
/*   if(get_liste_zone(z4) != gauche) */
/*     fprintf(stderr, "Erreur z4 mauvais coté get liste zone\n"); */
/*   if(get_liste_zone(z5) != haut) */
/*     fprintf(stderr, "Erreur z5 mauvais coté get liste zone\n"); */

/*   if(get_list_zone_par_coor(91, 100, 221, 240) != gauche) */
/*     fprintf(stderr, "Erreur z1 mauvais coté get list zone par coor\n"); */
/*   if(get_list_zone_par_coor(301, 500, 0, 300) != droite) */
/*     fprintf(stderr, "Erreur z2 mauvais coté get list zone par coor\n"); */
/*   if(get_list_zone_par_coor(101, 300, 0, 200) != bas) */
/*     fprintf(stderr, "Erreur z3 mauvais coté get list zone par coor\n"); */
/*   if(get_list_zone_par_coor(91, 100, 201, 220) != gauche) */
/*     fprintf(stderr, "Erreur z4 mauvais coté get list zone par coor\n"); */
/*   if(get_list_zone_par_coor(0, 300, 251, 300) != haut) */
/*     fprintf(stderr, "Erreur z5 mauvais coté get list zone par coor\n"); */

/*   if(!est_adjacent(&my_zone, z1)) */
/*     fprintf(stderr, "Erreur z1 non adjacent\n"); */
/*   if(!est_adjacent(&my_zone, z2)) */
/*     fprintf(stderr, "Erreur z2 non adjacent\n"); */
/*   if(!est_adjacent(&my_zone, z3)) */
/*     fprintf(stderr, "Erreur z3 non adjacent\n"); */
/*   if(!est_adjacent(&my_zone, z4)) */
/*     fprintf(stderr, "Erreur z4 non adjacent\n"); */
/*   if(!est_adjacent(&my_zone, z5)) */
/*     fprintf(stderr, "Erreur z5 non adjacent\n"); */
/*   if(!est_adjacent(z2, z3)) */
/*     fprintf(stderr, "Erreur z3 et z2 non adjacents\n"); */
/*   if(est_adjacent(z2, z4)) */
/*     fprintf(stderr, "Erreur z2 et z4  adjacents\n"); */
    
/*   ajouter_entete_liste(get_liste_zone(z1), z1); */
/*   ajouter_entete_liste(get_liste_zone(z2), z2); */
/*   ajouter_entete_liste(get_liste_zone(z3), z3); */
/*   ajouter_entete_liste(get_liste_zone(z4), z4); */
/*   ajouter_entete_liste(get_liste_zone(z5), z5); */
  
/*   if(get_zone_par_id(gauche, 1) != z1) */
/*     fprintf(stderr, "Erreur z1 mal trouvé get zone par id\n"); */
/*   if(get_zone_par_id(droite, 1)) */
/*     fprintf(stderr, "Erreur z1 trouvé get zone par id\n"); */
/*   if(get_zone_par_id(droite, 2) != z2) */
/*     fprintf(stderr, "Erreur z2 mal trouvé get zone par id\n"); */
/*   if(get_zone_par_id(gauche, 2)) */
/*     fprintf(stderr, "Erreur z2 trouvé get zone par id\n"); */
/*   if(get_zone_par_id(bas, 3) != z3) */
/*     fprintf(stderr, "Erreur z3 mal trouvé get zone par id\n"); */
/*   if(get_zone_par_id(gauche, 3)) */
/*     fprintf(stderr, "Erreur z3 trouvé get zone par id\n"); */
/*   if(get_zone_par_id(gauche, 4) != z4) */
/*     fprintf(stderr, "Erreur z4 mal trouvé get zone par id\n"); */
/*   if(get_zone_par_id(haut, 5) != z5) */
/*     fprintf(stderr, "Erreur z5 mal trouvé get zone par id\n"); */

/*   if(gauche->prem->id_noeud != 4)   */
/*     fprintf(stderr, "Erreur z4 n'est pas en tête\n"); */
/*   if(gauche->prem->next->id_noeud != 1)   */
/*     fprintf(stderr, "Erreur z1 n'est pas en second\n"); */

/*   supprimer_zone(gauche, z4); */
/*   if(gauche->prem->id_noeud != 1) */
/*     fprintf(stderr, "Erreur z1 n'est pas en tête\n"); */
  
/*   supprimer_zone(bas, z3); */
/*   if(bas->prem) */
/*     fprintf(stderr, "Erreur bas n'est pas vide\n"); */

/*   /\* z2->minX++; *\/ */
/*   /\* supprimer_voisin_non_adjacent(droite, z2); *\/ */
/*   /\* if(droite->prem) *\/ */
/*   /\*   fprintf(stderr, "Erreur bas n'est pas vide\n"); *\/ */

/*   /\* supprimer_voisin_non_adjacent(gauche, z2); *\/ */
/*   /\* if(droite->prem) *\/ */
/*   /\*   fprintf(stderr, "Erreur bas n'est pas vide\n"); *\/ */

/*   /\* supprimer_voisin_non_adjacent(z1, &my_zone); *\/ */
/*   /\* if(!gauche->prem) *\/ */
/*   /\*   fprintf(stderr, "Erreur z1 a été supprimé\n"); *\/ */

/*   return EXIT_SUCCESS; */
/* } */


