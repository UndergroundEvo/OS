#include "lab07.h"

char* menu = "Меню";
char* n1 = "1. Добавить запись";
char* n2 = "2. Редактировать запись";
char* n3 = "3. Удалить запись";
char* n4 = "4. Поиск записи";
char* n5 = "5. Просмотр всех записей";
char* n6 = "6. Экспорт базы данных в файл";
char* n7 = "7. Импорт базы данных из файла";
char* n0 = "0. Выйти";

char* action = "Выберите действие (1-0): ";
char* exit_text = "Выход из программы.";
char* wrong_text = "Неверный выбор. Попробуйте снова.";

struct Person database[100] = {1};
int databaseSize = 0;

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