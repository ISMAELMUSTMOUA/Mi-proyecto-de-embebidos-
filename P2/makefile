all: libcomaflotante.so libpuntofijo.so libcalcl_tams.so puntofijo comaflotante calculo_punto_fijo
CC = gcc
PY = python3
CFLAGS = -g -Wall `pkg-config --cflags gtk+-3.0` -fPIC
LIBS = `pkg-config --libs gtk+-3.0` -lm

calculo_punto_fijo: interfaz.c
	$(CC) $(CFLAGS) -o calculo_punto_fijo interfaz.c gestion.c calcl_tams.c $(LIBS)

comaflotante: comaflotante.c
	$(CC) comaflotante.c -o comaflotante -lm

puntofijo: puntofijo.c
	$(CC) puntofijo.c -o puntofijo -L. -lm

calcl_tams: calcl_tams.c
	$(CC) calcl_tams.c -o calcl_tams -L. -lm

gestion: gestion.c
	$(CC) gestion.c -o gestion -L. -lm
	
libcomaflotante.so: comaflotante.c
	$(CC) -fPIC -c comaflotante.c -o comaflotante.o
	$(CC) -shared -o libcomaflotante.so comaflotante.o

libcalcl_tams.so:
	$(CC) -fPIC -c calcl_tams.c -o calcl_tams.o
	$(CC) -shared -o libcalcl_tams.so calcl_tams.o

libpuntofijo.so: puntofijo.c
	$(CC) -fPIC -c puntofijo.c -o puntofijo.o
	$(CC) -shared -o libpuntofijo.so puntofijo.o

test-moles: 
	$(PY) testeo.py

test-densidad: 
	$(PY) testeo_dens.py

test-energia: 
	$(PY) testeo_ener.py

test-all: test-moles test-densidad test-energia

run: calculo_punto_fijo
	./calculo_punto_fijo

clean:
	rm *.so *.o calcl_tams puntofijo comaflotante calculo_punto_fijo test_*.txt 

.PHONY: clean
