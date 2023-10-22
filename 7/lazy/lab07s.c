#include <stdio.h>
#include <dlfcn.h>
//#include "lab07.h"

struct Person {
    char name[50];
    int age;
    char address[100];
};
struct Person database[100];
int databaseSize = 0;
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

int main() {
    system("clear");
    printf("%s\n", "для загрузки .so нажмите Enter");
    getchar();
    void* handle = dlopen("./liblab05.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, " нету .so файла, проверьте название файла 🦣 %s\n", dlerror());
        return 1;
    };

    void* (*func1)();

    int choice;
    while (1) {
        printf("\n%s\n",menu);
        printf("%s\n", n1);
        printf("%s\n", n2);
        printf("%s\n", n3);
        printf("%s\n", n4);
        printf("%s\n", n5);
        printf("%s\n", n6);
        printf("%s\n", n7);
        printf("%s\n", n0);
        printf("%s\n", action);
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            func1 = dlsym(handle, "addRecord");
            (*func1)();
            break;
        case 2:
            func1 = dlsym(handle, "editRecord");
            (*func1)();
            break;
        case 3:
            func1 = dlsym(handle, "deleteRecord");
            (*func1)();
            break;
        case 4:
            func1 = dlsym(handle, "searchRecord");
            (*func1)();
            break;
        case 5:
            func1 = dlsym(handle, "viewAllRecords");
            (*func1)();
            break;
        case 6:
            func1 = dlsym(handle, "exportDatabaseToFile");
            (*func1)();
            break;
        case 7:
            func1 = dlsym(handle, "importDatabaseFromFile");
            (*func1)();
            break;
        case 0:
            printf("%s\n", exit_text);
            dlclose(handle);
            getchar();
            return 0;
        default:
            printf("%s\n", wrong_text);
        }
    }
    return 0;
}