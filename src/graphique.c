#include "graphique.h"

int jour;
int mois;
int annee;
int heures;
int minutes;
int secondes;

/* Appellé seulement une fois par le coordinateur pour débuter un fichier
   html */
void initialiser_export() {
  FILE *f;
  time_t tps = time(NULL);
  struct tm* temps = localtime(&tps);
  char nomFichier[strlen(PREFIXE_FICHIER) + strlen("jj_mm_aa_hh_mm_ss.html")+1];

  jour = temps->tm_mday;
  mois = temps->tm_mon + 1;
  annee = temps->tm_year - 100;
  heures = temps->tm_hour;
  minutes = temps->tm_min;
  secondes = temps->tm_sec;

  sprintf(nomFichier, "%s%2d_%2d_%2d_%2d_%2d_%2d.html", 
          PREFIXE_FICHIER, jour, mois, annee, heures, minutes, secondes);

  f = fopen(nomFichier, "w");

  fprintf(f, "<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML Basic 1.1//EN' 'http://www.w3.org/TR/xhtml-basic/xhtml-basic11.dtd'>\n<html xml:lang='fr' lang='fr' xmlns='http://www.w3.org/1999/xhtml'>\n  <head>\n    <meta http-equiv='Content-Type' content='text/html; charset=utf-8' />\n\n    <link rel='stylesheet' href='styles.css' type='text/css'>\n    <style>\n      .grille {\n        width : 500px;\n        height : 500px;\n      }\n    </style>\n    <title> CAN </title>\n    </head>\n    <body><div>\n        <div id='conteneurEtats'>\n\n");

  if(fclose(f)) {
    perror("fclose ");
  }
  
  
}

/* Appellé seulement une fois par le coordinateur pour terminer un fichier
   html */
void terminer_export() {
  FILE *f;
  char nomFichier[strlen(PREFIXE_FICHIER) + strlen("jj_mm_aa_hh_mm_ss.html")+1];

  sprintf(nomFichier, "%s%2d_%2d_%2d_%2d_%2d_%2d.html", 
          PREFIXE_FICHIER, jour, mois, annee, heures, minutes, secondes);

  f = fopen(nomFichier, "a");

  fprintf(f, "        </div>\n\n    </div></body>\n  </html>\n");

  if(fclose(f)) {
    perror("fclose ");
  }
  

}

/* Appellé par le coordinateur, provoque la sauvegarde d'une étape */
void exporter(int nb_noeuds, char *titre) {
  static int nbExport = 0;
  nbExport++;
  FILE *f;
  char nomFichier[strlen(PREFIXE_FICHIER) + strlen("jj_mm_aa_hh_mm_ss.html")+1];
  int i;
  int data[LEN_MAX_MSG];

  sprintf(nomFichier, "%s%2d_%2d_%2d_%2d_%2d_%2d.html", 
          PREFIXE_FICHIER, jour, mois, annee, heures, minutes, secondes);

  f = fopen(nomFichier, "a");
  if(nbExport > 1)
    fprintf(f, "          <input type='radio' name='selecteurEtat' id='selecteurEtat%d'/>\n          <label for='selecteurEtat%d'>\n            <img src='go-previous-5.png' class='fleche flechePrecedent'\n                 alt='flèche précédent' title='afficher l'état précédent' />\n          </label>\n          <label for='selecteurEtat%d'>\n            <img src='go-next-5.png' class='fleche  flecheSuivant'\n                 alt='flèche suivant' title='afficher l'état suivant' />\n          </label>\n          <div class='etat'>\n            <h1> %s </h1>\n\n            <div class='grille'>\n", nbExport, nbExport-1, nbExport, titre);
  else
    fprintf(f, "          <input type='radio' name='selecteurEtat' id='selecteurEtat%d'/>\n          <div class='etat'>\n            <h1> %s </h1>\n\n            <div class='grille'>\n", nbExport, titre);

  if(fclose(f)) {
    perror("fclose ");
  }

  data[0] = jour;
  data[1] = mois;
  data[2] = annee;
  data[3] = heures;
  data[4] = minutes;
  data[5] = secondes;
  for(i=0; i<nb_noeuds; i++) {
    envoyer_message(i+1, data, EXPORT);
    attendreMessage();
  }

  f = fopen(nomFichier, "a");

  fprintf(f, "            </div>\n          </div>\n\n");

  if(fclose(f)) {
    perror("fclose ");
  }

}

/* Appellé par un noeud après avoir reçu une requete */
void traiter_export(int jour, int mois, int annee, int heures, int minutes, int secondes) {
  FILE *f;
  char nomFichier[strlen(PREFIXE_FICHIER) + strlen("jj_mm_aa_hh_mm_ss.html")+1];
  int donnees[LEN_MAX_MSG];
  int nd_left, nd_bottom, id, width, height, left, bottom;


  sprintf(nomFichier, "%s%2d_%2d_%2d_%2d_%2d_%2d.html", 
          PREFIXE_FICHIER, jour, mois, annee, heures, minutes, secondes);

  nd_left = my_x/2; 
  nd_bottom = my_y/2;
  id = my_zone.id_noeud;
  width = (my_zone.maxX - my_zone.minX)/2;
  height = (my_zone.maxY - my_zone.minY)/2;
  left = (my_zone.minX)/2;
  bottom = (my_zone.minY)/2;

  f = fopen(nomFichier, "a");

  fprintf(f, "                <div style='left:%dpx; bottom:%dpx;' class='noeud'>%d</div>\n              <div style='width:%dpx; height:%dpx;left:%dpx; bottom:%dpx;' class='zone'></div>\n", nd_left, nd_bottom, id, width, height, left, bottom);

  if(fclose(f)) {
    perror("fclose ");
  }

  envoyer_message(COORDINATEUR, donnees, ACK);
}

