#include <stdio.h>
#include <thread>
#include <unistd.h>
typedef int (*fun)(char*);
int g(char* str) {
	printf("%s\n", str);
	return 0;
}void my_thread(void*);
int main() {
	std::thread th(my_thread, (void*)g);
	printf("thread's been created\n");
	th.join();
	printf("parent\n");
	return 0;
}
void my_thread(void* pg) {
	int counter = 0;
	while (1) {
		printf("child\n");
		sleep(1);
		if (++counter > 5)
			break;
	}
	((fun)pg)((char*)"thread_is_over!\n");
}