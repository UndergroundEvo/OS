#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int sh = 0;
int flag[2] = { 1,1 };
void* my_thread0() {
	int i = 0;
	for (; i < 5; i++, sh++)sleep(1);
	flag[0] = 0;
}
void* my_thread1() {
	int i = 0;
	for (; i < 5; i++, sh += 2)sleep(1);
	flag[1] = 0;
}int main() {
	pthread_t th_id[2];
	pthread_create(&th_id[0], NULL, &my_thread0, NULL);
	pthread_create(&th_id[1], NULL, &my_thread1, NULL);
	while (flag[0] || flag[1]);
	printf("%i\n", sh);
	return 0;
}