CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm
RM = rm -f
SRC = abr.c build.c chaine.c dijkstra.c erreur.c fichier.c hachage.c heap.c menu.c optimisation.c reseau.c stringTools.c timer.c xfigTools.c 
OBJ = $(SRC:.c=.o)
EXEC = main convertres converthash convertabr converttimer convertxfig testheap convertchaine chainestat convertchainecsp


all: $(EXEC)

.depend: $(SRC) $(EXEC:=.c)
	 $(CC) -MM $^ > $@

-include .depend

%: %.o $(OBJ) 
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	$(RM) $(OBJ) .depend $(SRC:.c=.h.gch) $(EXEC:=.o)

mrproper:
	$(RM) $(OBJ) $(EXEC) .depend $(SRC:.c=.h.gch) $(EXEC:=.o)

.PHONY: all clean mrproper
