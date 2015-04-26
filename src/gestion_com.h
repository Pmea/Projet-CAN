#ifndef GESTION_COM_H
#define GESTION_COM_H

#include "can.h"

// envoi un element a une liste
void boardcast_element_a_liste(zone* elem, int tag_msg, liste_zone liste);

// envoi une liste une personne
// cela generer autant de message que d'element dans la liste
void envoyer_tous_liste_a_un(zone* dest, int tag_msg, liste_zone a_envoyer);

#endif /* GESTION_COM_H */