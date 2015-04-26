#include "gestion_com.h"

void boardcast_element_a_liste(zone* elem, int tag_msg, liste_zone liste){
	zone * curs= liste->prem;
	int msg[LEN_MAX_MSG]{elem->id_noeud, elem->minX, elem->maxX, elem->minY, elem->maxY};;

	while(curs != NULL){
		//MPI_Send(msg, LEN_MAX_MSG, MPI_INT, curs->id_noeud, tag_msg, MPI_COMM_WORLD);
		printf("envoi msg[%d:%d:%d:%d:%d] a %d\n",curs->id_noeud, curs->minX, curs->maxX, curs->minY, curs->maxY, dest->id_noeud);
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
		printf("envoi msg[%d:%d:%d:%d:%d] a %d\n",curs->id_noeud, curs->minX, curs->maxX, curs->minY, curs->maxY, dest->id_noeud);
		curs= curs->next;
	}
}


void envoyer_msg_au_adjacent(liste_zone lz, zone* z, int* msg, int tag_msg){
	zone* curs= lz->prem;

	while(curs != NULL){
		if(est_adjacent(z, curs) == true){
			//MPI_Send(msg, LEN_MAX_MSG, MPI_INT, curs->id_noeud, tag_msg, MPI_COMM_WORLD);
			printf("envoi msg[%d:%d:%d:%d:%d] a %d\n",curs->id_noeud, curs->minX, curs->maxX, curs->minY, curs->maxY, dest->id_noeud);

		}
		curs= curs->next;
	}
}

void envoyer_info_tous_adjacent_a_un(liste_zone liste, zone* dest, int tag_msg){
	zone* curs= liste->prem;
	int msg[LEN_MAX_MSG];

	while(curs != NULL){
		if(est_adjacent(dest, curs)== true){
			msg[0]=curs->id_noeud;
			msg[1]=curs->minX;
			msg[2]=curs->maxX;
			msg[3]=curs->minY;
			msg[4]=curs->maxY;
			
			//MPI_Send(msg, LEN_MAX_MSG, MPI_INT, dest, tag_msg, MPI_COMM_WORLD);
			printf("envoi msg[%d:%d:%d:%d:%d] a %d\n",curs->id_noeud, curs->minX, curs->maxX, curs->minY, curs->maxY, dest->id_noeud);

		}

		curs= curs->next;
	}
} 