#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

/* Pour l'affichage, le coordinateur créé un fichier html et écrit dedans le
   début du fichier. Tous les états seront écrit dans le même fichier. Quand on
   veut ajouter un état au fichier, le coordinateur place le début d'une balise
   HTML qui servira de conteneur à cet état puis on demande séquentiellement à
   tous les noeuds d'exporter leurs données dans le fichier puis le coordinateur
   ferme la balise. A la fin de l'exécution, le coordinateur doit écrire la fin
   du fichier HTML. Le fichier sera nommé en fonction de la date et de l'heure
   pour éviter d'écraser un fichier existant. */


#include "can.h"

#define PREFIXE_FICHIER "execution_"

/* Date de l'initialisation. Sers pour le nom du fichier à créer. Disponible
   seulement pour le coordinateur qui les initialisera. Les autres noeuds
   utiliseront les valeurs du message EXPORT */
int jour;
int mois;
int annee;
int heures;
int minutes;
int secondes;

/* Coordinateur : Ecrire le début du fichier HTML */
void initialiser_export();
/* Coordinateur : Ecrire la fin du fichier HTML */
void terminer_export();
/* Coordinateur : Place la balise conteneur des états, demande l'exportation des noeuds et
   place la balise fermante */
void exporter(int nb_noeuds, char *titre);
/* Pour les noeuds : Ecrire ses données (coord du noeud et valeurs) dans le
   fichier. Appelé quand un message de type export est reçu */
void traiter_export(int jour, int mois, int annee, int heures, int minutes, int secondes);

#endif /* GRAPHIQUE_H */
