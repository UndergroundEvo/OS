.PHONY: all
all: 
	gcc -c -fPIC lab05_*.c
	gcc -shared lab05_*.o -o liblab05.so
	gcc -c -Wimplicit-function-declaration lab05.c
	gcc lab05.o -L. -llab05 -o lab5s

.PHONY: full
full: 
	gcc -o lab05_full.c lab05full 

.PHONY: export
export:
	echo 'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.'

.PHONY: clean
clean:
	rm lab05_*.o
	rm liblab05.so
	rm lab05.o
	rm lab5s