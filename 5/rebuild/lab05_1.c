#include "lab05.h"



// Функция для редактирования записи в базе данных
void editRecord() {
    int index;
    printf("Введите номер записи для редактирования (0-%d): ", databaseSize - 1);
    scanf("%d", &index);

    if (index >= 0 && index < databaseSize) {
        struct Person* person = &database[index];
        printf("Текущая запись:\n");
        printf("Имя: %s\n", person->name);
        printf("Возраст: %d\n", person->age);
        printf("Адрес: %s\n", person->address);

        printf("Введите новые данные:\n");
        printf("Имя: ");
        scanf("%s", person->name);
        printf("Возраст: ");
        scanf("%d", &person->age);
        printf("Адрес: ");
        scanf("%s", person->address);

        printf("Запись успешно отредактирована.\n");
    }
    else {
        printf("Неправильный номер записи.\n");
    }
}