.PHONY: all
all:
	g++ -std=c++11 -pthread lab11_1.cpp -o lab11_1
	g++ -std=c++11 -pthread lab11_2.cpp -o lab11_2

.PHONY: clean
clean:
	rm lab11_1
	rm lab11_2

.PHONY: zabul
zabul:
	@echo "c таймером: time(./prog)"
	@echo "одно ядро: taskset -c 0 ./prog"
	@echo "все ядра: taskset -c cpu-core-number(s) ./prog"
	@echo "имба: time(taskset -c 0,1 ./lab10_3)"