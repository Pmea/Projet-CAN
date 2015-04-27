#include "can.h"

//la division marche 
void diviser(int id_noeud){
	zone* new_zone= creer_zone(id_noeud, my_zone.minX, my_zone.maxX, my_zone.minY, my_zone.maxY, NULL);

	if((my_zone.maxX - my_zone.minX) >= (my_zone.maxY - my_zone.minY) ){			// si largeur plus grand
		printf("DECOUPAGE VERTICAL\n");
		my_zone.maxX= my_zone.minX + (my_zone.maxX - my_zone.minX) / 2 - 1;
		new_zone->minX= my_zone.maxX + 1;

		// ajouter pour lui envoyer la partie ou je ne suis pas 
	}

	else{
		printf("DECOUPAGE HORIZONTAL\n");
		my_zone.maxY= my_zone.minY +(my_zone.maxY- my_zone.minY) / 2 - 1;
		new_zone->minY= my_zone.maxY + 1;
	}


	afficher_zone(&my_zone);
	afficher_zone(new_zone);

	// propagation de l'information
	int msg[LEN_MAX_MSG]={ new_zone->id_noeud, new_zone->minX, new_zone->maxX, new_zone->minY, new_zone->maxY};	
	envoyer_msg_au_adjacent(gauche, new_zone, msg, INIT_ZONE);
	envoyer_msg_au_adjacent(droite, new_zone, msg, INIT_ZONE);
	envoyer_msg_au_adjacent(haut, new_zone, msg, INIT_ZONE);
	envoyer_msg_au_adjacent(bas, new_zone, msg, INIT_ZONE);

	switch(dequel_cote(&my_zone, new_zone)){			
		case DROITE:					// l'autre est a droite donc je suis a gauche
			
				envoyer_info_tous_adjacent_a_un(bas, new_zone, MAJ_ZONE);
				envoyer_info_tous_adjacent_a_un(haut, new_zone, MAJ_ZONE);

				supprimer_voisin_non_adjacent(bas, &my_zone);
				supprimer_voisin_non_adjacent(haut, &my_zone);

				envoyer_tous_liste_a_un(new_zone, MAJ_ZONE, droite);

				vider_liste(droite);
				ajouter_entete_liste(droite, new_zone);
			break;
		case GAUCHE:

				envoyer_info_tous_adjacent_a_un(bas, new_zone, MAJ_ZONE);
				envoyer_info_tous_adjacent_a_un(haut, new_zone, MAJ_ZONE);

				supprimer_voisin_non_adjacent(bas, &my_zone);
				supprimer_voisin_non_adjacent(haut, &my_zone);

				envoyer_tous_liste_a_un(new_zone, MAJ_ZONE, droite);	

				vider_liste(gauche);
				ajouter_entete_liste(gauche, new_zone);
			break; 
		case HAUT:

				envoyer_info_tous_adjacent_a_un(droite, new_zone, MAJ_ZONE);
				envoyer_info_tous_adjacent_a_un(gauche, new_zone, MAJ_ZONE);

				supprimer_voisin_non_adjacent(droite, &my_zone);
				supprimer_voisin_non_adjacent(gauche, &my_zone);

				envoyer_tous_liste_a_un(new_zone, MAJ_ZONE, droite);

				vider_liste(haut);
				ajouter_entete_liste(haut, new_zone);
			break;
		case BAS:

				envoyer_info_tous_adjacent_a_un(droite, new_zone, MAJ_ZONE);
				envoyer_info_tous_adjacent_a_un(gauche, new_zone, MAJ_ZONE);

				supprimer_voisin_non_adjacent(droite, &my_zone);
				supprimer_voisin_non_adjacent(gauche, &my_zone);

				envoyer_tous_liste_a_un(new_zone, MAJ_ZONE, droite);

				vider_liste(bas);
				ajouter_entete_liste(bas, new_zone);
			break;
		default:
			printf("Mauvaise direction\n");
			exit(EXIT_FAILURE);
	}
	
	// dispatch  data
}




bool traiter_requete_insere_toi(int nd_init) {
  /* Envoyer un message insertion noeud au bootstrap, attendre une réponse de
     type ack et envoyer un ack au coordinateur */
  int data[LEN_MAX_MSG];
  data[0] = my_zone.id_noeud;
  data[1] = my_x;
  data[2] = my_y;

  envoyer_message(BOOTSTRAP, data, REQ_INSERTION_NOEUD);
  attendreMessage();
  printf("J'ai pas envie d'envoyer NULL mais on pourrait y réféchir\n");
  envoyer_message(COORDINATEUR, data, ACK);
  return true;
}



bool traiter_requete_insertion_noeud(int id_noeud, int x, int y) {
  /* Si le noeud c'est moi dans mon espace=> je me divise (les voisins seront mis à jour) et
     j'envoie un message de type "ACK" au coordinateur (qui est maintenant un
     voisin) */
  if(point_dans_zone(x,y) == true){
  	diviser(id_noeud);
  	int msgUseless[LEN_MAX_MSG]={0};
  	envoyer_message(COORDINATEUR, msgUseless, ACK);
  }
    /* Sinon, je cherche à qui je devrai envoyer le message (avec router) et je
     lui envoie un message "REQ_INSERTION_NOEUD" avec id_noeud, x et y */
  else{
  	int id_route= routage(x,y);
  	int msg[LEN_MAX_MSG]={id_noeud, x, y};
  	envoyer_message(id_route, msg, REQ_INSERTION_NOEUD);
  }

  return true;
}



void tirer_point_dans_zone(){
  while( x_dans_zone(my_x) == false){
    my_x= rand() % ( my_zone.maxX - my_zone.minX);
  }
  while( y_dans_zone(my_y) == false){
    my_y= rand() % ( my_zone.maxY - my_zone.minY);
  }
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
  liste_zone l;
  zone *v;

  if(noeud == my_zone.id_noeud) {
    // Cas ou on mets à jour sa propre zone 
    my_zone.minX = minX;
    my_zone.maxX = maxX;
    my_zone.minY = minY;
    my_zone.maxY = maxY;

    // si le point n'est pas dans ma zone
    if( point_dans_zone(my_x, my_y) == false){					// on ne doit y passer qu'une seul fois
    	// on retir jusqu'a qu'il le soit
		tirer_point_dans_zone();
	}	
  } else {
    // Cas ou on mets à jour un voisin 
    l = get_liste_zone_par_coor(minX, maxX, minY, maxY);
    v = get_zone_par_id(l, noeud);
    if(v) {
      // Déjà voisin : On le mets à jour 
      v->minX = minX;
      v->maxX = maxX;
      v->minY = minY;
      v->maxY = maxY;
      if(!est_adjacent(&my_zone, v)) {
        // Si v n'est plus un voisin on le supprime 
        supprimer_element_liste(l, v);
      }
    } else {
      // Nouveau voisin : on l'ajoute 
      v = creer_zone(noeud, minX, maxX, minY, maxY, NULL);
      if(est_adjacent(&my_zone, v))
        ajouter_entete_liste(l, v);
      else                      /* Ou pas */
        detruire_zone(v);
    }
  }
  return true;
}


/*
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
*/