#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Person {
    char name[50];
    int age;
    char address[100];
};

// Глобальная база данных, ограниченная 100 записями
struct Person database[100];
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

// Функция для просмотра всех записей
void viewAllRecords() {
    system("clear");
    printf("Все записи в базе данных:\n");
    printf("%-3s %-6s %-3s %-6s\n","Запись","Имя","Возраст","Адрес");
    for (int i = 0; i < databaseSize; i++) {
        printf("%d-3\t%-6s\t%d-3\t%-10s\n", i, database[i].name, database[i].age , database[i].address);
        /*printf("Имя: %s\n", database[i].name);
        printf("Возраст: %d\n", database[i].age);
        printf("Адрес: %s\n", database[i].address);*/
    }
    getchar();
}

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
