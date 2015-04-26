#include "gestion_voisin.h"

bool est_adjacent(zone* z, zone* z2){
	if((z->maxX == z2->minX -1 ) && (z->minY < z2->maxY && z->maxY > z2->minY)	||			
		(z2->maxX == z->minX -1 && (z->minY < z2->maxY && z->maxY > z2->minY))	||			
		(z->maxY == z2->minY -1 && (z->minX < z2->maxX && z->maxX > z2->minX))	||			
		(z2->maxY == z->minY -1 && (z->minX < z2->maxX && z->maxX > z2->minX))) {
		return true;
	}
	return false;
}