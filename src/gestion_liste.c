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
	detruire(tmp);
}

bool est_meme_zone(zone* z1, zone* z2){
	return z1->id_noeud == z2->id_noeud;
}

void supprimer_element_liste(zone* liste, zone* zone_supp){
	zone * prev_curs=NULL;
	zone* curs= liste;
	while(curs != NULL){
		if(est_meme_zone(curs, zone_supp) == true){
			if(prev_curs== NULL)
				supprimer_entete_liste(zone* liste);
			else
				prev_curs->next= curs->next;
				detruire_zone(curs);
			return;
		}
		
		prev_curs= curs;
		curs= curs->next;
	}
}

// detruire la totalité de la liste
void detruire_liste(zone* liste){
	while(liste != NULL){
		supprimer_entete_liste(liste);
	}
}

//dit si l'element est dans la liste
bool element_dans_liste(zone* liste, zone* z){
	zone * curs= liste;
	while(curs != NULL){
		if(est_meme_zone(curs, z))
			return true;
		curs=curs->next;
	}
	return false;
}
