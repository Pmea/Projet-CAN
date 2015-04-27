CC= mpicc
CFLAGS= -std=c99 -Wall -Werror -g
SRC= src
INC= include
OBJ= obj
BIN= bin

all: $(BIN)/main_can

#Etape 0
$(OBJ)/gestion_liste.o: $(SRC)/gestion_liste.c $(SRC)/gestion_liste.h $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)	

$(OBJ)/gestion_voisin.o: $(SRC)/gestion_voisin.c $(SRC)/gestion_voisin.h $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)	

$(OBJ)/gestion_com.o: $(SRC)/gestion_com.c $(SRC)/gestion_com.h $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)	

$(OBJ)/graphique.o: $(SRC)/graphique.c $(SRC)/graphique.h $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)	

$(OBJ)/gestion_routage.o: $(SRC)/gestion_routage.c $(SRC)/gestion_routage.h  $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)	

$(OBJ)/gestion_donnees.o: $(SRC)/gestion_donnees.c $(SRC)/gestion_donnees.h $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)	

$(OBJ)/main_can.o: $(SRC)/main_can.c $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)

#Etape 1
$(OBJ)/insertion_noeud.o: $(SRC)/insertion_noeud.c $(SRC)/insertion_noeud.h $(SRC)/can.h 
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)

#Etape 2
$(OBJ)/insertion_donnee.o: $(SRC)/insertion_donnee.c  $(SRC)/insertion_donnee.h $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)

#Etape 3
$(OBJ)/recherche_donnee.o: $(SRC)/recherche_donnee.c  $(SRC)/recherche_donnee.h $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)

#Final
$(BIN)/main_can: $(OBJ)/main_can.o $(OBJ)/insertion_noeud.o $(OBJ)/insertion_donnee.o $(OBJ)/recherche_donnee.o $(OBJ)/gestion_liste.o $(OBJ)/gestion_voisin.o $(OBJ)/gestion_com.o $(OBJ)/gestion_routage.o $(OBJ)/graphique.o $(OBJ)/gestion_donnees.o
	$(CC) -o $@ $^ $(CFLAGS)

run: $(BIN)/main_can
	mpirun -np 10 $<


clean: 
	rm -f obj/*.o src/*~ bin/*