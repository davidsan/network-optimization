CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm
RM = rm -f
SRC = erreur.c main.c fichier.c stringTools.c chaine.c xfigTools.c
OBJ = $(SRC:.c=.o)
EXEC = main

all: $(EXEC)

.depend: $(SRC)
	 $(CC) -MM $^ > $@

-include .depend

%.o: %.C
	$(CC) $(CFLAGS) -c $^

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(OBJ) .depend

mrproper:
	$(RM) $(OBJ) $(EXEC) .depend

.PHONY: all clean mrproper
