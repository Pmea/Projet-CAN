#include "can.h"
#include "insertion_noeud.h"

//la division marche 
void diviser(int id_noeud){
	zone* new_zone= creer_zone(id_noeud, my_zone.minX, my_zone.maxX, my_zone.minY, my_zone.maxY, NULL);

	if((my_zone.maxX - my_zone.minX) >= (my_zone.maxY - my_zone.minY) ){			// si largeur plus grand
		printf("DECOUPAGE VERTICAL\n");
		my_zone.maxX= my_zone.minX + (my_zone.maxX - my_zone.minX) / 2 - 1;
		new_zone->minX= my_zone.maxX + 1;
	}

	else{
		printf("DECOUPAGE HORIZONTAL\n");
		my_zone.maxY= my_zone.minY +(my_zone.maxY- my_zone.minY) / 2 - 1;
		new_zone->minY= my_zone.maxY + 1;
	}


	afficher_zone(&my_zone);
	afficher_zone(new_zone);
/*
	// mis a jour mes voisins // ajout du nouveux noeud
	int msg[LEN_MAX_MSG]={ new_zone->id_noeud, new_zone->minX, new_zone->maxX, new_zone->minY, new_zone->maxY};
	MPI_Send(msg, LEN_MAX_MSG, MPI_INT, id_noeud, INIT_ZONE, MPI_COMM_WORLD);										//prevenir le zone init	

	envoyer_a_tous_element_liste(gauche, new_zone, &my_zone);
	envoyer_a_tou_element_liste(droite, new_zone, &my_zone);
	envoyer_a_tous_element_liste(haut, new_zone, &my_zone);
	envoyer_a_tous_element_liste(bas, new_zone, &my_zone);
*/

	// -> dispatch voisins 
	// savoir de quel cote il est
	// partager voisin
	// ajouter a ma liste de voir sin
	/*
	direction dir;
	dir= quel_cote( my_zone, new_zone);
	switch(dir){			// je lui donne mes voisins
		case DROITE:					// l'autre est a droite donc je suis a gauche
			// partage haut
			// partage bas
			envoyer_element_liste(haut, new_zone);
			envoyer_element_liste(bas, new_zone);
			envoyer_element_liste(my_zone, new_zone);					
			envoyer_element_liste(droite, new_zone);

			vider_liste_zone(droite);
			ajouter_entete_liste_zone(droite, new_zone);
				//revoir ce code
			supprimer_voisin_non_adjacent(haut, &my_zone);
			supprimer_voisin_non_adjacent(bas, &my_zone);

			break;
		case GAUCHE:
			// partage haut
			// partage bas 
			envoyer_element_liste(haut, new_zone);
			envoyer_element_liste(bas, new_zone);
			envoyer_element_liste(gauche, new_zone);					
			envoyer_element_liste(my_zone, new_zone);
			
			vider_liste_zone(gauche);
			ajouter_entete_liste_zone(gauche, new_zone);

			// pour tous les voisins H/B on 
			supprimer_voisin_non_adjacent(haut,&my_zone);
			supprimer_voisin_non_adjacent(bas, &my_zone);

			break; 
		case HAUT:
			// partage droite
			// partage gauche
			envoyer_element_liste(haut, new_zone);
			envoyer_element_liste(my_zone, new_zone);
			envoyer_element_liste(gauche, new_zone);					
			envoyer_element_liste(droite, new_zone);

			vider_liste_zone(haut);
			ajouter_entete_liste_zone(haut, new_zone);

			supprimer_voisin_non_adjacent(gauche, &my_zone);
			supprimer_voisin_non_adjacent(droite, &my_zone);

			break;
		case BAS:
			// partage droite
			// partage gauche	
			envoyer_element_liste(my_zone, new_zone);
			envoyer_element_liste(bas, new_zone);
			envoyer_element_liste(gauche, new_zone);					
			envoyer_element_liste(droite, new_zone);

			vider_liste_zone(bas);
			ajouter_entete_liste_zone(bas, new_zone);	

			supprimer_voisin_non_adjacent(gauche, &my_zone);
			supprimer_voisin_non_adjacent(droite, &my_zone);

			break;
		default:
			printf("Mauvaise direction\n");
			exit(EXIT_FAILURE);
	}*/

	// dispatch  data
			printf("fin\n");
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
  /*zone *v;
  
  if(noeud == my_zone.id_noeud) {
    // Cas ou on mets à jour sa propre zone 
    my_zone.minX = minX;
    my_zone.maxX = maxX;
    my_zone.minY = minY;
    my_zone.maxY = maxY;
  } else {
    // Cas ou on mets à jour un voisin 
    v = rechercheVoisin(noeud, minX, maxX, minY, maxY);
    if(v) {
      // Déjà voisin : On le mets à jour 
      v->minX = minX;
      v->maxX = maxX;
      v->minY = minY;
      v->maxY = maxY;
      if(!est_adjacent(&my_zone, v)) {
        // Si v n'est plus un voisin on le supprime 
        supprimerVoisin(v->id_noeud, v->minX, v->maxX, v->minY, v->maxY);
        free(v);
      }
    } else {
      // Nouveau voisin : on l'ajoute 
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
*/
  return true;
}


int main(int argc, char* argv[]){				// fonction de test
	printf("Fonction de test\n");
	zone z1,z2;
	z1.id_noeud= 1;
	z1.minX= 100;
	z1.maxX= 200;
	z1.minY= 300;
	z1.maxY= 400;
	z1.next= NULL;


	z2.id_noeud= 1;
	z2.minX= 201;
	z2.maxX= 300;
	z2.minY= 100;
	z2.maxY= 600;
	z2.next= NULL;

	my_zone= z1;

	diviser(z2.id_noeud);

	printf("test passé avec SUCCES\n");
	return EXIT_SUCCESS;
}
