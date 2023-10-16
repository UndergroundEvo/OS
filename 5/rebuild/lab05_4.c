#include "lab05.h"

// Функция для просмотра всех записей
void viewAllRecords() {
    system("clear");
    printf("Все записи в базе данных:\n");
    printf("%-3s %-6s %-3s %-6s\n", "Запись", "Имя", "Возраст", "Адрес");
    for (int i = 0; i < databaseSize; i++) {
        printf("%d-3\t%-6s\t%d-3\t%-10s\n", i, database[i].name, database[i].age, database[i].address);
        /*printf("Имя: %s\n", database[i].name);
        printf("Возраст: %d\n", database[i].age);
        printf("Адрес: %s\n", database[i].address);*/
    }
    getchar();
}