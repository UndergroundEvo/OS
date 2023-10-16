#include <stdio.h>
#include "lab05.h"

int main() {
    system("clear");
    int choice;
    while (1) {
        printf("\nМеню:\n");
        printf("1. Добавить запись\n");
        printf("2. Редактировать запись\n");
        printf("3. Удалить запись\n");
        printf("4. Поиск записи\n");
        printf("5. Просмотр всех записей\n");
        printf("6. Экспорт базы данных в файл\n");
        printf("7. Импорт базы данных из файла\n");
        printf("0. Выйти\n");
        printf("Выберите действие (1-0): ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addRecord();
            break;
        case 2:
            editRecord();
            break;
        case 3:
            deleteRecord();
            break;
        case 4:
            searchRecord();
            break;
        case 5:
            viewAllRecords();
            break;
        case 6:
            exportDatabaseToFile();
            break;
        case 7:
            importDatabaseFromFile();
            break;
        case 0:
            printf("Выход из программы.\n");
            return 0;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
    return 0;
}