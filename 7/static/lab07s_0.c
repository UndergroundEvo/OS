#include "lab07.h"

// Функция для добавления записи в базу данных
void addRecord() {
    if (databaseSize < 100) {
        struct Person newPerson;
        printf("Введите имя: ");
        scanf("%s", newPerson.name);
        printf("Введите возраст: ");
        scanf("%d", &newPerson.age);
        printf("Введите адрес: ");
        scanf("%s", newPerson.address);

        database[databaseSize++] = newPerson;
        printf("Запись добавлена в базу данных.\n");
    }
    else {
        printf("База данных полна, невозможно добавить больше записей.\n");
    }
}