#include "lab05.h"

// Функция для поиска записи в базе данных
void searchRecord() {
    char searchName[50];
    printf("Введите имя для поиска: ");
    scanf("%s", searchName);

    int found = 0;
    for (int i = 0; i < databaseSize; i++) {
        if (strcmp(database[i].name, searchName) == 0) {
            printf("Найдена запись:\n");
            printf("Имя: %s\n", database[i].name);
            printf("Возраст: %d\n", database[i].age);
            printf("Адрес: %s\n", database[i].address);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Запись с именем \"%s\" не найдена в базе данных.\n", searchName);
    }
}