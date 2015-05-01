#ifndef GESTION_ROUTAGE_H
#define GESTION_ROUTAGE_H

#include "can.h"

// retourne le noeud dans ses voisins rapprochant de la coordonnee
// le voisins n'est pas forcement celui qui rapproche le plus 
// il est choisi au hasare pour eviter de faire des boucle de routage
int routage(int x, int y);

#endif /* _H */