CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm
RM = rm -f
SRC = erreur.c main.c fichier.c stringTools.c chaine.c xfigTools.c reseau.c menu.c
OBJ = $(SRC:.c=.o)
EXEC = main

SRC_TEST =  erreur.c mainChaine.c fichier.c stringTools.c chaine.c xfigTools.c reseau.c menu.c
OBJ_TEST = $(SRC_TEST:.c=.o)

all: $(EXEC)

.depend: $(SRC_TEST)
	 $(CC) -MM $^ > $@

-include .depend

%.o: %.C
	$(CC) $(CFLAGS) -c $^

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

mainChaine: $(OBJ_TEST)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(OBJ) .depend $(OBJ_TEST)

mrproper:
	$(RM) $(OBJ) $(EXEC) .depend $(OBJ_TEST) mainChaine

.PHONY: all clean mrproper
