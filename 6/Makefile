.PHONY: all
all:
	gcc lab06_1.c -o lab06_1
	gcc lab06_2.c -o lab06_2
	gcc lab06_3.c -o lab06_3

.PHONY: clean
clean:
	rm lab06_1
	rm lab06_2
	rm lab06_3

.PHONY: zabul
zabul:
	@echo "c таймером: time(./prog)"
	@echo "одно ядро: taskset -c 0 ./prog"
	@echo "все ядра: taskset -c cpu-core-number(s) ./prog"
	@echo "имба: time(taskset -c 0,1 ./lab10_3)"