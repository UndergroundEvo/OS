#include "lab05.h"

struct Person database[100];
int databaseSize = 0;

// ������� ��� ���������� ������ � ���� ������
void addRecord() {
    if (databaseSize < 100) {
        struct Person newPerson;
        printf("������� ���: ");
        scanf("%s", newPerson.name);
        printf("������� �������: ");
        scanf("%d", &newPerson.age);
        printf("������� �����: ");
        scanf("%s", newPerson.address);

        database[databaseSize++] = newPerson;
        printf("������ ��������� � ���� ������.\n");
    }
    else {
        printf("���� ������ �����, ���������� �������� ������ �������.\n");
    }
}