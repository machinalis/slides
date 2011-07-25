#Compilar
gcc -Wall -c a.c
gcc -Wall -c b.c

#Crear un nuevo codigo objeto
ld -r -o lib.o a.o b.o

#Crear un archive (library)
ar r lib.a a.o b.o


