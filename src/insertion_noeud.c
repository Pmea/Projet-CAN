#include "can.h"




void diviser(int id_noeud){
	zone new_zone;
	new_zone.id_noeud= id_noeud;
	
	new_zone.maxX= my_zone.maxX;
	new_zone.minX= my_zone.minX;

	new_zone.maxY= my_zone.maxY;
	new_zone.minY= my_zone.minY;

	zone* curs_voisin;


	if((my_zone.maxX - my_zone.minX) >= (my_zone.maxY - my_zone.minY) ){			// si largeur plus grand
		my_zone.maxX= (my_zone.maxX - my_zone.minX) / 2 - 1;
		new_zone.maxX= my_zone.maxX;

		//prevenir les voisins

		if((abs(my_zone.minX-my_x))>(abs(new_zone.maxX-my_x))){				// si a droite
			curs_voisin= gauche;
		}
		else{			// si a gauche
			curs_voisin= droite;
		}
	}

	else{
		my_zone.maxY= (my_zone.maxY- my_zone.minY) / 2 - 1;
		new_zone.maxY= my_zone.maxY;
	
		//prevenir les voisins

		if((abs(my_zone.minY-my_y))>(abs(new_zone.maxY-my_y))){				// si en bas
			curs_voisin= haut;
		}
		else{			// si en haut
			curs_voisin= bas;
		}
	}


	int msg[LEN_MAX_MSG]={ new_zone.id_noeud, new_zone.minX, new_zone.maxX, new_zone.minY, new_zone.maxY};
	MPI_Send(msg, LEN_MAX_MSG, MPI_INT, curs_voisin->id_noeud, INIT_ZONE, MPI_COMM_WORLD);					//prevenir le zone init


	while(curs_voisin != NULL){
		//prevenir les voisins
		MPI_Send(msg, LEN_MAX_MSG, MPI_INT, curs_voisin->id_noeud, MAJ_ZONE, MPI_COMM_WORLD);

		curs_voisin= curs_voisin->next;
	}
}


bool traiter_requete_insere_toi(int nd_init) {
  printf("TODO : traiter_requete_insere_toi\n");
  return false;
}

bool traiter_requete_insertion_noeud(int id_noeud, int x, int y) {
  printf("TODO : traiter_requete_insertion_noeud\n");
  return false;
}

/* traiter_maj_zone reçoit l'id du noeud modifié et sa nouvelle zone */
/* 
   Si l'id est le notre, on mets à jour nos propres valeurs.  
   Si l'id est celui d'un voisin, on mets à jour le voisin et on le supprime si
     ce n'en est plus un 
   Si l'id n'est pas un voisin, on le créé et on l'ajoute si c'est effectivement
   un voisin
*/
bool traiter_maj_zone(int noeud, int minX, int maxX, int minY, int maxY) {
  zone *v;
  
  if(noeud == my_zone.id_noeud) {
    /* Cas ou on mets à jour sa propre zone */
    my_zone.minX = minX;
    my_zone.maxX = maxX;
    my_zone.minY = minY;
    my_zone.maxY = maxY;
  } else {
    /* Cas ou on mets à jour un voisin */
    v = rechercheVoisin(noeud, minX, maxX, minY, maxY);
    if(v) {
      /* Déjà voisin : On le mets à jour */
      v->minX = minX;
      v->maxX = maxX;
      v->minY = minY;
      v->maxY = maxY;
      if(!est_adjacent(&my_zone, v)) {
        /* Si v n'est plus un voisin on le supprime */
        supprimerVoisin(v->id_noeud, v->minX, v->maxX, v->minY, v->maxY);
        free(v);
      }
    } else {
      /* Nouveau voisin : on l'ajoute */
      v = (zone*) malloc(sizeof(zone));
      v->id_noeud = noeud;
      v->minX = minX;
      v->maxX = maxX;
      v->minY = minY;
      v->maxY = maxY;
      if(est_adjacent(&my_zone, v))
        ajouterVoisin(v);
      else
        free(v);
    }
  }

  return true;
}

