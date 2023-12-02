#include <semaphore.h>
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
    sem_t *sem;

    // Создаем или открываем именованную область памяти с именем "/common_region"
    // с флагами O_RDWR (открытие для чтения и записи), O_CREAT (создание, если не существует)
    // и устанавливаем права доступа S_IRUSR (чтение для владельца), S_IWUSR (запись для владельца), S_IRGRP (чтение для группы)
    fd = shm_open("/common_region", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);

    if (fd == -1) fprintf(stderr, "shm_open\n");

    ftruncate(fd, 6); // Устанавливаем размер общей области памяти в 6 байт

    // Отображаем общую область памяти в адресное пространство процесса
    // с правами PROT_READ (чтение), PROT_WRITE (запись) и флагом MAP_SHARED (создаем общее отображение)
    sh = (char *) mmap(0, 6, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (sh == MAP_FAILED) fprintf(stderr, "mmap\n");

    memset(sh, 0, 6);

    sem = sem_open("/common_sem", O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP, 1);

    // 🚦 не работает
    if (sem == SEM_FAILED) fprintf(stderr, "sem_open");

    while (1) {
        n++;
        sem_wait(sem); // Ожидаем, когда 🚦 станет доступным (уменьшаем его значение на 1)
        //write(fileno(stdout),sh, 6);
        printf("String: %s\n", sh); // Выводим содержимое общей области с использованием функции printf
        sem_post(sem); // Освобождаем семафор (увеличиваем его значение на 1)
        usleep(100);
    }

    // Удаляем именованную область памяти, память, именованный 🚦 и его самого
    shm_unlink("/common_region");
    munmap(sh, 6);
    sem_unlink("/common_sem");
    sem_close(sem);
    return 0;
}