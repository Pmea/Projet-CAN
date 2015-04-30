#include "can.h"

void coordinateur(int nb_proc) {
  int data[LEN_MAX_MSG];
  int i;
  char titre[1024];

  initialiser_export();

  data[0] = COORDINATEUR;
  /* Insertion des noeuds */
  for(i=1; i<=nb_proc; i++) {
    envoyer_message(i, data, REQ_INSERE_TOI);
    if(!attendreMessage())
      printf("\t\t\t\tInsertion échouée : noeud %d\n", i);
    /* if(!tmp) { */
    /*   /\* Le noeud n'a pas réussi à s'insérer *\/ */
    /*   printf("\t\t\t\tLe noeud %d n'a pas été inséré\n", i); */
    /* } else { */
    /*   printf("\t\t\t\tLe noeud %d a été inséré\n", i); */
    /* } */
    sprintf(titre, "Insertion du noeud %d", i);
    exporter(i, titre);
  }


  int valx;
  int valy;
  int val_calcul;

  for(i=0 ; i<  nb_proc*10; i++){
    valx= rand()% (LARGEUR_GRILLE+1);
    valy= rand()% (HAUTEUR_GRILLE+1);
    printf("DATA [%d;%d]\n", valx, valy);
    val_calcul= valx + valy;
    data[0]= COORDINATEUR;
    data[1]= valx;
    data[2]= valy;
    data[3]= val_calcul;
    //envoyer au bootstramp;
    envoyer_message(BOOTSTRAP, data, REQ_INSERTION_VALEUR);
    attendreMessage();

    sprintf(titre, "Insertion de la valeur (%d;%d;%d)", valx, valy, val_calcul);
    exporter(nb_proc, titre);
  }

  terminer_export();
  
  // fin du programme 
  for(i=1; i<=nb_proc; i++) {
    envoyer_message(i, data, ACK);
  }
  /* printf("Fin coord\n"); */
}

void noeud(int rang) {
  my_x = rand() % (LARGEUR_GRILLE+1); 
  my_y = rand() % (HAUTEUR_GRILLE+1);
  my_zone.id_noeud = rang;
  est_insere = false;
/* <<<<<<< HEAD */
  
/*   gauche = creer_liste(NULL); */
/*   bas = creer_liste(NULL); */
/*   droite = creer_liste(NULL); */

  /*MAIS OU EST PASSÉ MON HAUT ??????*/

/* ======= */
/* >>>>>>> 195c367bd37b909cac60d848082a471cca71ce35 */
  my_donnee= creer_liste_donnee(NULL);
  haut = creer_liste(NULL);
  droite = creer_liste(NULL);
  bas = creer_liste(NULL);
  gauche = creer_liste(NULL);


  printf("Début %d : (%d;%d)\n", rang, my_x, my_y);
  attendreMessage();
  printf("  Fin %d : (%d;%d)\n", rang, my_x, my_y);
  /* printf("Fin noeud %d\n", rang); */

  afficher_liste_donnee_valeur(rang, my_donnee);

  detruire_liste(haut);
  detruire_liste(droite);
  detruire_liste(bas);
  detruire_liste(gauche);

  detruire_liste_donnee(my_donnee);
}


int main(int argc, char* argv[]){

  int nb_proc, rang;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rang);

  srand(time(NULL)*rang);

  if(rang == 0) coordinateur(nb_proc - 1);
  else noeud(rang);

  MPI_Finalize();

  return EXIT_SUCCESS;
}
