## ---------------------------------------------------------------------
## SCD. Makefile para el seminario 1.
## ---------------------------------------------------------------------

.PHONY: 1, 2, 3, pi, msg, clean, todo
.SUFFIXES:

params_comp:= -c -g -Wall -I. 
libs:=        -lpthread -lrt  

msg:
	@echo "usa 'make 1','make 2' o 'make 3' para compilar y ejecutar los ejemplos 1,2 o 3."
	@echo "usa 'make pi' para compilar y ejecutar el programa de cálculo de pi."
	@echo "usa 'make clean' para borrar todos los archivos creados al compilar."
	@echo "usa 'make todo' para recompilar (si es necesario) los 4 programas."

## ---------------------------------------------------------------------

1: ejemplo1	
	./ejemplo1

ejemplo1: ejemplo1.o fun_tiempo.o
	g++ -o ejemplo1 ejemplo1.o fun_tiempo.o $(libs)

ejemplo1.o: ejemplo1.cpp fun_tiempo.h
	g++ $(params_comp) -o ejemplo1.o ejemplo1.cpp

## ---------------------------------------------------------------------

2: ejemplo2	
	./ejemplo2

ejemplo2: ejemplo2.o fun_tiempo.o
	g++ -o ejemplo2 ejemplo2.o fun_tiempo.o $(libs)

ejemplo2.o: ejemplo2.cpp fun_tiempo.h
	g++ $(params_comp) -o ejemplo2.o ejemplo2.cpp

## ---------------------------------------------------------------------

3: ejemplo3	
	./ejemplo3

ejemplo3: ejemplo3.o fun_tiempo.o
	g++ -o ejemplo3 ejemplo3.o fun_tiempo.o $(libs)

ejemplo3.o: ejemplo3.cpp fun_tiempo.h
	g++ $(params_comp) -o ejemplo3.o ejemplo3.cpp

## ---------------------------------------------------------------------

pi: calculopi
	./calculopi

calculopi: calculopi.o fun_tiempo.o
	g++ -o calculopi calculopi.o fun_tiempo.o $(libs)

calculopi.o: calculopi.cpp fun_tiempo.h
	g++ $(params_comp) -o calculopi.o calculopi.cpp

## ---------------------------------------------------------------------

fun_tiempo.o: fun_tiempo.c fun_tiempo.h
	g++ $(params_comp) -o fun_tiempo.o fun_tiempo.c

## ---------------------------------------------------------------------

todo:
	make ejemplo1
	make ejemplo2
	make ejemplo3
	make calculopi

## ---------------------------------------------------------------------

clean:
	rm -rf *.o ejemplo1 ejemplo2 ejemplo3 calculopi

## ---------------------------------------------------------------------










