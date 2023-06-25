# Declaratiile de variabile
CC = gcc
CFLAGS = -g -Wall -lm -std=c99
 
# Regula de compilare
all: highlight autocomplete

highlight: highlight.c
	$(CC) -o highlight highlight.c $(CFLAGS)

autocomplete: autocomplete.c
	$(CC) -o autocomplete autocomplete.c $(CFLAGS)

# Regulile de "curatenie" (se folosesc pentru stergerea fisierelor intermediare si/sau rezultate)
.PHONY : clean
clean :
	rm -f highlight autocomplete
	rm -f *.out
	rm my_diff
