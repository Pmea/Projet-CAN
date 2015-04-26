#include "gestion_com.h"

void boardcast_element_a_liste(zone* elem, int tag_msg, liste_zone liste){
	zone * curs= liste->prem;
	int msg[LEN_MAX_MSG]{elem->id_noeud, elem->minX, elem->maxX, elem->minY, elem->maxY};;

	while(curs != NULL){
		//MPI_Send(msg, LEN_MAX_MSG, MPI_INT, curs->id_noeud, tag_msg, MPI_COMM_WORLD);
		curs= curs->next;
	}
}

void envoyer_tous_liste_a_un(zone* dest, int tag_msg, liste_zone a_envoyer){
	zone * curs= a_envoyer->prem;
	int msg[LEN_MAX_MSG];

	while(curs != NULL){
		msg[0]=curs->id_noeud;
		msg[1]=curs->minX;
		msg[2]=curs->maxX;
		msg[3]=curs->minY;
		msg[4]=curs->maxY;

		//MPI_Send(msg, LEN_MAX_MSG, MPI_INT, dest, tag_msg, MPI_COMM_WORLD);
		curs= curs->next;
	}
}


// envoi un message au adjacent dans la liste
void envoyer_adjacent(liste_zone lz, zone* z, int* msg, int msg_tag){
	zone* curs= lz->prem;

	while(curs != NULL){
		if(est_adjacent(z, curs) == true){
			//MPI_Send(msg, LEN_MAX_MSG, MPI_INT, curs->id_noeud, tag_msg, MPI_COMM_WORLD);
		}
		curs= curs->next;
	}
}
