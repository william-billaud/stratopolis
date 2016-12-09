CFLAGS = -Wall -Werror -g


CLIBS = -lm -lGL -lGLU -lX11 -lglut  

all : main

main: main.o  moteur.o  affichage.o outil.o
	gcc $(CFLAGS) main.o  moteur.o  affichage.o outil.o  libisentlib.a -o main  $(CLIBS)

main.o:	main.c moteur.h
	gcc $(CFLAGS) -c main.c

moteur.o : moteur.c moteur.h
	gcc $(CFLAGS) -c moteur.c

affichage.o: affichage.c affichage.h
	gcc $(CFLAGS) -c affichage.c

outil.o: outil.c outil.c
	gcc $(CFLAGS) -c outil.c 
	
test : test.o  moteur.o  affichage.o outil.o
	gcc $(CFLAGS) test.o  moteur.o  affichage.o outil.o  libisentlib.a -o test  $(CLIBS)

test.o:	test.c moteur.h
	gcc $(CFLAGS) -c test.c
	
graphic : graphic.o moteur.o affichageGraphic.o outil.o
	gcc $(CFLAGS) graphic.o  moteur.o  affichageGraphic.o outil.o  libisentlib.a -o graphic  $(CLIBS)
	
grahic.o :graphic.c moteur.h
	gcc $(CFLAGS) -c grahic.c

affichageGraphic.o : affichageGraphic.c affichageGraphic.h
	gcc $(CFLAGS) -c affichageGraphic.c

clean:
	rm -f *.o
	rm -f main test graphic
