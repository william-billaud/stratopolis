WARNING_FLAGS = -Wall -Wextra -Werror -pedantic -Wformat\
				-fstrict-overflow -Wstrict-overflow=5\
				-Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes\
				-Wmissing-prototypes -Wcast-align -pedantic-errors

CFLAGS = -std=c99 -m64 -O3 $(WARNING_FLAGS)

CLIBS = -lm -lGL -lGLU -lX11 -lglut  

all: main.o  moteur.o  affichage.o outil.o
	gcc $(CFLAGS) main.o  moteur.o  affichage.o outil.o  libisentlib.a -o main  $(CLIBS)

main.o:	main.c moteur.h
	indent -linux main.c
	gcc $(CFLAGS) -c main.c

moteur.o : moteur.c moteur.h
	indent -linux moteur.c moteur.h
	gcc $(CFLAGS) -c moteur.c

affichage.o: affichage.c affichage.h
	indent -linux affichage.c affichage.h
	gcc $(CFLAGS) -c affichage.c

outil.o: outil.c outil.h
	indent -linux outil.c outil .h
	gcc $(CFLAGS) -c outil.c 
	
test : test.o  moteur.o  affichage.o outil.o
	gcc $(CFLAGS) test.o  moteur.o  affichage.o outil.o  libisentlib.a -o test  $(CLIBS)
	
test.o:	test.c moteur.h
	indent -linux test.c moteur.h
	gcc $(CFLAGS) -c test.c	

clean:
	rm -f *.o
	rm -f main test graphic
