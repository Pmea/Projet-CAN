#include "can.h"



void envoyer_a_tous_element_liste(zone* curs_voisin, zone* new_zone, zone* my_zone){
	while(curs_voisin != NULL){
			int msg[LEN_MAX_MSG]={new_zone->id_noeud, new_zone->minX, new_zone->maxX, new_zone->minY, new_zone->maxY};			// pour le nouveaux noeud 
			//MPI_Send(msg, LEN_MAX_MSG, MPI_INT, curs_voisin->id_noeud, MAJ_ZONE, MPI_COMM_WORLD);

			msg[LEN_MAX_MSG]={my_zone.id_noeud, my_zone.minX, my_zone.maxX, my_zone.minY, my_zone.maxY};			// pour mon nouvelle espace
			//MPI_Send(msg, LEN_MAX_MSG, MPI_INT, curs_voisin->id_noeud, MAJ_ZONE, MPI_COMM_WORLD);
			
			curs_voisin= curs_voisin.next;
	}
}

void envoyer_elemnt_liste(zone* curs_voisin, zone zone_dest){
	while(curs_voisin != NULL){
			int msg[LEN_MAX_MSG]={curs_voisin->id_noeud, curs_voisin->minX, curs_voisin->maxX, curs_voisin->minY, curs_voisin->maxY};			// pour le nouveaux noeud 
			//MPI_Send(msg, LEN_MAX_MSG, MPI_INT, zone_dest.id_noeud, MAJ_ZONE, MPI_COMM_WORLD);			
			curs_voisin= curs_voisin->next;
	}
}

// amelioration a faire, pas d'envoie si c'est le coté ou ca ne change pas
void diviser(int id_noeud){
	zone* new_zone= (zone*) malloc(sizeof(struct zone_t));
	new_zone->id_noeud= id_noeud;
	
	new_zone->maxX= my_zone.maxX;
	new_zone->minX= my_zone.minX;

	new_zone->maxY= my_zone.maxY;
	new_zone->minY= my_zone.minY;


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

	printf("id: %d\n", new_zone->id_noeud);
	printf("minX:%d maxX:%d\n", new_zone->minX, new_zone->maxX);
	printf("minY:%d maxY:%d\n", new_zone->minY, new_zone->maxY);

	// mis a jour mes voisins // ajout du nouveux noeud
	int msg[LEN_MAX_MSG]={ new_zone->id_noeud, new_zone->minX, new_zone->maxX, new_zone->minY, new_zone->maxY};
	MPI_Send(msg, LEN_MAX_MSG, MPI_INT, id_noeud, INIT_ZONE, MPI_COMM_WORLD);										//prevenir le zone init	

	envoyer_a_tous_element_liste(gauche, *new_zone, my_zone);
	envoyer_a_tou_element_liste(droite, *new_zone, my_zone);
	envoyer_a_tous_element_liste(haut, *new_zone, my_zone);
	envoyer_a_tous_element_liste(bas, *new_zone, my_zone));


	// -> dispatch voisins 
	// savoir de quel cote il est
	// partager voisin
	// ajouter a ma liste de voir sin

	switch(quel_cote(my_zone, new_zone)){			// je lui donne mes voisins
		case DROITE:					// l'autre est a droite donc je suis a gauche
			// partage haut
			// partage bas
			envoyer_element_liste(haut, new_zone);
			envoyer_element_liste(bas, new_zone);
			envoyer_element_liste(my_zone, new_zone);					
			envoyer_element_liste(droite, new_zone);

			vider_liste_zone(droite);
			droite= ajouter_entete_liste_zone(new_zone);

			supprimer_voisin_non_adjacent(haut ,&my_zone);
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
			gauche= ajouter_entete_liste_zone(new_zone);

			// pour tous les voisins H/B on 
			supprimer_voisin_non_adjacent(haut, &my_zone);
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
			haut= ajouter_entete_liste_zone(new_zone);

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
			bas= ajouter_entete_liste_zone(new_zone);	

			supprimer_voisin_non_adjacent(gauche, new_zone, &my_zone);
			supprimer_voisin_non_adjacent(droite, new_zone, &my_zone);

			break;
		default:
			printf("Mauvaise direction\n");
			exit(EXIT_FAILURE);
	}

	// dispatch  data
}


//suprimer_voisin  supprime 

void vider_liste_zone(zone* z){
	while(z!= NULL){
		free(z);
		z=z->next;
	}
}

void ajouter_entete_liste_zone(zone* z, zone* new){
	if(z== NULL)
		z=new;
	else{
		new->next= z;
		z=new;
	}
}

void supprimer_voisin_non_adjacent(zone* curs_voisin, zone* my_zone){
			while(curs_voisin!= NULL){
				if(!est_adjacent(&my_zone, new_zone)){
					supprimerVoisin(curs_voisin.id_noeud, curs_voisin.minX, curs_voisin.maxX, curs_voisin.minY, curs_voisin.minX);
				}
				curs_voisin=curs_voisin->next;
			}
}


bool est_adjacent(zone z1, zone z2){
	if((z1.maxX == z2.minX -1 && (z1.minY < z2.maxY || z1.maxY < z2.minY))	||			
		(z2.maxX == z1.minX -1 && (z1.minY < z2.maxY || z1.maxY < z2.minY))	||			
		(z1.maxY == z2.minY -1 && (z1.minX < z2.maxX || z1.maxX < z2.minX))	||			
		(z2.maxY == z1.minY -1 && (z1.minX < z2.maxX || z1.maxX < z2.minX))){
		return true;
	}
	return false;
}

	