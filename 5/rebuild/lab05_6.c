#include "lab05.h"

// ������� ��� ������� ���� ������ �� �����
void importDatabaseFromFile() {
    FILE* file = fopen("database.txt", "r");
    if (file == NULL) {
        printf("���� 'database.txt' �� ������.\n");
        return;
    }

    databaseSize = 0;
    while (fscanf(file, "%s %d %s", database[databaseSize].name, &database[databaseSize].age, database[databaseSize].address) != EOF) {
        databaseSize++;
    }

    fclose(file);
    printf("���� ������ ������� ������������� �� ����� 'database.txt'.\n");
}