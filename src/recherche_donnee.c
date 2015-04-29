#include "can.h"


bool traiter_requete_recherche_valeur(int nd_init, int x, int y){
	if(point_dans_zone(x, y) == true){

		int msgUseless[LEN_MAX_MSG]={0};
		msgUseless[0]= nd_init;
		donnee * tmp_don;
		if((tmp_don =get_donnee(my_donnee, x, y)) !=NULL){
			printf("DONNEE TROUVE sur le noeud: %d\n", my_zone.id_noeud);
			msgUseless[1]= tmp_don->data;		
		}
		else{
			msgUseless[1]= -1;	
		}
		envoyer_message(nd_init, msgUseless, ACK);
	}
	else{
		int id_route= routage(x,y);
		int msg[LEN_MAX_MSG]= {nd_init, x, y};
		envoyer_message(id_route, msg, REQ_RECHERCHE_VALEUR);
	}

  return true;
}
