#define _GNU_SOURCE // para que incluya algunas cosas extras

#include <stdio.h>  // para printf
#include <stddef.h> // para size_t
#include <dlfcn.h>  // para dlsym

int recv (int SOCKET, void *BUFFER, size_t SIZE, int FLAGS)
{
    int (*original)(int, void *, size_t, int); // Puntero a funcion
    int result;
    char fname[50];
    FILE * output;

    original = dlsym(RTLD_NEXT, "recv");
    
    result = original(SOCKET,BUFFER,SIZE,FLAGS);
    printf("receiving %i bytes\n",result);
    if (result != 0) {
        sprintf(fname,"/tmp/socket_%i.tmp",SOCKET);
        output = fopen(fname,"a");
        fwrite(BUFFER,SIZE,1,output);
        fclose(output);
    }
    
    return result;
}
