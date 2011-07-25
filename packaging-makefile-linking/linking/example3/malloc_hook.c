#define _GNU_SOURCE // para que incluya algunas cosas extras

#include <stdio.h>  // para printf
#include <stddef.h> // para size_t
#include <dlfcn.h>  // para dlsym

static unsigned int total=0;

void * malloc (size_t size)
{
    void * (*original )(size_t); // Puntero a funcion
    void * result;
    original = dlsym(RTLD_NEXT, "malloc");

    result = original(size);

    if (result != NULL) total += 1;
    printf("Chunks de memoria asignados via malloc/free: %i\n",total);
    return result;
}

void free (void *ptr)
{
    void (*original )(void *); // Puntero a funcion
    original = dlsym(RTLD_NEXT, "free");

    original(ptr);

    if (ptr != NULL) total -= 1;
    printf("Chunks de memoria asignados via malloc/free: %i\n",total);
}
