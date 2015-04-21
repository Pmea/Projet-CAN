CC= gcc
CFLAGS= -Wall -Werror -g 
SRC= src
INC= include
OBJ= obj
BIN= bin

all: $(BIN)/main-can

$(BIN)/main_can: $(OBJ)/main_can.o $(OBJ)/insertion_noeud.o 
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ)/main_can.o: $(SRC)/main_can.c $(SRC)can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)


#Etape 1
$(OBJ)/insertion_noeud.o: $(SRC)/insertion_noeud.c $(SRC)can.h
	$(CC) -o $@ -c $< -I$(INC) $(CFLAGS)



clean: 
	rm obj/*.o src/*~ bin/*
