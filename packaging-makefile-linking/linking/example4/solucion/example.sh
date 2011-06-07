#Compilar
gcc -Wall -c recv_hook.c -fPIC

#Linkear (notar la inclusion de libdl al final!)
ld -shared -o recv_hook.so recv_hook.o -ldl

#Ejecutar wget
LD_PRELOAD=./recv_hook.so wget http://cs.famaf.unc.edu.ar/~carrascosa/loremipsum.txt

#Mostrar los archivos en /tmp
cat /tmp/socket_*.tmp

