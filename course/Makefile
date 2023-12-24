.PHONY: all
all:
	gcc course.c course.h -o course

.PHONY: service
service:
	gcc course_systemV.c course.h -o service/course_systemV
	cp service/course_systemV /home/miron/
	cp service/course_systemV.service /etc/systemd/system/
	sudo systemctl daemon-reload
	sudo systemctl enable course_systemV.service
	sudo systemctl start course_systemV.service
	sudo systemctl status course_systemV.service

.PHONY: stop
stop:
	sudo systemctl stop course_systemV.service
	sudo systemctl status course_systemV.service

.PHONY: clean
clean:
	rm course
	rm log.txt

.PHONY: cl_s
cl_s:
	rm service/course_systemV
	rm /home/miron/course_systemV

.PHONY: zabul
zabul:
	@echo "c таймером: time(./prog)"
	@echo "одно ядро: taskset -c 0 ./prog"
	@echo "все ядра: taskset -c cpu-core-number(s) ./prog"
	@echo "имба: time(taskset -c 0,1 ./lab10_3)"
