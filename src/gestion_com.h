#ifndef GESTION_COM_H
#define GESTION_COM_H

#include "can.h"

// envoi un element a une liste
void boardcast_element_a_liste(zone* elem, int tag_msg, liste_zone liste);

// envoi une liste une personne
// cela generer autant de message que d'element dans la liste
void envoyer_tous_liste_a_un(zone* dest, int tag_msg, liste_zone a_envoyer);

// envoi un message au adjacent dans la liste
void envoyer_msg_au_adjacent(liste_zone lz, zone* z, int* msg, int tag_msg);

// envoie des infos des adjacents dans la liste 
void envoyer_info_tous_adjacent_a_un(liste_zone liste, zone* dest, int tag_msg);

void envoyer_message(int noeud, int *data, int tag);

#endif /* GESTION_COM_H */
