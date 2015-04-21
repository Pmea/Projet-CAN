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
