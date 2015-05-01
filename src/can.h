#ifndef __CAH_H__
#define __CAH_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>
#include <string.h>
#include <time.h>

#include <time.h>

#define COORDINATEUR 0
#define BOOTSTRAP 1
#define LEN_MAX_MSG 6
#define HAUTEUR_GRILLE 1000
#define LARGEUR_GRILLE 1000

// structure connu par les fonctions du programme 
typedef struct donnee_t {
  int data;
  int x, y;
  struct donnee_t *next;
} donnee;

typedef struct liste_donnee_t{
  donnee * prem;
} * liste_donnee;

typedef struct zone_t {
  int id_noeud;
  int minX, maxX;
  int minY, maxY;
  struct zone_t *next;
} zone;

typedef struct liste_zone_t{
  zone * prem;
} * liste_zone;

typedef enum tag_e{
  ACK,
  MAJ_ZONE,
  INIT_ZONE,
  REQ_INSERE_TOI,
  REQ_INSERTION_NOEUD,
  REQ_RECHERCHE_VALEUR,
  REQ_INSERTION_VALEUR,
  EXPORT
} tag;

typedef enum direction_e{
  DROITE,
  GAUCHE,
  HAUT,
  BAS
} direction;

// un processus a un zone, une coordonnee, 4 listes de voisins et une liste de donnee
zone my_zone;
int my_x;
int my_y;
bool est_insere;
liste_donnee my_donnee;
liste_zone gauche, bas, droite, haut;


#include "gestion_liste.h"
#include "gestion_voisin.h"
#include "gestion_com.h"
#include "gestion_routage.h"
#include "graphique.h"
#include "gestion_donnees.h"


void diviser(int noeud);
bool traiter_requete_insere_toi(int nd_init);
bool traiter_requete_insertion_noeud(int id_noeud, int x, int y);
bool traiter_requete_insertion_valeur(int nd_init, int x, int y, int val);
bool traiter_requete_recherche_valeur(int nd_init, int x, int y);
bool traiter_maj_zone(int noeud, int minX, int maxX, int minY, int maxY);

#endif
