#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#include "can.h"

#define PREFIXE_FICHIER "execution_"

int jour;
int mois;
int annee;
int heures;
int minutes;
int secondes;

void initialiser_export();
void terminer_export();
void exporter(int nb_noeuds, char *titre);
void traiter_export(int jour, int mois, int annee, int heures, int minutes, int secondes);

#endif /* GRAPHIQUE_H */
