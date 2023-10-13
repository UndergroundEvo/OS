#include "lab05.h"

// ������� ��� �������� ���� ������ � ����
void exportDatabaseToFile() {
    FILE* file = fopen("database.txt", "w");
    if (file == NULL) {
        printf("�� ������� ������� ���� ��� ������.\n");
        return;
    }

    for (int i = 0; i < databaseSize; i++) {
        fprintf(file, "%s %d %s\n", database[i].name, database[i].age, database[i].address);
    }

    fclose(file);
    printf("���� ������ ������� �������������� � ���� 'database.txt'.\n");
}