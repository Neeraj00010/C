#include "studRegSystem.h"

int *students;
char **courses;
int **registrationTable;
int totalRows;
int numOfStudents, numOfCourses;
 /*this is the return code of the user input*/
int rc;

void populateRegistrationTable() {

	registrationTable = (int**) malloc(totalRows * sizeof(int*));

	int rowCounter;
	for (rowCounter = 0; rowCounter < totalRows; rowCounter++)
		registrationTable[rowCounter] = (int*) malloc(3 * sizeof(int));

	initializeRegistrationTable();

	int counter = 0;
	int studentIndex = 0;

	for (rowCounter = 0; rowCounter < totalRows; rowCounter++) {

		if (counter != numOfCourses) {
			registrationTable[rowCounter][0] = studentIndex;
			registrationTable[rowCounter][1] = counter;
			counter++;
		} else {
			studentIndex++;
			counter = 0;
			rowCounter--;
		}
	}
}

int addValue() {

	int counter;

	printf("Enter the number of students to register: ");
	scanf("%d", &numOfStudents);
	students = (int*) malloc(numOfStudents * sizeof(int));

	for (counter = 0; counter < numOfStudents; counter++) {
		printf("Enter the student index[%d] student-id [5-digits]: ", (counter));
		students[counter] = checkIntegerInput(counter);

		while (students[counter] < 10000 || students[counter] > 99999) {
			printf("Student id must be of 5 digits.\n");
			printf("Enter the student index[%d] student-id [5-digits]: ", (counter));
		    students[counter] = checkIntegerInput(counter);
		}
		/*Check for duplicate IDs*/
		int i;

        for (i = 0; i < counter; i++)
        {
            if (students[i] == students[counter])
            {
                 printf("Error: Student IDs have to be unique (no duplicates). Try again.\n");
                 i = counter;
                /*If the user enters a duplicate ID it ovewrite it*/
                 counter--;
            } /*end if */
        }   /*end for */
	} /*end outer-for*/

	printf("\n");

/**************************************************************************
                        Prompt for courses' codes
***************************************************************************/
	printf("Enter the number of courses avalaible: ");
	scanf("%d", &numOfCourses);
	courses = (char**) malloc(numOfCourses * sizeof(char*));

	for (counter = 0; counter < numOfCourses; counter++)
		courses[counter] = (char*) malloc(8 * sizeof(char*));

	for (counter = 0; counter < numOfCourses; counter++) {
		printf("Enter the course index[%d] course-id [3-Alphas] [4-digits]: ", (counter));

		rc = 0;

    /*Prompts for course code and checks each character*/
    while (rc != 7)
      {
        char code[7+1];
        scanf(" %8[^\n]s", code);
        /*Returns 7 if all characters are valid "LLLNNNN"*/
        rc = CheckCourseCode(code);

        /*Repromt if not a valid code*/
        if (rc != 7)
        {
		  fflush(stdin);
          printf("Incorrect course Id input [3-Aphas][4-digits]\n");
          rc = 0;
        }/*end if */

        /*Store valid codes in the courses array*/
        else{
         strcpy(*(&courses[counter]), code);
        }/*end else */
	  }/*end while*/
	  
	int i;
	  /*Check for duplicate codes*/
    for (i = 0; i < counter; i++)
    {

      if (!strcmp(courses[i], courses[counter]))
      {
        printf("Error: course IDs are unique (no duplicates). Try again.\n");
        i = counter;
        /*If the user enters a duplicate ID it ovewrite it*/
        counter--;
      } /*end if */
    }   /*end for */

	}/*end for*/
	printf("\n");

	totalRows = numOfStudents * numOfCourses;
	populateRegistrationTable();

	return 1;
}

int getStudentId() {

	int studentId;
	printf("Enter the student's Id to register a course: ");
	scanf("%d", &studentId);
	return studentId;

}

int CheckCourseCode(char code[])
{
  /*This the return code */
  int rc=0;
  /*This the array index */
  int index;

    /*Display error message if not a 7 charachetrs string input and returns 0*/
    if (strlen(code) != 7)
    {
      printf("Incorrect course Id input [3-Aphas][4-digits]\n");
      rc = 0;
      while (getchar() != '\n')
      { /* chomp stdin */ }/*end  while*/
    } /*end if*/

    /*Counts the number of valid characters in the code*/
    else
    {
      for (index = 0; index < strlen(code); index++)
      {
        if (index < 3 && isalpha(code[index]))
        {
          ++rc;
        } /*end  if*/
        else if (index >= 3 && isdigit(code[index]))
        {
          ++rc;
        } /*end  else if*/
      } /*end for*/
    }/*end  else*/

  /*Return the number of valid characters in the code entered*/
  return rc;

} /* end CheckCourseCode */

int checkIntegerInput(int count)
{

  /*This is the user input */
  int number;
  /*This the return code */
  int rc = 0;
  /*This the next char after scanf() terminates */
  char nextChar;

  /*Loops untill the user enter a valid input */
  while (rc != 1)
  {
    /*it takes 1 if scanf reads an integer*/
    rc = scanf(" %d", &number);
    /*Read the next character in stdin after scanf is executed*/
    nextChar = getchar();

    /*Prints an error message if the user enters an invalid input (strings/float/negative integer)
    and goes back to the while loop*/
    if (rc != 1 || nextChar != '\n' || number < 0)
    {
      rc = 0;
      printf("Student ID must be 5 digits\n");
	  printf("Enter the student index[%d] student-id [5-digits]: ", (count));
      fflush(stdin);
      /*if not a valid input clear the stdin*/
      if (nextChar != '\n')
      {
        while (getchar() != '\n')
        { /*chomp stdin*/ } /*end while*/
      }   /*end  if*/
    }     /*end outer-if*/
  } /*end outer-while*/

  /*return valid input*/
  return number;

} /* end checkIntegerInput */


void registerStudent() {

	printf("List of Student Ids\n");

	int counter;

	for(counter = 0; counter < numOfStudents; counter++){
		printf("Index %d \t\t\t\t%d" , counter, students[counter]);
		printf("\n");
	}

	int studentId = getStudentId();
	int studentIndex = searchStudentId(studentId);

    printf("List of Available Course Id\n");
	char courseCode[8];

    for(counter = 0; counter < numOfCourses; counter++){
		printf("Index %d \t\t\t\t%s" , counter , courses[counter]);
		printf("\n");
	}

	printf("Enter the course id [3-Alphas][4-digits]: ");
	scanf("%s", courseCode);

	int courseCodeIndex = searchCourseCodeId(courseCode);

	if (studentIndex == -1 || courseCodeIndex == -1)
		return;

	setValueInRegistrationTable(studentIndex, courseCodeIndex, 1);
	printf("Registration Successful\n");

}
void dropStudent() {

	int studentId = getStudentId();
	char courseCode[8];
	printf("Enter course code: ");
	scanf("%s", courseCode);

	int studentIndex = searchStudentId(studentId);
	int courseCodeIndex = searchCourseCodeId(courseCode);

	if (studentIndex == -1 || courseCodeIndex == -1)
		return;

	setValueInRegistrationTable(studentIndex, courseCodeIndex, 0);
}
void menu() {

	int userInput;
	printf("Main Menu:\n");
	printf("\t[1] Register a student into a course.\n");
	printf("\t[2] Drop a student from a course.\n");
	printf("\t[3] Display Registration table.\n");
	printf("\t[4] Exit.\nEnter an option from the menu: ");

	scanf("%d", &userInput);

	switch (userInput) {
	case 1:
		registerStudent();
		break;
	case 2:
		dropStudent();
		break;
	case 3:
		printRegistrationTable();
		break;
	case 4:
		return;
		break;
	}
	printf("\n");
	menu();

}

int searchStudentId(int idToSearch) {

	int counter;
	int studentIndex = -1;
	for (counter = 0; counter < numOfStudents; counter++) {

		if (students[counter] == idToSearch) {
			studentIndex = counter;
			break;
		}

	}
	if (studentIndex == -1) {
		printf("No match with given student id.");
		return -1;
	} else {
		return studentIndex;
	}
}

void deleteAllocatedMemory() {

	free(students);
	free(courses);
	free(registrationTable);

}

int searchCourseCodeId(char courseCodeToSearch[8]) {
	int counter;
	int courseIndex = -1;
	for (counter = 0; counter < numOfCourses; counter++) {

		if (!strcmp(courseCodeToSearch, courses[counter])) {
			courseIndex = counter;
			break;
		}

	}
	if (courseIndex == -1) {
		printf("No match with given course code.");
		return -1;
	} else {
		return courseIndex;
	}

	return courseIndex;
}

void setValueInRegistrationTable(int studentIndex, int courseCodeIndex, int valueToSet) {

	int counter;
	for (counter = 0; counter < totalRows; counter++) {

		if (registrationTable[counter][0] == studentIndex
				&& registrationTable[counter][1] == courseCodeIndex) {
			registrationTable[counter][2] = valueToSet;
			break;
		}
	}
}

void printRegistrationTable() {

	printf("\n\t\t\tRegistration Table\nRegistration Index\tStudent ID\tCourse ID\tRegistration Status\n\n");

	int rowCounter;
	int counter = 0;
	int studentIndex = 0;

	for (rowCounter = 0; rowCounter < numOfStudents; rowCounter++) {

		if (counter != numOfCourses && students[rowCounter] != 0) {

			if (registrationTable[rowCounter][2])
				printf("  \t%d\t\t%d\t\t%s\tR\n", rowCounter, students[studentIndex], courses[counter]);
			else
				printf("  \t%d\t\t%d\t\t%s\tD\n", rowCounter, students[studentIndex], courses[counter]);

		} else {
			studentIndex++;
			counter = 0;
			rowCounter--;
		}
	}

}

void initializeRegistrationTable() {

	int i;
	for (i = 0; i < totalRows; i++) {
		int j;
		for (j = 0; j < 3; j++) {
			registrationTable[i][j] = 0;
		}
	}
}

int main() {

    printf("Welcome to Student Registration System.\n\n");
	if (addValue())
		menu();
	else {
		main();
	}

	deleteAllocatedMemory();
	return 1;

}