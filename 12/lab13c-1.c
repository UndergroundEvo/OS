#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, char *const argv[]) {

    int fd;

    struct stat stat_file;

    char *map_address;
    // Открываем файл "test_shared.txt"
    fd = open("test_shared.txt", O_RDWR | O_CREAT, S_IWUSR | S_IRGRP);

    if (fd == -1)
        fprintf(stderr, "open\n");

    // Отображаем файл в память с правами PROT_READ (чтение), PROT_WRITE (запись)
    // и флагом MAP_SHARED (создаем общее отображение файла)
    map_address = (char *) mmap(0, 256, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (map_address == MAP_FAILED)
        fprintf(stderr, "mmap\n");

    close(fd);
    // Копируем строку "Take it easy!" в отображенную область файла
    memcpy(map_address, "Take it easy!\0", sizeof("Take it easy!\0"));


    getc(stdin);

    // Освобождаем отображенную область файла из памяти
    munmap(map_address, 256);
    return 0;
}
