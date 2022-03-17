#ifndef studRegSystem_h
#define studRegSystem_h

/**************************************************************************
Declare header include files
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void populateRegistrationTable();

int addValue();

int getStudentId();

int CheckCourseCode(char code[]);

int checkIntegerInput(int count);

void registerStudent();

void dropStudent();

void menu();

int searchStudentId(int idToSearch);

int searchCourseCodeId(char courseCodeToSearch[8]);

void setValueInRegistrationTable(int studentIndex, int courseCodeIndex,
		int valueToSet);

void printRegistrationTable();

void initializeRegistrationTable();

void deleteAllocatedMemory();

#endif