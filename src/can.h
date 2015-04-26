#ifndef __CAH_H__
#define __CAH_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>

#define LEN_MAX_MSG 5

typedef struct donnee_t {
  int donnee;
  int x, y;
  struct donnee_t *next;
} donnee;

typedef struct zone_t {
  int id_noeud;
  int minX, maxX;
  int minY, maxY;
  struct zone_t *next;
} zone;

typedef enum tag_e{
  ACK,
  MAJ_ZONE,
  INIT_ZONE,
  REQ_INSERE_TOI,
  REQ_INSERTION_NOEUD,
  REQ_RECHERCHE_VALEUR,
  REQ_INSERTION_VALEUR
} tag;

typedef enum direction_e{
  DROITE,
  GAUCHE,
  HAUT,
  BAS
} direction;

zone my_zone;
int my_x;
int my_y;
zone *gauche, *bas, *droite, *haut;

/*les primitives de gestion des voisins sont maintenat dans gestion liste voisin.h*/

int router(int x, int y);
void diviser(int noeud);
void attendreMessage(void);

bool est_adjacent(zone* z1, zone* z2);
direction quel_cote(zone* z1, zone* z2);

void vider_liste_zone(zone* z);
void ajouter_entete_liste_zone(zone* z, zone* new);

bool traiter_requete_insere_toi(int nd_init);
bool traiter_requete_insertion_noeud(int id_noeud, int x, int y);
bool traiter_requete_insertion_valeur(int nd_init, int x, int y, int val);
bool traiter_requete_recherche_valeur(int nd_init, int x, int y);
bool traiter_maj_zone(int noeud, int minX, int maxX, int minY, int maxY);

void test_ajout_recherche_suppr_voisins(void);

#endif
