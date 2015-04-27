#include "can.h"

void coordinateur(int nb_proc) {
  int data[LEN_MAX_MSG];
  /* int timestamp[LEN_MAX_MSG]; */
  int i;
  char titre[1024];

  initialiser_export();
  /* timestamp[0] = jour; */
  /* timestamp[1] = mois; */
  /* timestamp[2] = annee; */
  /* timestamp[3] = heures; */
  /* timestamp[4] = minutes; */
  /* timestamp[5] = secondes; */

  data[0] = COORDINATEUR;
  /* Insertion des noeuds */
  for(i=1; i<=nb_proc; i++) {
    envoyer_message(i, data, REQ_INSERE_TOI);
    attendreMessage();
    sprintf(titre, "Insertion de %d", i);
    exporter(i, titre);
  }
  terminer_export();
  for(i=1; i<=nb_proc; i++) {
    envoyer_message(i, data, ACK);
  }
  /* printf("Fin coord\n"); */
}

void noeud(int rang) {
  my_x = rand() % (LARGEUR_GRILLE+1); 
   my_y = rand() % (HAUTEUR_GRILLE+1); 
  my_zone.id_noeud = rang;
  
  gauche = creer_liste(NULL);
  bas = creer_liste(NULL);
  droite = creer_liste(NULL);
  haut = creer_liste(NULL);

  printf("Début %d : (%d;%d)\n", rang, my_x, my_y);
  attendreMessage();
  printf("  Fin %d : (%d;%d)\n", rang, my_x, my_y);
  /* printf("Fin noeud %d\n", rang); */
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
