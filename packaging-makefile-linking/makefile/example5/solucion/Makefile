GCC=gcc
CFLAGS=-Wall -c -fPIC
LDFLAGS=-shared
GOODPATH=/tmp/good
EVILPATH=/tmp/evil
LIBNAME=lib.so
TARGETS=agood aevil ablank astatic $(GOODPATH)/$(LIBNAME) $(EVILPATH)/$(LIBNAME)

all: $(TARGETS)

agood: a.o $(LIBNAME)
	$(GCC) -Wl,-rpath=$(GOODPATH) -o $@ $^

aevil: a.o $(LIBNAME)
	$(GCC) -Wl,-rpath=$(EVILPATH) -o $@ $^

ablank: a.o $(LIBNAME)
	$(GCC) -o $@ $^

astatic: a.o good.o
	$(GCC) -o $@ $^

$(GOODPATH)/$(LIBNAME): good.so $(GOODPATH)
	cp good.so $(GOODPATH)/$(LIBNAME)

$(EVILPATH)/$(LIBNAME): evil.so $(EVILPATH)
	cp evil.so $(EVILPATH)/$(LIBNAME)

$(GOODPATH) $(EVILPATH):
	mkdir $@

$(LIBNAME): good.so
	cp good.so lib.so

%.so: %.o
	$(LD) $(LDFLAGS) -o $@ $<

clean:
	rm -rf *.so *.o $(EVILPATH) $(GOODPATH) $(TARGETS)

.PHONY: clean all

