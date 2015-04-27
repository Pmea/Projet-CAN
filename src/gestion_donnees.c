#include "gestion_donnees.h"


donnee* get_donnee(int x, int y);


liste_donnee creer_liste_donne(donnee*  prem){
	liste_donnee ld= (liste_donnee) malloc(sizeof(struct liste_donnee_t));
	ld->prem= prem;
	return ld;
}

void detruire_liste_donne(liste_donnee liste){
	vider_liste_donnee(liste);
}

donnee* creer_donnee(int a, int b, int data, donnee* next){
	donnee* d= (donnee*) malloc(sizeof(struct donnee_t));
	d->x=a;
	d->y=b;
	d->data= data;
	d->next= next;

	return d;
}

void detruire_donnee(donnee *d){
	free(d);
}

void ajouter_entete_liste_donnee(liste_donnee liste, donnee* new_one){
	if(liste == NULL || new_one == NULL){
		printf("ajouter_entete_liste_donnee: liste ou donnee egale a NULL\n");
		exit(EXIT_FAILURE);
	}
	new_one->next= liste->prem;
	liste->prem= new_one;
}

void supprimer_entete_liste_donnee(liste_donnee liste){
	if(liste == NULL || liste->prem){
		printf("supprimer_entete_liste_donnee: Liste ou premiere element egal a NULL\n");
		exit(EXIT_FAILURE);
	}
	donnee* tmp= liste->prem;
	liste->prem=liste->prem->next;
	detruire_donnee(tmp);
}

void supprimer_element_liste_donnee(liste_donnee liste, donnee* d_supp){
	if(liste == NULL){
		printf("supprimer_element_liste_donnee liste egale a NULL\n");
	}
	donnee * prev_curs=NULL;
	donnee * curs= liste->prem;
	while(curs != NULL){
		if(est_meme_donnee(d_supp, curs) == true){
			if(prev_curs== NULL)
				supprimer_entete_liste_donnee(liste);
			else{
				prev_curs->next= curs->next;
				detruire_donnee(curs);
			}
			return;
		}
	
		prev_curs= curs;
		curs= curs->next;
	}
}

void vider_liste_donnee(liste_donnee liste){
	if(liste == NULL){
		printf("vider_liste_donnee: liste egale a NULL\n");
		exit(EXIT_FAILURE);
	}
	while(liste->prem != NULL){
		supprimer_entete_liste_donnee(liste);
	}
}

bool est_dans_liste_donnee(liste_donnee liste, donnee* elem){
	if(liste == NULL){
		printf("est_dans_liste_donnee: liste egale a NULL\n");
		exit(EXIT_FAILURE);
	}
	donnee * curs= liste->prem;
	while(curs != NULL){
		if(est_meme_donnee(elem, curs))
			return true;

		curs= curs->next;
	}
	return false;
}

bool est_meme_donnee(donnee* d1, donnee* d2){
	return d1->x == d2->x && d1->y == d2->y;
}