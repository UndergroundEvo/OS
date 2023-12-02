#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char *const argv[]) {
    int fd;
    struct stat stat_file;
    char dummy;
    char *map_address;
    fd = open("test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
    if (fd == -1)
        fprintf(stderr, "open\n");
    if (fstat(fd, &stat_file)) // Получаем информацию о файле (размер, права и т.д.)
        fprintf(stderr, "fstat\n");

    // Открываем файл "test.txt" с флагами O_RDWR (открытие для чтения и записи) и O_CREAT (создание, если не существует)
    // и устанавливаем права доступа S_IRUSR (чтение для владельца) | S_IWUSR (запись для владельца) | S_IRGRP (чтение для группы)
    map_address = (char *) mmap(0, stat_file.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

    if (map_address == MAP_FAILED)
        fprintf(stderr, "mmap\n");

    //меняем "This is a test." на "Is this a test?"
    dummy = map_address[1];
    map_address[0] = map_address[5] - 0x20;
    map_address[1] = map_address[3];
    map_address[2] = map_address[4];
    map_address[3] = map_address[10];
    map_address[4] = dummy;
    map_address[14] = 63;

    write(fd, map_address, stat_file.st_size); // Записываем измененные данные обратно в файл
    munmap(map_address, stat_file.st_size); // Освобождаем отображенную область файла из памяти

    close(fd);

    return 0;
}
