#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, char *const argv) {

    int fd;

    char *map_address;

    // Создаем или открываем общую область памяти с именем "/common_region"
    // с флагами O_RDWR (открытие для чтения и записи), O_CREAT (создание, если не существует)
    // и устанавливаем права доступа S_IRUSR (чтение для владельца), S_IWUSR (запись для владельца), S_IRGRP (чтение для группы)
    fd = shm_open("/common_region", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);

    if (fd == -1) fprintf(stderr, "open \n");

    ftruncate(fd, 256); // Устанавливаем размер общей области памяти в 256 байт

    // Отображаем общую область памяти в адресное пространство процесса
    // с правами PROT_READ (чтение), PROT_WRITE (запись) и флагом MAP_SHARED (создаем общее отображение)
    map_address = (char *) mmap(0, 256, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (map_address == MAP_FAILED) fprintf(stderr, "mmap\n");

    //копируем "Take it easy! Be happy!" в общую память
    memcpy(map_address, "Take it easy! Be happy!\0", sizeof("Take it easy! Be happy!\0"));

    getc(stdin);


    munmap(map_address, 256); //очищаем память
    shm_unlink("/common_region"); //разыменовываем область памяти
    close(fd);
    return 0;
}
