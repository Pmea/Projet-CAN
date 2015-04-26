#ifndef GESTION_COM_H
#define GESTION_COM_H

#include "can.h"

// envoi un element a une liste
void boardcast_element_a_liste(zone* source, zone* elem, liste_zone liste);

// envoi une liste une personne
void envoyer_tous_liste_a_un(zone* source, zone* dest, liste_zone a_envoyer);

#endif /* GESTION_COM_H */