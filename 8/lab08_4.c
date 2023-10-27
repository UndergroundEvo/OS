#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int sh = 0;
pthread_barrier_t barrier;
void* my_thread0() {
	int i = 0;
	for (; i < 5; i++, sh++)sleep(1);
	pthread_barrier_wait(&barrier);
}
void* my_thread1() {
	int i = 0;
	for (; i < 5; i++, sh += 2)sleep(1);
	pthread_barrier_wait(&barrier);
}
int main() {
	pthread_t th_id[2];
	pthread_barrier_init(&barrier, NULL, 3);
	pthread_create(&th_id[0], NULL, &my_thread0, NULL);
	pthread_create(&th_id[1], NULL, &my_thread1, NULL);
	pthread_barrier_wait(&barrier);
	printf("%i\n", sh);
	pthread_barrier_destroy(&barrier);
	return 0;
}