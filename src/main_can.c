#include "can.h"

/* Ajoute v à une des liste de voisins */
/* Le voisin doit etre un voisin, il n'y a pas de vérification !! */
bool ajouterVoisin(zone *v) {
  if (v->maxX < my_zone.minX) {
    v->next = gauche;
    gauche = v;
  } else if (v->minX > my_zone.maxX) {
    v->next = droite;
    droite = v;
  } else if (v->maxY < my_zone.minY) {
    v->next = bas;
    bas = v;
  } else /* if (v->minY > my_zone.maxY) */ {
    v->next = haut;
    haut = v;
  }

  return true;
}

// Retourne 
zone *rechercheVoisin(int id, int minX, int maxX, int minY, int maxY) {
  zone *elt;

  if (v->maxX < my_zone.minX) {
    for(elt = gauche; elt; elt = elt->next) {
      if(elt->id == id) return elt;
    }
  } else if (v->minX > my_zone.maxX) {
    for(elt = droite; elt; elt = elt->next) {
      if(elt->id == id) return elt;
    }
  } else if (v->maxY < my_zone.minY) {
    for(elt = bas; elt; elt = elt->next) {
      if(elt->id == id) return elt;
    }
  } else /* if (v->minY > my_zone.maxY) */ {
    for(elt = haut; elt; elt = elt->next) {
      if(elt->id == id) return elt;
    }
  }

  return NULL;
}

void attendreMessage(void) {
  MPI_Status status;
  int donnees[LEN_MAX_MSG];
  
  while(1) {
    MPI_Recv(&donnees, LEN_MAX_MSG, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

    switch(status.MPI_TAG) {
    case ACK:
      return;
    case MAJ_ZONE:
      traiter_maj_zone(donnees[0], donnees[1], donnees[2], donnees[3], donnees[4]);
      return;
    case INIT_ZONE:
      traiter_maj_zone(donnees[0], donnees[1], donnees[2], donnees[3], donnees[4]);
      return;
    case REQ_INSERE_TOI:
      traiter_requete_insere_toi(donnees[0]);
      return;
    case REQ_INSERTION_NOEUD:
      traiter_requete_insertion_noeud(donnees[0], donnees[1], donnees[2]);
      return;
    case REQ_INSERTION_VALEUR:
      traiter_requete_insertion_valeur(donnees[0], donnees[1], donnees[2], donnees[3]);
      return;
    case REQ_RECHERCHE_VALEUR:
      traiter_requete_recherche_valeur(donnees[0], donnees[1], donnees[2]);
      return;
    }
  }
}


