#include "gestion_donnees.h"


donnee* get_donnee(liste_donnee liste, int x, int y){
	if(liste == NULL){
		printf("Erreur: get donnee: liste egale a NULL\n");
		exit(EXIT_FAILURE);
	}
	donnee* curs= liste->prem;
	while(curs != NULL){
		if( curs->x == x &&  curs->y == y){
			return curs;
		}
		curs=curs->next;
	}
	return NULL;
}


liste_donnee creer_liste_donnee(donnee*  prem){
	liste_donnee ld= (liste_donnee) malloc(sizeof(struct liste_donnee_t));
	ld->prem= prem;
	return ld;
}

void detruire_liste_donnee(liste_donnee liste){
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
	if(liste == NULL){
		printf("ajouter_entete_liste_donnee: liste ou donnee egale a NULL\n");
		exit(EXIT_FAILURE);
	}
	new_one->next= liste->prem;
	liste->prem= new_one;
}

void supprimer_entete_liste_donnee(liste_donnee liste){
	if(liste == NULL){
		printf("supprimer_entete_liste_donnee: Liste ou premiere element egal a NULL\n");
		exit(EXIT_FAILURE);
	}
	donnee* tmp= liste->prem;
	liste->prem=liste->prem->next;
	detruire_donnee(tmp);
}

void supprimer_element_liste_donnee(liste_donnee liste, donnee* d_supp){
	if(liste == NULL ){
		printf("supprimer_element_liste_donnee liste egale a NULL\n");
		exit(EXIT_FAILURE);
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
	if(liste == NULL ){
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

/* DEBUG */

void afficher_donnee(donnee* d){
	printf("\t--AFFICHE donnee--\n");
	printf("\t[%d:%d]: %d\n", d->x, d->y, d->data);
	printf("\tnext %p\n", d->next);
	printf("\t----------------\n");
}

void afficher_liste_donnee(liste_donnee liste_d){
	printf("--AFFICHE LISTE DONNE--\n");
	donnee * curs= liste_d->prem;
	while(curs != NULL){
		afficher_donnee(curs);
		curs=curs->next;
	}
	printf("----------------\n");
}

void afficher_liste_donnee_valeur(int id_noeud, liste_donnee liste_d){
	donnee * curs= liste_d->prem;
	printf("ID: %d: ", id_noeud);
	if(curs == NULL){
		printf("\n");
		return;
	}
	printf("[%d;%d]", curs->x, curs->y);
	curs=curs->next;
	while(curs != NULL){
		printf("->[%d; %d]",curs->x, curs->y);
		curs=curs->next;
	}
	printf("\n");
}

/*
int main(int argc, char* argv[]){
	printf("TEST unitaire\n");
	srand(time(NULL));

	srand(time(NULL));
	liste_donnee liste=creer_liste_donnee( NULL);
	donnee* tmp1= creer_donnee(rand()%10, rand()%10, rand()%100, NULL);
	donnee* tmp2= creer_donnee(rand()%10, rand()%10, rand()%100, NULL);


	if(est_meme_donnee(tmp1, tmp2)== true){
		printf("EST MEME ELEM\n");
	}
	else{
		printf("N'EST PAS MEME ELEM\n");
	}

	afficher_donnee(tmp1);
	ajouter_entete_liste_donnee(liste, tmp1);
	afficher_liste_donnee(liste);
	ajouter_entete_liste_donnee(liste, tmp2);
	afficher_liste_donnee(liste);

	if(est_dans_liste_donnee(liste, tmp1)== true){
		printf("EST DANS LA LISTE\n");
	}
	else{
		printf("N'EST PAS DANS LA LISTE\n");
	}

	if(est_dans_liste_donnee(liste, tmp2)== true){
		printf("EST DANS LA LISTE\n");
	}
	else{
		printf("N'EST PAS DANS LA LISTE\n");
	}

	supprimer_entete_liste_donnee(liste);

	if(est_dans_liste_donnee(liste, tmp2)== true){
		printf("EST DANS LA LISTE\n");
	}
	else{
		printf("N'EST PAS DANS LA LISTE\n");
	}

	detruire_liste_donnee(liste);

	printf("Fin test unitaire\n");
	return EXIT_SUCCESS;
}*/