CC= mpicc
CFLAGS= -Wall -Werror -g
SRC= src
INC= include
OBJ= obj
BIN= bin

all: $(BIN)/main_can

$(BIN)/main_can: $(OBJ)/main_can.o $(OBJ)/insertion_noeud.o $(OBJ)/insertion_donnee.o $(OBJ)/recherche_donnee.o
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ)/main_can.o: $(SRC)/main_can.c $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)

run: $(BIN)/main_can
	mpirun -np 10 $<

#Etape 1
$(OBJ)/insertion_noeud.o: $(SRC)/insertion_noeud.c $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)

#Etape 2
$(OBJ)/insertion_donnee.o: $(SRC)/insertion_donnee.c $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)

#Etape 3
$(OBJ)/recherche_donnee.o: $(SRC)/recherche_donnee.c $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)

$(OBJ)/tests.o: $(OBJ)/main_can.o $(OBJ)/insertion_noeud.o $(OBJ)/tests.o $(SRC)/can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)

tests: $(OBJ)/main_can.o $(OBJ)/tests.o $(OBJ)/insertion_noeud.o $(OBJ)/insertion_donnee.o $(OBJ)/recherche_donnee.o
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
	rm -f obj/*.o src/*~ bin/*
