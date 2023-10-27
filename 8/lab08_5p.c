#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4
#define ITERATIONS 500000000

long double pi = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* calculate_pi(void* thread_id) {
    long double local_pi = 0;
    int thread_num = *(int*)thread_id;
    int start = thread_num * (ITERATIONS / NUM_THREADS) + 1;
    int end = (thread_num + 1) * (ITERATIONS / NUM_THREADS);

    for (int i = start; i <= end; i++) local_pi += (i % 2 == 1) ? (long double)4 / (2 * i - 1) : -(long double)4 / (2 * i - 1);

    pthread_mutex_lock(&mutex);
    pi += local_pi;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main() {
    clock_t start = clock();
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, calculate_pi, (void*)&thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) pthread_join(threads[i], NULL);

    printf("w = %2d p = %2d pi = %*.*Lf\n", 62, 62, 62, 62, pi);

    clock_t end = clock();
    printf("%s%f%s\n", "Потрачено на вычисление и вывод: ", (double)(end - start) / CLOCKS_PER_SEC, " сек.");
    pthread_mutex_destroy(&mutex);
    return 0;
}
