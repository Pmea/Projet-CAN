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
      printf("Insertion échouée : noeud %d\n", i);
    sprintf(titre, "Insertion du noeud %d", i);
    exporter(i, titre);
  }

  int valx;
  int valy;
  int val_calcul;

  int save_val[10][2];

  // on insert les donnees
  for(i=0 ; i<  nb_proc*10; i++){
    valx= rand()% (LARGEUR_GRILLE+1);
    valy= rand()% (HAUTEUR_GRILLE+1);
    printf("DATA [%d;%d]\n", valx, valy);
    val_calcul= valx + valy;
    data[0]= COORDINATEUR;
    data[1]= valx;
    data[2]= valy;
    data[3]= val_calcul;

    //envoyer demande au bootstramp;
    envoyer_message(BOOTSTRAP, data, REQ_INSERTION_VALEUR);
    attendreMessage();

    sprintf(titre, "Insertion de la valeur (%d;%d;%d)", valx, valy, val_calcul);
    exporter(nb_proc, titre);

    // sauvegarde des valeurs
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
  for(i=0; i<10; i++){      // recuperation valeur sauvegarde
      data[0]= COORDINATEUR;
      data[1]= save_val[i][0];
      data[2]= save_val[i][1];

      envoyer_message(BOOTSTRAP, data, REQ_RECHERCHE_VALEUR);
      valeur= attendreMessage();
     if(valeur == -1){
      printf("Erreur donnée absente\n");
      exit(EXIT_FAILURE);
     }
     else{
      printf("Valeur trouvé: (%d;%d;%d)\n", data[1], data[2],valeur);
     }   
  }

  printf("Recherche aléatoire de valeurs qui n'existent sûrement pas\n");
  for(i=0; i<4; i++) {
    data[0] = COORDINATEUR;
    data[1] = rand()%1001;
    data[2] = rand()%1001;
    printf("Recherche d'une valeur à [%d;%d]\n", data[1], data[2]);
    envoyer_message(BOOTSTRAP, data, REQ_RECHERCHE_VALEUR);
    valeur= attendreMessage();
    if(valeur == -1)
      printf("Donnée absente\n");
    else
      printf("Valeur trouvé: (%d;%d;%d)\n", data[1], data[2],valeur);
  }

  terminer_export();
  
  // fin du programme, le ACK provoquera la sortie de la boucle infinie des
  // noeuds en attente d'un message
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

  /* rang+1 pour le cas du coordinateur qui sinon aura toujours une graine
     valanat 0 */
  srand(time(NULL)*(rang+1));

  if(rang == 0) coordinateur(nb_proc - 1);
  else noeud(rang);

  MPI_Finalize();

  return EXIT_SUCCESS;
}
