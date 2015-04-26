#include "gestion_liste.h"


zone* creer_zone(int id_noeud, int minX, int maxX, int minY, int maxY, zone * next){
	zone* new= (zone*) malloc(sizeof(struct zone_t));
	new->id_noeud= id_noeud;
	new->maxY=maxY;
	new->maxX=maxX;
	new->minY= minY;
	new->minX= minX;
	new->next= next;
	return new;
}

void detruire_zone(zone * z){
	free(z);
}

void ajouter_entete_liste(zone *liste, zone* new_one){
	new_one->next=liste;
	liste= new_one;
}

void supprimer_entete_liste(zone* liste){
	if(liste== NULL)
		return;
	zone * tmp= liste;
	liste= liste->next;
	detruire_zone(tmp);
}

bool est_meme_element(zone* z1, zone* z2){
	return z1->id_noeud == z2->id_noeud;
}

void supprimer_element_liste(zone* liste, zone* zone_supp){
	zone * prev_curs=NULL;
	zone* curs= liste;
	while(curs != NULL){
		if(est_meme_element(curs, zone_supp) == true){
			if(prev_curs== NULL)
				supprimer_entete_liste(liste);
			else
				prev_curs->next= curs->next;
				detruire_zone(curs);
			return;
		}
		
		prev_curs= curs;
		curs= curs->next;
	}
}

void detruire_liste(zone* liste){
	while(liste != NULL){
		supprimer_entete_liste(liste);
	}
}

bool est_dans_liste(zone* liste, zone* z){
	zone * curs= liste;
	while(curs != NULL){
		if(est_meme_element(curs, z))
			return true;
		curs=curs->next;
	}
	return false;
}



/** DEBBUG **/

void afficher_zone(zone* z){
	printf("--AFFICHE ZONE--\n");
	printf("id_noeud %d\n", z->id_noeud);
	printf("x=[%d:%d]\n", z->minX, z->maxX);
	printf("y=[%d:%d]\n", z->minY, z->maxY);
	printf("next %p\n", z->next);
	printf("----------------\n");
}

void afficher_liste(zone* liste){
	zone* curs= liste;
	while(curs != NULL){
		afficher_zone(curs);
		curs=curs->next;
	}
}

int main(int argc, char* argv[]){
	printf("TEST unitaire\n");
	srand(time(NULL));


	zone* liste= NULL;
	zone* tmp, *tmp2;
	tmp= creer_zone(1,rand()%100,rand()%100,rand()%100,rand()%100, NULL);
	tmp2= creer_zone(1,rand()%100,rand()%100,rand()%100,rand()%100, NULL);


	if(est_meme_element(tmp2, tmp)== true){
		printf("EST MEME ELEM\n");
	}
	else{
		printf("N'EST PAS MEME ELEM\n");
	}

	afficher_zone(tmp);
	ajouter_entete_liste(liste, tmp);
	afficher_liste(liste);
	ajouter_entete_liste(liste, tmp2);
	afficher_liste(liste);

	if(est_dans_liste(liste, tmp)== true){
		printf("EST DANS LA LISTE\n");
	}
	else{
		printf("N'EST PAS DANS LA LISTE\n");
	}

	if(est_dans_liste(liste, tmp)== true){
		printf("EST DANS LA LISTE\n");
	}
	else{
		printf("N'EST PAS DANS LA LISTE\n");
	}

	supprimer_entete_liste(liste);

	if(est_dans_liste(liste, tmp)== true){
		printf("EST DANS LA LISTE\n");
	}
	else{
		printf("N'EST PAS DANS LA LISTE\n");
	}


	detruire_zone(tmp);

	detruire_liste(liste);


	printf("FIn test unitaire\n");
	return EXIT_SUCCESS;
}