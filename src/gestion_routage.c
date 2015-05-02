#include "gestion_routage.h"

#define NB_DIR 4


// retourne une zone  pioche au hasard
zone* zone_au_hasard_dans_liste(liste_zone liste){
	int compt=0;
	zone* curs= liste->prem;
	while(curs != NULL){
		compt++;
		curs= curs->next;
	}

	int choix= rand()% compt;
	
	curs= liste->prem;
	for(int i=0; i<choix; i++)
		curs=curs->next;
	return curs;
}

// retourne une liste valide pioche au hasard
liste_zone liste_au_hasard_dans_liste(bool *dir_possible){

	int choix= rand()% 4; 

	int inc=0;

	while(dir_possible[(choix + inc) % 4] != true){
		inc++;
	}

	switch((choix+inc)%4){
		case HAUT:
			return haut;
		case DROITE:
			return droite;
		case BAS:
			return bas;
		case GAUCHE:
			return gauche;
		default:
			printf("Erreur, de choix de liste\n");
			exit(EXIT_FAILURE);
	}
}


int routage(int x,  int y){
	bool dir[NB_DIR]= {false};			// 0:haut, 1:droite, 2:bas, 3:gauche

	if(x > my_zone.maxX )
		dir[DROITE]=true;
	if(x < my_zone.minX )
		dir[GAUCHE]=true;
	if(y > my_zone.maxY)
		dir[HAUT]=true;
	if(y < my_zone.minY)
		dir[BAS]=true;

	liste_zone ltmp= liste_au_hasard_dans_liste(dir);
	zone * tmp= zone_au_hasard_dans_liste(ltmp);

	return tmp->id_noeud;
}



/* DEBBUG */

/*
int main(int argc, char* argv[]){
	printf("DEBUT TEST\n");

	haut= creer_liste(NULL);
	bas= creer_liste(NULL);
	gauche= creer_liste(NULL);
	droite= creer_liste(NULL);

	zone* useless= creer_zone(0, 0, 0, 0, 0, NULL);
	my_zone= *useless;
	my_x= 200;
	my_y= 100;

	zone* z1= creer_zone(1, 1, 1, 1, 1, NULL);
	zone* z2= creer_zone(2, 2, 2, 2, 2, NULL);
	
	ajouter_entete_liste(haut, z1);
	ajouter_entete_liste(haut, z2);

	int id= routage(200, 200);
	zone* tmp= get_zone_par_id_total(id);
	afficher_zone(tmp);

	printf("FIN TEST \n");
	return EXIT_SUCCESS;
}
*/
