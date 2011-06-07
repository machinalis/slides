CC=cc
GCC=gcc
LD=ld
CFLAGS=-Wall -c -fPIC
LDFLAGS=-shared -lc
GOODPATH=/tmp/good
EVILPATH=/tmp/evil
LIBNAME=lib.so
TARGETS=agood aevil ablank astatic $(GOODPATH)/$(LIBNAME) $(EVILPATH)/$(LIBNAME)

all: $(TARGETS)

agood: a.o $(LIBNAME)


aevil: a.o $(LIBNAME)


ablank: a.o $(LIBNAME)


astatic: a.o good.o


$(GOODPATH)/$(LIBNAME): good.so $(GOODPATH)


$(EVILPATH)/$(LIBNAME): evil.so $(EVILPATH)

clean:
	rm -rf *.so *.o $(EVILPATH) $(GOODPATH) $(TARGETS)

