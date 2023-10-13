#include "lab05.h"

// Функция для экспорта базы данных в файл
void exportDatabaseToFile() {
    FILE* file = fopen("database.txt", "w");
    if (file == NULL) {
        printf("Не удалось открыть файл для записи.\n");
        return;
    }

    for (int i = 0; i < databaseSize; i++) {
        fprintf(file, "%s %d %s\n", database[i].name, database[i].age, database[i].address);
    }

    fclose(file);
    printf("База данных успешно экспортирована в файл 'database.txt'.\n");
}