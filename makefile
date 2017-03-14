WARNING_FLAGS = -Wall -Wextra -Werror -pedantic -Wformat\
				-fstrict-overflow -Wstrict-overflow=5\
				-Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes\
				-Wmissing-prototypes -Wcast-align -pedantic-errors

CFLAGS = -std=c99 -m64 -O3 $(WARNING_FLAGS)

CLIBS =lib/libisentlib.a -lm -lGL -lGLU -lglut -lX11

all: main.o  moteur.o  affichage.o outils.o
	gcc -o main main.o  moteur.o  affichage.o outils.o $(CLIBS)
	rm *~

main.o:	main.c moteur.h affichage.h
	indent -linux main.c
	gcc $(CFLAGS) -c main.c

moteur.o : moteur.c moteur.h
	indent -linux moteur.c moteur.h
	gcc $(CFLAGS) -c moteur.c

affichage.o: affichage.c affichage.h
	indent -linux affichage.c affichage.h
	gcc $(CFLAGS) -c affichage.c

outils.o: outils.c outils.h
	indent -linux outils.c outils.h
	gcc $(CFLAGS) -c outils.c

test: test.o  moteur.o  affichage.o outils.o
	gcc -o test test.o  moteur.o  affichage.o outils.o $(CLIBS)
	rm *~

test.o:	test.c moteur.h affichage.h
	indent -linux test.c
	gcc $(CFLAGS) -c test.c

clean:
	rm -f *.o
	rm -f main test
	rm *~
