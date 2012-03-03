CC = gcc
CFLAGS = -Wall
RM = rm -f
SRC = erreur.c main.c fichier.c stringTools.c chaine.c
OBJ = $(SRC:.c=.o)
EXEC = main

SRC_TEST = erreur.c main.c fichier.c stringTools.c chaine.c
EXEC_TEST = test

all: $(EXEC)

.depend: $(SRC)
	 $(CC) -MM $^ > $@

-include .depend

%.o: %.C
	$(CC) $(CFLAGS) -c $^

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

$(EXEC_TEST): $(SRC_TEST:.c=.o)
	$(CC) -o $@ $^

clean:
	$(RM) $(OBJ) .depend

mrproper:
	$(RM) $(OBJ) $(EXEC) $(EXEC_TEST) .depend

.PHONY: all clean mrproper
