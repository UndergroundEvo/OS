.PHONY: all
all: 
	gcc -c -fPIC lab07d_*.c
	gcc -shared lab07d_*.o -o liblab07d.so
	gcc -c -Wall lab07d.c
	gcc lab07d.o -L. -llab07d -o lab7dynamic

.PHONY: export
export:
	echo 'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.'

.PHONY: clean
clean:
	rm lab07d_*.o
	rm liblab07d.so
	rm lab07d.o
	rm lab7dynamic