# Este script crea 4 ejecutables y 2 bibliotecas dinámicas.
# Los ejecutables:
# agood:   usa rpath para encontrar a good
# aevil:   usa rpath para encontrar a evil
# ablank:  necesita a lib.o, pero no sabe donde buscarla
# astatic: compilado estaticamente, pero tiene rpath
#
# Las bibliotecas:
# /tmp/good/lib.o: Imprime "Soy good"
# /tmp/evil/lib.o: Imprime "Soy evil"

#Compilar
gcc -Wall -c a.c
gcc -Wall -fPIC -c good.c
gcc -Wall -fPIC -c evil.c

#Crear las libs dinámicas
ld -shared -o good.so good.o
ld -shared -o evil.so evil.o
cp good.so lib.so #Podría haber sido evil.o, es lo mismo.

#Ubicarlas
mkdir /tmp/good 2> /dev/null
mkdir /tmp/evil 2> /dev/null
cp good.so /tmp/good/lib.so
cp evil.so /tmp/evil/lib.so

#Crear ejecutables dinámicos
gcc -Wl,-rpath=/tmp/good -o agood a.o lib.so
gcc -Wl,-rpath=/tmp/evil -o aevil a.o lib.so
gcc -o ablank a.o lib.so #una copia dinámica, pero sin rpath

#Crear una version linkeada estáticamente
gcc -Wl,-rpath=/tmp/evil -o astatic a.o good.o

#
# La tarea:
# Jugar a adivina adivinador, adivinar lo que los programas sacan como output
#

./ablank   #Output: un error, no encuentra a lib.o (el primero va de yapa)
./astatic  #Output: good
LD_PRELOAD=/tmp/evil/lib.so ./astatic #Output: good
./agood  #Output: good
./aevil  #Output: evil
LD_PRELOAD=/tmp/evil/lib.so ./ablank  #Output: Error, sutil. Resulta que LD_PRELOAD fuerza la carga de una bib y sus simbolos, pero no rellena el espacio de una lib faltante.
LD_PRELOAD=/tmp/evil/lib.so ./agood  #Output: evil
LD_LIBRARY_PATH=/tmp/evil/ ./agood  #Output: good
LD_LIBRARY_PATH=/tmp/evil/ ./ablank  #Output: evil
LD_LIBRARY_PATH=/tmp/evil/ LD_PRELOAD=/tmp/good/lib.so ./ablank #Output: good

# 
# Si > es sobre la precedencia en el orden de busqueda de bibliotecas dinámicas
# de tal manera que a > b si se busca primero en a y luego en b.
# En base a lo experimentado, responder True o False:
#
# LD_PRELOAD < rpath  --- False
# system_default > LD_LIBRARY_PATH (hint: probar en example3) --- True
# rpath < system_default --- False
# LD_PRELOAD > rpath > system_default > LD_LIBRARY_PATH --- True

# Notar que segun google LD_LIBRARY_PATH tiene precedencia casi máxima (por debajo de LD_PRELOAD), sin embargo
# los experimentos muestran otra cosa. Tal vez es system-dependant. Tal vez LD_LIBRARY_PATH esta siendo deprecada... quien sabe.

