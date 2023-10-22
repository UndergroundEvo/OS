#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Person {
    char name[50];
    int age;
    char address[100];
}
extern database[100];
extern int databaseSize;

extern char* menu, * n1, * n2, * n3, * n4,
* n5, * n6, * n7, * n0, * action,
* exit_text, * wrong_text;

void addRecord();
void editRecord();
void deleteRecord();
void searchRecord();
void viewAllRecords();
void exportDatabaseToFile();
void importDatabaseFromFile();