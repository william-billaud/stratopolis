MACHINE= $(shell uname -s)

ifeq ($(MACHINE),Darwin)
	GFXLIB_LINE = gcc -Wall -O2 -c GfxLib.c -Wno-deprecated-declarations
else
	GFXLIB_LINE = gcc -Wall -O2 -c GfxLib.c -I/usr/include/GL
endif

all: BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o ThreadLib.o
	ar r libisentlib.a BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o ThreadLib.o
	ranlib libisentlib.a
	make clean

BmpLib.o: BmpLib.c BmpLib.h OutilsLib.h
	gcc -Wall -O2 -c BmpLib.c

ESLib.o: ESLib.c ESLib.h ErreurLib.h
	gcc -Wall -O2 -c ESLib.c

ErreurLib.o: ErreurLib.c ErreurLib.h
	gcc -Wall -O2 -c ErreurLib.c

GfxLib.o: GfxLib.c GfxLib.h ESLib.h
	$(GFXLIB_LINE)
# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :

OutilsLib.o: OutilsLib.c OutilsLib.h
	gcc -Wall -O2 -c OutilsLib.c


ThreadLib.o: ThreadLib.c ThreadLib.h
	gcc -Wall -O2 -c ThreadLib.c


zip:
	tar -cvzf libisentlib.tgz *.[ch] *.bmp *.pdf makefile

clean:
	rm -f *~ *.o

deepclean: clean
	rm -f libisentlib.a

