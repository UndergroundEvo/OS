#include "lab05.h"



// ������� ��� �������������� ������ � ���� ������
void editRecord() {
    int index;
    printf("������� ����� ������ ��� �������������� (0-%d): ", databaseSize - 1);
    scanf("%d", &index);

    if (index >= 0 && index < databaseSize) {
        struct Person* person = &database[index];
        printf("������� ������:\n");
        printf("���: %s\n", person->name);
        printf("�������: %d\n", person->age);
        printf("�����: %s\n", person->address);

        printf("������� ����� ������:\n");
        printf("���: ");
        scanf("%s", person->name);
        printf("�������: ");
        scanf("%d", &person->age);
        printf("�����: ");
        scanf("%s", person->address);

        printf("������ ������� ���������������.\n");
    }
    else {
        printf("������������ ����� ������.\n");
    }
}