#include "graphique.h"

void initialiser_export() {
  FILE *f;
  time_t tps = time(NULL);
  struct tm* temps = localtime(&tps);
  char nomFichier[strlen(PREFIXE_FICHIER) + strlen("jj_mm_aa_hh_mm_ss.html")+1];

  /* Détermine le nom du fichier à créer */
  jour = temps->tm_mday;
  mois = temps->tm_mon + 1;
  annee = temps->tm_year - 100;
  heures = temps->tm_hour;
  minutes = temps->tm_min;
  secondes = temps->tm_sec;

  sprintf(nomFichier, "%s%.2d_%.2d_%.2d_%.2d_%.2d_%.2d.html",
          PREFIXE_FICHIER, jour, mois, annee, heures, minutes, secondes);

  f = fopen(nomFichier, "w");

  /* Ecrit le début du fichier */
  fprintf(f, "<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML Basic 1.1//EN' 'http://www.w3.org/TR/xhtml-basic/xhtml-basic11.dtd'>\n<html xml:lang='fr' lang='fr' xmlns='http://www.w3.org/1999/xhtml'>\n  <head>\n    <meta http-equiv='Content-Type' content='text/html; charset=utf-8' />\n\n    <link rel='stylesheet' href='styles.css' type='text/css'>\n    <style>\n      .grille {\n        width : 500px;\n        height : 500px;\n      }\n    </style>\n    <title> CAN </title>\n    </head>\n    <body><div>\n        <div id='conteneurEtats'>\n\n");

  if(fclose(f)) {
    perror("fclose ");
  }


}

void terminer_export() {
  FILE *f;
  char nomFichier[strlen(PREFIXE_FICHIER) + strlen("jj_mm_aa_hh_mm_ss.html")+1];

  sprintf(nomFichier, "%s%.2d_%.2d_%.2d_%.2d_%.2d_%.2d.html",
          PREFIXE_FICHIER, jour, mois, annee, heures, minutes, secondes);

  f = fopen(nomFichier, "a");

  /* Ecrit la fin duu fichier */
  fprintf(f, "        </div>\n        <div id='raccourcis'></div>\n\n    </div>    <script type=\"text/javascript\" src=\"script.js\"></script>\n    </body>\n  </html>\n");

  if(fclose(f)) {
    perror("fclose ");
  }


}

void exporter(int nb_noeuds, char *titre) {
  static int nbExport = 0;
  nbExport++;
  FILE *f;
  char nomFichier[strlen(PREFIXE_FICHIER) + strlen("jj_mm_aa_hh_mm_ss.html")+1];
  int i;
  int data[LEN_MAX_MSG];

  sprintf(nomFichier, "%s%.2d_%.2d_%.2d_%.2d_%.2d_%.2d.html",
          PREFIXE_FICHIER, jour, mois, annee, heures, minutes, secondes);


  f = fopen(nomFichier, "a");

  /* Place les balises nécéssaire à l'affichage de cet état */
  if(nbExport > 1)
    fprintf(f, "          <input type=\"radio\" name=\"selecteurEtat\" id=\"selecteurEtat%d\"/>\n          <label for=\"selecteurEtat%d\">\n            <img src=\"go-previous-5.png\" class=\"fleche flechePrecedent\"\n                 alt=\"flèche précédent\" title=\"afficher l'état précédent\" />\n          </label>\n          <label for=\"selecteurEtat%d\">\n            <img src=\"go-next-5.png\" class=\"fleche  flecheSuivant\"\n                 alt=\"flèche suivant\" title=\"afficher l'état suivant\" />\n          </label>\n          <div class=\"etat\">\n            <h1> %s </h1>\n            <div class=\"grille\">\n", nbExport, nbExport-1, nbExport, titre);
  else
    fprintf(f, "          <input type=\"radio\" name=\"selecteurEtat\" id=\"selecteurEtat%d\" checked=\"checked\"/>\n          <div class=\"etat\">\n            <h1> %s </h1>\n            <div class=\"grille\">\n", nbExport, titre);

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

void traiter_export(int jour, int mois, int annee, int heures, int minutes, int secondes) {
  FILE *f;
  char nomFichier[strlen(PREFIXE_FICHIER) + strlen("jj_mm_aa_hh_mm_ss.html")+1];
  int donnees[LEN_MAX_MSG];
  int nd_left, nd_bottom, id, width, height, left, bottom, val_left, val_bottom;
  donnee *d;

  if(!est_insere) {
    envoyer_message(COORDINATEUR, donnees, ACK);
    return;
  }


  sprintf(nomFichier, "%s%.2d_%.2d_%.2d_%.2d_%.2d_%.2d.html",
          PREFIXE_FICHIER, jour, mois, annee, heures, minutes, secondes);

  /* Détermine les valeurs à écrire */
  nd_left = my_x/2;
  nd_bottom = my_y/2;
  id = my_zone.id_noeud;
  width = (my_zone.maxX - my_zone.minX)/2;
  height = (my_zone.maxY - my_zone.minY)/2;
  left = (my_zone.minX)/2;
  bottom = (my_zone.minY)/2;

  f = fopen(nomFichier, "a");

  /* Exporte le noeud et la zone */
  fprintf(f, "                <div style='left:%dpx; bottom:%dpx;' class='noeud'>%d</div>\n                <div style='width:%dpx; height:%dpx;left:%dpx; bottom:%dpx;' class='zone'></div>\n", nd_left, nd_bottom, id, width, height, left, bottom);

  /* Ecrit les données associées au noeud */
  for(d=my_donnee->prem; d; d = d->next) {
    val_left = d->x/2;
    val_bottom = d->y/2;
    fprintf(f, "                <div style='left:%dpx; bottom:%dpx;' class='noeud donnee'>[%d;%d]</div>\n", val_left, val_bottom, d->x, d->y);
  }

  if(fclose(f)) {
    perror("fclose ");
  }

  envoyer_message(COORDINATEUR, donnees, ACK);
}

