CC=gcc
LD=ld
CFLAGS=-Wall -fPIC -c
LDFLAGS=-shared -ldl

all: hooks.so

malloc_hook.o: malloc_hook.c
	$(CC) $(CFLAGS) malloc_hook.c

hooks.so: malloc_hook.o recv_hook.o
	$(LD) $(LDFLAGS) -o hooks.so malloc_hook.o recv_hook.o

recv_hook.o: recv_hook.c
	$(CC) $(CFLAGS) recv_hook.c

clean:
	rm -f hooks.so malloc_hook.o recv_hook.o

