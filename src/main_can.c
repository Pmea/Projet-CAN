#include "can.h"

void coordinateur(int nb_proc) {
  int data[LEN_MAX_MSG];
  int i;

  data[0] = COORDINATEUR;
  /* Insertion des noeuds */
  for(i=1; i<=nb_proc; i++) {
    envoyer_message(nb_proc, data, REQ_INSERE_TOI);
    attendreMessage();
  }
  
}

void noeud(int rang) {
  my_x = rand() % (LARGEUR_GRILLE+1);
  my_y = rand() % (HAUTEUR_GRILLE+1);

  attendreMessage();

}

int main(int argc, char* argv[]){

  int nb_proc, rang;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rang);

  srand(rang);

  if(rang == 0) coordinateur(nb_proc - 1);
  else noeud(rang);

  MPI_Finalize();

  return EXIT_SUCCESS;
}
