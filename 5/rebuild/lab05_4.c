#include "lab05.h"

// ������� ��� ��������� ���� �������
void viewAllRecords() {
    system("clear");
    printf("��� ������ � ���� ������:\n");
    printf("%-3s %-6s %-3s %-6s\n", "������", "���", "�������", "�����");
    for (int i = 0; i < databaseSize; i++) {
        printf("%d-3\t%-6s\t%d-3\t%-10s\n", i, database[i].name, database[i].age, database[i].address);
        /*printf("���: %s\n", database[i].name);
        printf("�������: %d\n", database[i].age);
        printf("�����: %s\n", database[i].address);*/
    }
    getchar();
}