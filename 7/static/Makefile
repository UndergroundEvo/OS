.PHONY: all
all: 
	gcc -c -fPIC lab07s_*.c
	gcc -shared lab07s_*.o -o liblab07s.so
	gcc -c -Wall lab07s.c
	gcc lab07s.o -L. -llab07s -o lab7static

.PHONY: export
export:
	echo 'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.'

.PHONY: clean
clean:
	rm lab07s_*.o
	rm liblab07s.so
	rm lab07s.o
	rm lab7static