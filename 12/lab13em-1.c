#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

int main(void) {
    int n = 0;
    int fd;
    char *sh;

    pthread_mutex_t *Mutex; // Указатель на мьютекс (синхронизация доступа к общей памяти)
    pthread_mutexattr_t mutex_attr; // Атрибуты мьютекса

    // Создаем или открываем именованную область памяти с именем "/common_region1"
    // с флагами O_RDWR (открытие для чтения и записи), O_CREAT (создание, если не существует)
    // и устанавливаем права доступа S_IRUSR (чтение для владельца), S_IWUSR (запись для владельца), S_IRGRP (чтение для группы)
    fd = shm_open("/common_region1", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);

    if (fd == -1) fprintf(stderr, "shm_open\n");

    ftruncate(fd, 6); // Устанавливаем размер общей области памяти в 6 байт

    // Отображаем общую область памяти в адресное пространство процесса
    // с правами PROT_READ (чтение), PROT_WRITE (запись) и флагом MAP_SHARED (создаем общее отображение)
    sh = (char *) mmap(0, 6, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (sh == MAP_FAILED) fprintf(stderr, "mmap\n");

    close(fd);
    memset(sh, 0, 6); // Заполняем общую область памяти нулями

    fd = shm_open("/common_mutex", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);

    if (fd == -1) fprintf(stderr, "shm_open for mutex\n");

    ftruncate(fd, sizeof(pthread_mutex_t)); // Устанавливаем размер области памяти для мьютекса в размер pthread_mutex_t

    pthread_mutexattr_init(&mutex_attr); // Инициализируем атрибуты мьютекса
    pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED); // Устанавливаем атрибут PTHREAD_PROCESS_SHARED, чтобы мьютекс был видим в разных процессах
    // Отображаем область памяти для мьютекса в адресное пространство процесса
    Mutex = (pthread_mutex_t *) mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    close(fd);

    pthread_mutex_init(Mutex, &mutex_attr); // Инициализируем мьютекс с использованием атрибутов

    while (1) {
        pthread_mutex_lock(Mutex); // Захватываем мьютекс
        //write(fileno (stdout), sh, 6);
        printf("String: %sin", sh);
        pthread_mutex_unlock(Mutex); // Освобождаем мьютекс
    }

    munmap(sh, 6);

    munmap(Mutex, sizeof(pthread_mutex_t));

    shm_unlink("/common_mutex");
    shm_unlink("/common_region1");

    getc(stdin);
    return 0;
}


