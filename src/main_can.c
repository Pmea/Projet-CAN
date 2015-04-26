#include "can.h"

void attendreMessage(void) {
  MPI_Status status;
  int donnees[LEN_MAX_MSG];
  
  while(1) {
    MPI_Recv(&donnees, LEN_MAX_MSG, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

    switch(status.MPI_TAG) {
    case ACK:
      return;
    case MAJ_ZONE:
      traiter_maj_zone(donnees[0], donnees[1], donnees[2], donnees[3], donnees[4]);
      return;
    case INIT_ZONE:
      traiter_maj_zone(donnees[0], donnees[1], donnees[2], donnees[3], donnees[4]);
      return;
    case REQ_INSERE_TOI:
      traiter_requete_insere_toi(donnees[0]);
      return;
    case REQ_INSERTION_NOEUD:
      traiter_requete_insertion_noeud(donnees[0], donnees[1], donnees[2]);
      return;
    case REQ_INSERTION_VALEUR:
      traiter_requete_insertion_valeur(donnees[0], donnees[1], donnees[2], donnees[3]);
      return;
    case REQ_RECHERCHE_VALEUR:
      traiter_requete_recherche_valeur(donnees[0], donnees[1], donnees[2]);
      return;
    }
  }
}

int main(int argc, char* argv[]){


	return EXIT_SUCCESS;
}
