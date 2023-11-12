.PHONY: all
all:
	g++ -std=c++20 -pthread lab10_3.cpp -o lab10_3

.PHONY: clean
clean:
	rm lab10_3

.PHONY: zabul
zabul:
	@echo "c таймером: time(./prog)"
	@echo "одно ядро: taskset -c 0 ./prog"
	@echo "все ядра: taskset -c cpu-core-number(s) ./prog"
	@echo "имба: time(taskset -c 0,1 ./lab10_3)"