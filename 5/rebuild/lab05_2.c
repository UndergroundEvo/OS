#include "lab05.h"

// ������� ��� �������� ������ �� ���� ������
void deleteRecord() {
    int index;
    printf("������� ����� ������ ��� �������� (0-%d): ", databaseSize - 1);
    scanf("%d", &index);

    if (index >= 0 && index < databaseSize) {
        for (int i = index; i < databaseSize - 1; i++) {
            database[i] = database[i + 1];
        }
        databaseSize--;
        printf("������ ������� �� ���� ������.\n");
    }
    else {
        printf("������������ ����� ������.\n");
    }
}