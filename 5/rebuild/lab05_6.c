#include "lab05.h"

// Функция для импорта базы данных из файла
void importDatabaseFromFile() {
    FILE* file = fopen("database.txt", "r");
    if (file == NULL) {
        printf("Файл 'database.txt' не найден.\n");
        return;
    }

    databaseSize = 0;
    while (fscanf(file, "%s %d %s", database[databaseSize].name, &database[databaseSize].age, database[databaseSize].address) != EOF) {
        databaseSize++;
    }

    fclose(file);
    printf("База данных успешно импортирована из файла 'database.txt'.\n");
}