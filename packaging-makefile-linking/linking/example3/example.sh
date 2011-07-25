#Compilar
gcc -Wall -c malloc_hook.c -fPIC

#Linkear (notar la inclusion de libdl al final!)
ld -shared -o malloc_hook.so malloc_hook.o -ldl

#Ejecutar date
date

#Ejecutar date con hooks
LD_PRELOAD=./malloc_hook.so date

