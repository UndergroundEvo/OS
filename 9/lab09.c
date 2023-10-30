#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

char sh[6];
int n = 100;

void *Thread(void *pParams);

int main(void)
{
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, &Thread, NULL);
	while (1)
		printf("%s\n", sh);
}

void *Thread(void *pParams)
{
	int counter = 0;
	while (1)
	{
		if (counter % 2)
		{
			sh[0] = 'H';
			sh[1] = 'e';
			sh[2] = 'l';
			sh[3] = 'l';
			sh[4] = 'o';
			sh[5] = '\0';
		}
		else
		{
			sh[0] = 'B';
			sh[1] = 'y';
			sh[2] = 'e';
			sh[3] = '_';
			sh[4] = 'u';
			sh[5] = '\0';
		}
		counter++;
	}
	return NULL;
}