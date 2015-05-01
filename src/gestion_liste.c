#include "gestion_liste.h"

liste_zone creer_liste(zone * prem){
	liste_zone l= malloc(sizeof(struct liste_zone_t));
	l->prem= prem;
	return l;
}
void detruire_liste(liste_zone liste){
	vider_liste(liste);
}

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

void ajouter_entete_liste(liste_zone liste, zone* new_one){
	new_one->next=liste->prem;
	liste->prem= new_one;
}

void supprimer_entete_liste(liste_zone liste){
	if(liste->prem== NULL)
		return;
	zone * tmp= liste->prem;
	liste->prem= liste->prem->next;
	detruire_zone(tmp);
}

bool est_meme_element(zone* z1, zone* z2){
	return z1->id_noeud == z2->id_noeud;
}

void supprimer_element_liste(liste_zone liste, zone* zone_supp){
	zone * prev_curs=NULL;
	zone* curs= liste->prem;
	while(curs != NULL){
		if(est_meme_element(curs, zone_supp) == true){
			if(prev_curs== NULL)
				supprimer_entete_liste(liste);
			else{
				prev_curs->next= curs->next;
				detruire_zone(curs);
			}
			return;
		}
		
		prev_curs= curs;
		curs= curs->next;
	}
}

void vider_liste(liste_zone liste){
	while(liste->prem != NULL){
		supprimer_entete_liste(liste);
	}
}

bool est_dans_liste(liste_zone liste, zone* z){
	zone * curs= liste->prem;
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

void afficher_liste(liste_zone liste){
	printf("--AFFICHE LISTE--\n");
	zone* curs= liste->prem;
	while(curs != NULL){
		afficher_zone(curs);
		curs=curs->next;
	}
	printf("----------------\n");

}