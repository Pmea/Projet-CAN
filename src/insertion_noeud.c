#include "can.h"

// Divise ma zone en deux, que je 
void diviser(int id_noeud){
	zone* new_zone= creer_zone(id_noeud, my_zone.minX, my_zone.maxX, my_zone.minY, my_zone.maxY, NULL);

	if((my_zone.maxX - my_zone.minX) >= (my_zone.maxY - my_zone.minY) ){			
    // si largeur plus grand
    // on decoupe verticalmeent
		my_zone.maxX= my_zone.minX + (my_zone.maxX - my_zone.minX) / 2 - 1;    
		new_zone->minX= my_zone.maxX + 1;

		if( x_dans_zone(my_x) == false){   // si je mes coordonnee ne sont pas dans la zone que je viens de decouper
			int minXtmp= my_zone.minX;       // j'echange avec le noeud qui veut s'inserer
			int maxXtmp= my_zone.maxX;

			my_zone.maxX= new_zone->maxX;
			my_zone.minX= new_zone->minX;

			new_zone->minX= minXtmp;
			new_zone->maxX= maxXtmp;
		}
	}

	else{
    // si largeur plus grand
    // on decoupe verticalmeent
		my_zone.maxY= my_zone.minY +(my_zone.maxY- my_zone.minY) / 2 - 1;
		new_zone->minY= my_zone.maxY + 1;

		if( y_dans_zone(my_y) == false){
			int minYtmp= my_zone.minY;
			int maxYtmp= my_zone.maxY;

			my_zone.maxY= new_zone->maxY;
			my_zone.minY= new_zone->minY;

			new_zone->minY= minYtmp;
			new_zone->maxY= maxYtmp;
		}
	}


	int msg[LEN_MAX_MSG]={ new_zone->id_noeud, new_zone->minX, new_zone->maxX, new_zone->minY, new_zone->maxY};	
  // envoi les coordonnées au nouveau noeud
  envoyer_message(new_zone->id_noeud, msg, INIT_ZONE);

  // propagation de l'information a mes voisin
	envoyer_msg_au_adjacent(gauche, new_zone, msg, MAJ_ZONE);
	envoyer_msg_au_adjacent(droite, new_zone, msg, MAJ_ZONE);
	envoyer_msg_au_adjacent(haut, new_zone, msg, MAJ_ZONE);
	envoyer_msg_au_adjacent(bas, new_zone, msg, MAJ_ZONE);

  // je donne mes coordonner au nouveau noeud
  msg[0]= my_zone.id_noeud;
  msg[1]= my_zone.minX;
  msg[2]= my_zone.maxX;
  msg[3]= my_zone.minY;
  msg[4]= my_zone.maxY;
  envoyer_message(new_zone->id_noeud, msg, MAJ_ZONE);

	switch(dequel_cote(&my_zone, new_zone)){			
		case DROITE:					// l'autre est a droite donc je suis a gauche
			
        // je lui envoi mes voisins qui son adjacent au nouveau noeud
				envoyer_info_tous_adjacent_a_un(bas, new_zone, MAJ_ZONE);     
				envoyer_info_tous_adjacent_a_un(haut, new_zone, MAJ_ZONE);

        // je supprimer les voisins qui ne sont plus adjacent avec moi
				supprimer_voisin_non_adjacent(bas, &my_zone);
				supprimer_voisin_non_adjacent(haut, &my_zone);

        // j'envoi ma coorodnnee au nouveau noeud pour qu'il m'ajoute a ses voisins
				envoyer_tous_liste_a_un(new_zone, MAJ_ZONE, droite);

        // je l'ajoute a mes voisins de droite comme ces lui maintenant mon unique voisin
				vider_liste(droite);
				ajouter_entete_liste(droite, new_zone);
			break;
		case GAUCHE:           // idem mais pour les autres directions

				envoyer_info_tous_adjacent_a_un(bas, new_zone, MAJ_ZONE);
				envoyer_info_tous_adjacent_a_un(haut, new_zone, MAJ_ZONE);

				supprimer_voisin_non_adjacent(bas, &my_zone);
				supprimer_voisin_non_adjacent(haut, &my_zone);

				envoyer_tous_liste_a_un(new_zone, MAJ_ZONE, gauche);	

				vider_liste(gauche);
				ajouter_entete_liste(gauche, new_zone);
			break; 
		case HAUT:

				envoyer_info_tous_adjacent_a_un(droite, new_zone, MAJ_ZONE);
				envoyer_info_tous_adjacent_a_un(gauche, new_zone, MAJ_ZONE);

				supprimer_voisin_non_adjacent(droite, &my_zone);
				supprimer_voisin_non_adjacent(gauche, &my_zone);

				envoyer_tous_liste_a_un(new_zone, MAJ_ZONE, haut);

				vider_liste(haut);
				ajouter_entete_liste(haut, new_zone);
			break;
		case BAS:

				envoyer_info_tous_adjacent_a_un(droite, new_zone, MAJ_ZONE);
				envoyer_info_tous_adjacent_a_un(gauche, new_zone, MAJ_ZONE);

				supprimer_voisin_non_adjacent(droite, &my_zone);
				supprimer_voisin_non_adjacent(gauche, &my_zone);

				envoyer_tous_liste_a_un(new_zone, MAJ_ZONE, bas);

				vider_liste(bas);
				ajouter_entete_liste(bas, new_zone);
			break;
		default:
			printf("Mauvaise direction\n");
			exit(EXIT_FAILURE);
	}
	
	// Si nous voulions ajouter l'insertion de noeud apres la distribution de donnee, il faudrai faire
  // une mise a jour des donnees, comme pour les voisins, pour savoir lesquelles j'envoi au nouveau noeud 
}




bool traiter_requete_insere_toi(int nd_init) {
  /* Envoyer un message insertion noeud au bootstrap, attendre une réponse de
     type ack et envoyer un ack au coordinateur */
  int data[LEN_MAX_MSG];


  if(my_zone.id_noeud == BOOTSTRAP) {   /* Cas initial */
    /* Mettre à jour sa zone */
    my_zone.minX = 0;
    my_zone.maxX = LARGEUR_GRILLE;
    my_zone.minY = 0;
    my_zone.maxY = HAUTEUR_GRILLE;
    data[1] = 1;
  } else {
    /* Envoyer la requête d'insertion de noeud et attendre l'ACK */
    data[0] = my_zone.id_noeud;
    data[1] = my_x;
    data[2] = my_y;
    envoyer_message(BOOTSTRAP, data, REQ_INSERTION_NOEUD);
    data[1] = attendreMessage();
  }

  /* Mettre à jour son état si l'insertion a réussie */
  if(data[1])
    est_insere = true;
  data[0] = COORDINATEUR;
  /* data[1] représente toujours le succès de l'insertion */
  envoyer_message(COORDINATEUR, data, ACK);
  return true;
}

/* Retourne vrai si la zone est assez grande pour être divisée */
bool est_divisible_zone(zone *z) {
  if(z->maxX - z->minX > 1 || z->maxY - z->minY > 1)
    return true;
  return false;
}

bool traiter_requete_insertion_noeud(int id_noeud, int x, int y) {
  /* Si le noeud veut s'insérer dans mon espace => je me divise (la division
     mets à jours les voisins) et j'envoie un ACK au nouveau noeud (qui est
     maintenant mon voisin) */

  if(point_dans_zone(x,y) == true){

    /* Si la zone n'est pas divisible, on retourne faux au noeud qui cherche à
       s'insérer  */
    if(!est_divisible_zone(&my_zone)) {
      int msg[LEN_MAX_MSG];
      msg[0] = id_noeud;
      msg[1] = 0;
      envoyer_message(id_noeud, msg, ACK);
      return false;
    }
    diviser(id_noeud);
    int msgUseless[LEN_MAX_MSG]={0};
    msgUseless[0]= id_noeud;
    msgUseless[1] = 1;
    envoyer_message(id_noeud, msgUseless, ACK);
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

// tire un nouveau point dans la zone, si ses coordonnées ne sont pas bonnes
void tirer_point_dans_zone(){
  if( x_dans_zone(my_x) == false){
    my_x= rand() % ( my_zone.maxX - my_zone.minX + 1);
    my_x+= my_zone.minX;
  }
  if( y_dans_zone(my_y) == false){
    my_y= rand() %  (my_zone.maxY - my_zone.minY + 1);
    my_y+= my_zone.minY;
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
    if( point_dans_zone(my_x, my_y) == false){		   // on ne peut y passer qu'une seul fois
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
      else                     
        detruire_zone(v);
    }
  }
  
  return true;
}


/* DEBUG */
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
	my_x= 150;
	my_y= 350;

	diviser(z2.id_noeud);

	printf("test passé avec SUCCES\n");
	return EXIT_SUCCESS;
}
*/
