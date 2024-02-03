CC=gcc
CFLAGS=-O3 -g
LDFLAGS=-lm

TARGETS=test mandel

all: $(TARGETS)

libppm.so: ppm.c
	$(CC) $(CFLAGS) -fpic -shared $^ -o $@

test: main.c libppm.so
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -lppm -L. -o $@

mandel: mandel.c libppm.so
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -lm -L. -o $@

clean:
	rm -fr $(TARGETS) *.so

