#include "can.h"

bool traiter_requete_insertion_valeur(int nd_init, int x, int y, int val) {
	if(point_dans_zone(x, y) == true){
		donnee* new_data= creer_donnee(x,y,val, NULL);
		int msgUseless[LEN_MAX_MSG]={0};

		if(!est_dans_liste_donnee(my_donnee, new_data)){
			ajouter_entete_liste_donnee(my_donnee, new_data);
			msgUseless[0]=1;
		}

		envoyer_message(nd_init, msgUseless, ACK);
	}
	else{
		int id_route= routage(x,y);
		int msg[LEN_MAX_MSG]= {nd_init, x, y, val};
		envoyer_message(id_route, msg, REQ_INSERTION_VALEUR);
	}

  return true;
}


