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
	$(GCC) -Wl,-rpath=$(GOODPATH) -o agood a.o $(LIBNAME)

aevil: a.o $(LIBNAME)
	$(GCC) -Wl,-rpath=$(EVILPATH) -o aevil a.o $(LIBNAME)

ablank: a.o $(LIBNAME)
	$(GCC) -o ablank a.o $(LIBNAME)

astatic: a.o good.o
	$(GCC) -o astatic a.o good.o

$(GOODPATH)/$(LIBNAME): good.so $(GOODPATH)
	cp good.so $(GOODPATH)/$(LIBNAME)

$(EVILPATH)/$(LIBNAME): evil.so $(EVILPATH)
	cp evil.so $(EVILPATH)/$(LIBNAME)

$(GOODPATH):
	mkdir $(GOODPATH)

$(EVILPATH):
	mkdir $(EVILPATH)

a.o: a.c
	$(CC) $(CFLAGS) a.c

$(LIBNAME): good.so
	cp good.so lib.so

good.o: good.c
	$(CC) $(CFLAGS) good.c

evil.o: evil.c
	$(CC) $(CFLAGS) evil.c

good.so: good.o
	$(LD) $(LDFLAGS) -o good.so good.o

evil.so: evil.o
	$(LD) $(LDFLAGS) -o evil.so evil.o

clean:
	rm -rf *.so *.o $(EVILPATH) $(GOODPATH) $(TARGETS)

