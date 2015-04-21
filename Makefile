CC= mpicc
CFLAGS= -Wall -Werror 
SRC= src
INC= include
OBJ= obj
BIN= bin

all: $(BIN)/main_can

$(BIN)/main_can: $(OBJ)/main_can.o $(OBJ)/insertion_noeud.o $(OBJ)/insertion_donnee.o $(OBJ)/recherche_donnee.o $(OBJ)/test_ajout_recherche_voisins.o
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ)/main_can.o: $(SRC)/main_can.c $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)


#Etape 1
$(OBJ)/insertion_noeud.o: $(SRC)/insertion_noeud.c $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)

#Etape 2
$(OBJ)/insertion_donnee.o: $(SRC)/insertion_donnee.c $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)

#Etape 3
$(OBJ)/recherche_donnee.o: $(SRC)/recherche_donnee.c $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)


$(OBJ)/test_ajout_recherche_voisins.o: $(SRC)/test_ajout_recherche_voisins.c $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)

clean: 
	rm -f obj/*.o src/*~ bin/*
