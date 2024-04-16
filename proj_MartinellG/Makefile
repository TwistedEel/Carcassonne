SRC = ./src/
INC = ./include/
OBJ = ./obj/
BIN = ./bin/
LIB = ./lib

CC = gcc
CFLAGS = -Wall -std=c11
EXEC = carcassonne
RAY = $(LIB)/libraylib.a

.PHONY: all run clean

all: $(EXEC)

run: $(EXEC)
	$(BIN)$<

$(EXEC): moteur_jeu.o lecteur_csv.o affichage.o pion.o
	$(CC) $(OBJ)* $(RAY) -I $(INC) -o $(BIN)$@ -lm
	
moteur_jeu.o: $(SRC)moteur_jeu.c
	$(CC) $(CFLAGS) $< -c -I $(INC) -o $(OBJ)$@

lecteur_csv.o: $(SRC)lecteur_csv.c
	$(CC) $(CFLAGS) $< -c -I $(INC) -o $(OBJ)$@
	
affichage.o: $(SRC)affichage.c
	$(CC) $(CFLAGS) $< -c -I $(INC) -o $(OBJ)$@

pion.o : $(SRC)pion.c
	$(CC) $(CFLAGS) $< -c -I $(INC) -o $(OBJ)$@

clean:
	rm $(BIN)* $(OBJ)*
