.PHONY: all
all:
	gcc lab13b.c -o lab13b
	gcc lab13c-1.c -o lab13c-1
	gcc lab13c-2.c -o lab13c-2
	gcc lab13d-1.c -lrt -o lab13d-1
	gcc lab13d-2.c -lrt -o lab13d-2
	gcc lab13em-1.c -o lab13em-1
	gcc lab13em-2.c -o lab13em-2
	gcc lab13e-1.c -lpthread -lrt -o lab13e-1
	gcc lab13e-2.c -lpthread -lrt -o lab13e-2

.PHONY: clean
clean:
	rm lab13b
	rm lab13c-1
	rm lab13c-2
	rm lab13d-1
	rm lab13d-2
	rm lab13em-1
	rm lab13em-2
	rm lab13e-1
	rm lab13e-2

.PHONY: zabul
zabul:
	@echo "c таймером: time(./prog)"
	@echo "одно ядро: taskset -c 0 ./prog"
	@echo "все ядра: taskset -c cpu-core-number(s) ./prog"
	@echo "имба: time(taskset -c 0,1 ./lab10_3)"
