#include "gestion_com.h"

void boardcast_element_a_liste(zone* elem, int tag_msg, liste_zone liste){
	zone * curs= liste->prem;
	int msg[LEN_MAX_MSG]={elem->id_noeud, elem->minX, elem->maxX, elem->minY, elem->maxY};;

	while(curs != NULL){
		MPI_Send(msg, LEN_MAX_MSG, MPI_INT, curs->id_noeud, tag_msg, MPI_COMM_WORLD);
		/* printf("envoi msg[%d:%d:%d:%d:%d] à %d\n",elem->id_noeud, elem->minX, elem->maxX, elem->minY, elem->maxY, elem->id_noeud); */
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

		MPI_Send(msg, LEN_MAX_MSG, MPI_INT, dest->id_noeud, tag_msg, MPI_COMM_WORLD);
		/* printf("envoi msg[%d:%d:%d:%d:%d] a %d\n",curs->id_noeud, curs->minX, curs->maxX, curs->minY, curs->maxY, dest->id_noeud); */
		curs= curs->next;
	}

}


void envoyer_msg_au_adjacent(liste_zone lz, zone* z,  int* msg, int tag_msg){
	zone* curs= lz->prem;

	while(curs != NULL){
		if(est_adjacent(z, curs) == true){
			MPI_Send(msg, LEN_MAX_MSG, MPI_INT, curs->id_noeud, tag_msg, MPI_COMM_WORLD);
			/* printf("envoi msg[%d:%d:%d:%d:%d] a %d\n",msg[0], msg[1], msg[2], msg[3], msg[4], curs->id_noeud); */

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
		      
			MPI_Send(msg, LEN_MAX_MSG, MPI_INT, dest->id_noeud, tag_msg, MPI_COMM_WORLD);
			/* printf("envoi msg[%d:%d:%d:%d:%d] a %d\n",curs->id_noeud, curs->minX, curs->maxX, curs->minY, curs->maxY, dest->id_noeud); */

		}

		curs= curs->next;
	}
} 

void envoyer_message(int noeud, int *data, int tag) {
  MPI_Send(data, LEN_MAX_MSG, MPI_INT, noeud, tag, MPI_COMM_WORLD);
}

int attendreMessage(void) {
  MPI_Status status;
  int donnees[LEN_MAX_MSG];
  
  /* SAUF !! dans le cas initial, où on veux recevoir des messages à vie (et
     donc on ne recevra pas de ACK), la seule possibilitée de sortie est de
     recevoir un ack puisque si on entre dans attendreMessage, c'est qu'on
     attends une réponse  */
  while(1) {
    MPI_Recv(&donnees, LEN_MAX_MSG, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

    switch(status.MPI_TAG) {
    case ACK:
      /* Si une valeur est présente, on la renvoie. S'il n'y a pas de valeur, on
         la renvoie quand même. Elle sera non pertinente et ignorée par la
         fonction appelante qui ne cherche pas de retour */
      printf("noeud %d : ACK reçu (%d)\n", my_zone.id_noeud, donnees[1]);
      return donnees[1];
    case MAJ_ZONE:
      printf("noeud %d : MAJ_ZONE reçu\n", my_zone.id_noeud);
      traiter_maj_zone(donnees[0], donnees[1], donnees[2], donnees[3], donnees[4]);
      break;
    case INIT_ZONE:
      printf("noeud %d : INIT_ZONE reçu\n", my_zone.id_noeud);
      traiter_maj_zone(donnees[0], donnees[1], donnees[2], donnees[3], donnees[4]);
      break;
    case REQ_INSERE_TOI:
      printf("noeud %d : REQ_INSERE_TOI reçu\n", my_zone.id_noeud);
      traiter_requete_insere_toi(donnees[0]);
      break;
    case REQ_INSERTION_NOEUD:
      printf("noeud %d : REQ_INSERTION_NOEUD reçu\n", my_zone.id_noeud);
      traiter_requete_insertion_noeud(donnees[0], donnees[1], donnees[2]);
      break;
    case REQ_INSERTION_VALEUR:
      printf("noeud %d : REQ_INSERTION_VALEUR reçu\n", my_zone.id_noeud);
      traiter_requete_insertion_valeur(donnees[0], donnees[1], donnees[2], donnees[3]);
      break;
    case REQ_RECHERCHE_VALEUR:
      printf("noeud %d : REQ_RECHERCHE_VALEUR reçu\n", my_zone.id_noeud);
      traiter_requete_recherche_valeur(donnees[0], donnees[1], donnees[2]);
      break;
    case EXPORT:
      printf("noeud %d : EXPORT reçu\n", my_zone.id_noeud);
      traiter_export(donnees[0], donnees[1], donnees[2], donnees[3], donnees[4], donnees[5]);
      break;
    default:
      printf("NOEUD %d ERREUR TYPE MESSAGE %d\n", my_zone.id_noeud, status.MPI_TAG);
      break;
    }
  }
}

