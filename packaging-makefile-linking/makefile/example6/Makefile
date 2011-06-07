SOURCES=$(shell ls *.c)
all: techo

techo: techo.o paredes.o columnas.o cimientos.o

depend:
	gcc -MM $(SOURCES) > .depend

clean:
	rm -f *.o techo .depend

.PHONY: all clean depend

-include .depend
