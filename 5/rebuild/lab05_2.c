#include "lab05.h"

// Функция для удаления записи из базы данных
void deleteRecord() {
    int index;
    printf("Введите номер записи для удаления (0-%d): ", databaseSize - 1);
    scanf("%d", &index);

    if (index >= 0 && index < databaseSize) {
        for (int i = index; i < databaseSize - 1; i++) {
            database[i] = database[i + 1];
        }
        databaseSize--;
        printf("Запись удалена из базы данных.\n");
    }
    else {
        printf("Неправильный номер записи.\n");
    }
}