#include <stdio.h>


int main() {
    system("clear");
    int choice;
    while (1) {
        printf("\n����:\n");
        printf("1. �������� ������\n");
        printf("2. ������������� ������\n");
        printf("3. ������� ������\n");
        printf("4. ����� ������\n");
        printf("5. �������� ���� �������\n");
        printf("6. ������� ���� ������ � ����\n");
        printf("7. ������ ���� ������ �� �����\n");
        printf("0. �����\n");
        printf("�������� �������� (1-0): ");
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
            printf("����� �� ���������.\n");
            return 0;
        default:
            printf("�������� �����. ���������� �����.\n");
        }
    }
    return 0;
}