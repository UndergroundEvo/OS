#include "lab05.h"

// ������� ��� ������ ������ � ���� ������
void searchRecord() {
    char searchName[50];
    printf("������� ��� ��� ������: ");
    scanf("%s", searchName);

    int found = 0;
    for (int i = 0; i < databaseSize; i++) {
        if (strcmp(database[i].name, searchName) == 0) {
            printf("������� ������:\n");
            printf("���: %s\n", database[i].name);
            printf("�������: %d\n", database[i].age);
            printf("�����: %s\n", database[i].address);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("������ � ������ \"%s\" �� ������� � ���� ������.\n", searchName);
    }
}