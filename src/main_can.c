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
    sprintf(titre, "Insertion du noeud %d", i);
    exporter(i, titre);
  }

  int valx;
  int valy;
  int val_calcul;

  int save_val[10][2];

  for(i=0 ; i<  nb_proc*100; i++){
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

    if(i<5){
      save_val[i][0]=valx;
      save_val[i][1]=valy;
    }
    if( (nb_proc*10 - i) <= 5){
      save_val[4+ (nb_proc*10 - i)][0]=valx;
      save_val[4+ (nb_proc*10 - i)][1]=valy;    
    }
  }

  int valeur=0;
  for(i=0; i<10; i++){
      data[0]= COORDINATEUR;
      data[1]= save_val[i][0];
      data[2]= save_val[i][1];

      envoyer_message(BOOTSTRAP, data, REQ_RECHERCHE_VALEUR);
      valeur= attendreMessage();
     if(valeur != -1){
      sprintf(titre, "Insertion de la valeur (%d;%d;%d)", valx, valy, val_calcul);
      exporter(nb_proc, titre);
    }
  }

  terminer_export();
  
  // fin du programme 
  for(i=1; i<=nb_proc; i++) {
    envoyer_message(i, data, ACK);
  }
}

void noeud(int rang) {
  my_x = rand() % (LARGEUR_GRILLE+1); 
  my_y = rand() % (HAUTEUR_GRILLE+1);
  my_zone.id_noeud = rang;
  est_insere = false;
  my_donnee= creer_liste_donnee(NULL);
  haut = creer_liste(NULL);
  droite = creer_liste(NULL);
  bas = creer_liste(NULL);
  gauche = creer_liste(NULL);

  printf("Début %d : (%d;%d)\n", rang, my_x, my_y);
  attendreMessage();
  printf("  Fin %d : (%d;%d)\n", rang, my_x, my_y);

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

  srand(time(NULL)*(rang+1));

  if(rang == 0) coordinateur(nb_proc - 1);
  else noeud(rang);

  MPI_Finalize();

  return EXIT_SUCCESS;
}
