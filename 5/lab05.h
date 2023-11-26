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

void addRecord();
void editRecord();
void deleteRecord();
void searchRecord();
void viewAllRecords();
void exportDatabaseToFile();
void importDatabaseFromFile();