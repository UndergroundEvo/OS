#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
typedef int (*fun)(char*, int*);
int q = 1;
int g(char* str, int* p) {
	*p = 0;
	printf("%s\t%d\n", str, q);
	return 0;
}

void* my_thread(void*);

int main(){
	pthread_t th_id;
	pthread_create(&th_id, NULL, &my_thread, (void*)g);
	while (q) {
		printf("parent\t%d\n", q);
		sleep(1);
	}
	return 0;
}

void* my_thread(void* pg) {
	int counter = 0;
	while (q) {
		printf("child\n");
		sleep(1);
		if (counter++ > 5)
			break;
	}
	((fun)pg)("thread_is_over!\n", &q);
}