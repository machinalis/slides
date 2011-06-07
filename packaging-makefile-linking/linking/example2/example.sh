#Compilar
gcc -Wall -c a.c
gcc -Wall -c good.c

#Crear a.out estatico
cp good.o lib.o
gcc a.o lib.o
./a.out

#Crear a.out dinámico
gcc -Wall -fPIC -c good.c
ld -shared -o lib.o good.o
gcc a.o lib.o
./a.out # Produce un a.out que no encuentra a lib.o

gcc -Wl,-rpath=. a.o lib.o
./a.out #Ahora lo encuenta (busca en ".")

#Ocupar el lugar antes con otra funcion
gcc -Wall -fPIC -c evil.c
ld -shared -o tmp evil.o
mv tmp evil.o
LD_PRELOAD=evil.o ./a.out
