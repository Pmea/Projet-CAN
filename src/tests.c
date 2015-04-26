#include "can.h"

bool test_ajout_recherche_suppr_voisins() {
  zone z1, z2, z3, z4;
  bool retour = true;
  zone *elt;
  
  printf("Début test ajout, recherche, suppression voisins\n");

  z1.id_noeud = 1;
  z2.id_noeud = 2;
  z3.id_noeud = 3;
  z4.id_noeud = 4;

  z1.minX = 90;
  z1.maxX = 100;
  z1.minY = 220;
  z1.maxY = 240;

  z2.minX = 300;
  z2.maxX = 500;
  z2.minY = 0;
  z2.maxY = 300;

  z3.minX = 100;
  z3.maxX = 300;
  z3.minY = 0;
  z3.maxY = 200;

  z4.minX = 90;
  z4.maxX = 100;
  z4.minY = 200;
  z4.maxY = 220;

  ajouterVoisin(&z1);
  ajouterVoisin(&z2);
  ajouterVoisin(&z3);

  if(rechercheVoisin(1, 90, 100, 220, 240) != &z1) {
    printf("erreur recherche voisin 1\n");
    retour = false;
  }

  if(rechercheVoisin(2, 300, 500, 0, 300) != &z2) {
    printf("erreur recherche voisin 2\n");
    retour = false;
  }

  if(rechercheVoisin(3, 100, 300, 0, 200) != &z3) {
    printf("erreur recherche voisin 3\n");
    retour = false;
  }

  if(rechercheVoisin(4, 90, 100, 200, 220) != NULL) {
    printf("erreur recherche voisin 4 : est présent\n");
    retour = false;
  }

  ajouterVoisin(&z4);

  if(rechercheVoisin(4, 90, 100, 200, 220) != &z4) {
    printf("erreur recherche voisin 4\n");
    retour = false;
  }

  if(rechercheVoisin(1, 90, 95, 220, 230) != &z1) {
    printf("erreur recherche voisin 1 plage différente\n");
    retour = false;
  }

  elt = supprimerVoisin(3, 100, 300, 0, 200);
  if(elt->id_noeud != 3) {
    printf("Erreur supprimer voisin : CPA3\n");
  }

  if(rechercheVoisin(3, 100, 300, 0, 200) != NULL) {
    printf("erreur recherche voisin : 3 présent\n");
  }

  for(elt=gauche; elt; elt = elt->next) {
    if(elt->id_noeud == 3) {
      printf("erreur voisin 3 présent\n");
      retour = false;
    }
  }
  for(elt=bas; elt; elt = elt->next) {
    if(elt->id_noeud == 3) {
      printf("erreur voisin 3 présent\n");
      retour = false;
    }
  }
  for(elt=droite; elt; elt = elt->next) {
    if(elt->id_noeud == 3) {
      printf("erreur voisin 3 présent\n");
      retour = false;
    }
  }
  for(elt=haut; elt; elt = elt->next) {
    if(elt->id_noeud == 3) {
      printf("erreur voisin 3 présent\n");
      retour = false;
    }
  }

  return retour;
}


bool zone_equal(int id_noeud, int minX, int maxX, int minY, int maxY) {
  zone *v;
  v = rechercheVoisin(id_noeud, minX, maxX, minY, maxY);
  if(!v) return false;
  if(v->id_noeud != id_noeud) return false;
  if(v->minX != minX) return false;
  if(v->maxX != maxX) return false;
  if(v->minY != minY) return false;
  if(v->maxY != maxY) return false;
  return true;
}

bool tests_traiter_maj_noeuds() {
  zone z1, z2, z3, z4;
  int retour = true;
  zone *elt;
  
  printf("Début test maj_zone\n");

  my_zone.id_noeud = 5;
  traiter_maj_zone(5, 101, 300, 201, 250);

  if(my_zone.id_noeud != 5 || my_zone.minX != 101 || 
     my_zone.maxX != 300 || my_zone.minY != 201 || my_zone.maxY != 250) {
    retour = false;
    printf("Erreur mauvaise mise à jour de my_zone\n");
  }

  /* Ajout des voisins */
  traiter_maj_zone(1, 91, 100, 221, 240);
  if(!zone_equal(1, 91, 100, 221, 240)) {
    retour = false;
    printf("Erreur ajout de 1\n");
  }

  traiter_maj_zone(2, 301, 500, 0, 300);
  if(!zone_equal(2, 301, 500, 0, 300)) {
    retour = false;
    printf("Erreur ajout de 1\n");
  }

  traiter_maj_zone(3, 101, 300, 0, 200);
  if(!zone_equal(3, 101, 300, 0, 200)) {
    retour = false;
    printf("Erreur ajout de 1\n");
  }

  traiter_maj_zone(4, 91, 100, 201, 220);
  if(!zone_equal(4, 91, 100, 201, 220)) {
    retour = false;
    printf("Erreur ajout de 1\n");
  }


  /* modification de voisins */
  traiter_maj_zone(1, 91, 95, 221, 240);
  if(rechercheVoisin(1, 91, 95, 221, 240)) {
    retour = false;
    printf("Erreur modification de 1 : non supprimé\n");
  }

  traiter_maj_zone(2, 301, 500, 0, 230);
  if(!zone_equal(2, 301, 500, 0, 230)) {
    retour = false;
    printf("Erreur modification de 2\n");
  }


  traiter_maj_zone(2, 301, 500, 0, 200);
  if(rechercheVoisin(2, 301, 500, 0, 200)) {
    retour = false;
    printf("Erreur modification de 2 : non supprimé\n");
  }

  traiter_maj_zone(2, 301, 500, 0, 201);
  if(rechercheVoisin(2, 301, 500, 0, 201)) {
    retour = false;
    printf("Erreur modification de 2 : non supprimé\n");
  }

  return retour;
}


int main() {
  if (!test_ajout_recherche_suppr_voisins()) {
    printf("Test voisins loupé\n");
  }
  if (!tests_traiter_maj_noeuds()) {
    printf("Test maj_noeuds loupé\n");
  }
}

