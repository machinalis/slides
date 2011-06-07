all: both

both: both.o evil_libs good_libs
	gcc -o $@ $< evil/evil.o good/good.o

evil_libs:
	cd evil && $(MAKE)

good_libs:
	cd good && $(MAKE)

clean:
	rm both.o both

.PHONY: all clean good_libs evil_libs
