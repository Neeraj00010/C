/*
* Title: Lab Assessment #3 - Student Registration System  
* Course: CST8234 C Language 
* @Author: Neeraj Bansal (041000185)
* Lab Section: 011 
* Professor: Surbhi Bahri 
* Due date: 03/06/22 
* Submission date: 03/06/22
*
*   Status:
*   Requirement #1:{complete}
*   Requirement #2:{complete}
*   Requirement #3:{complete}
*   Requirement #4:{complete}
*   Requirement #5:{complete}
*   Requirement #6:{complete}
*   Requirement #7:{complete}
*   Requirement #8:{complete}
*   Requirement #9:{complete}
**/

/**************************************************************************
Declared include files
***************************************************************************/
#include "studRegSystem.h"

/**************************************************************************
Declared global variables
***************************************************************************/

/*This is the pointer array that holds the integer studens' IDs*/
int *students;
/*This is the pointer array that holds the string courses'codes(LLLNNNN)*/
char **courses;
/*This is the pointer to pointer array that holds the status of each student*/
int **registrationTable;
/*This is the number of students to register */
int numOfStudents;
/*This is the number of the offered courses */
int numOfCourses;
/*This is the total number of rows for registration table: numStudents*numCourses */
int totalRows;
/*This is the return code of the user input*/
int rc;

/***************************************************************************** 
 * Function Name:  populateRegistrationTable
 * Purpose: Populate registration table
 * Function in parameters: void 
 * Function out parameter: NA
 * Version: 1 
 * Author: Neeraj Kumar Bansal
 * *****************************************************************************/
void populateRegistrationTable() {

    /*Local variable for counting*/
    int rowCounter;
	/*Local variable for counting of courses*/
	int counter = 0;
	/*Local variable for counting of student indexes*/
	int studentIndex = 0;

	registrationTable = (int**) malloc(totalRows * sizeof(int*));            /*allocate proper memory to array*/

	for (rowCounter = 0; rowCounter < totalRows; rowCounter++)
		registrationTable[rowCounter] = (int*) malloc(3 * sizeof(int));             /*allocate proper memory to array for index*/

	initializeRegistrationTable();                                               /*method called*/

	for (rowCounter = 0; rowCounter < totalRows; rowCounter++) {

		if (counter != numOfCourses) {
			registrationTable[rowCounter][1] = studentIndex;
			registrationTable[rowCounter][2] = counter;
			counter++;
		} else {
			studentIndex++;
			counter = 0;
			rowCounter--;
		}
	}
}

/***************************************************************************** 
 * Function Name:  addValue
 * Purpose: Add values into arrays
 * Function in parameters: Integer 
 * Function out parameter: EXIT_SUCCESS
 * Version: 1 
 * Author: Neeraj Kumar Bansal
 * *****************************************************************************/
int addValue() {

    /*Local variable for counting*/
    int counter;
	/*Check for duplicate IDs*/
	int i;

	printf("Enter the number of students to register: ");
	scanf("%d", &numOfStudents);
	students = (int*) malloc(numOfStudents * sizeof(int));         /*allocate proper memory to array*/

	for (counter = 0; counter < numOfStudents; counter++) {
		printf("Enter the student index[%d] student-id [5-digits]: ", (counter));
		students[counter] = checkIntegerInput(counter);

		while (students[counter] < 10000 || students[counter] > 99999) {
			printf("Student id must be of 5 digits.\n");
			printf("Enter the student index[%d] student-id [5-digits]: ", (counter));
		    students[counter] = checkIntegerInput(counter);
		}

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
	courses = (char**) malloc(numOfCourses * sizeof(char*));             /*allocate proper memory to array*/

	for (counter = 0; counter < numOfCourses; counter++)
		courses[counter] = (char*) malloc(8 * sizeof(char*));              /*allocate proper memory to array for index*/

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
          printf("Incorrect course Id length [7-character ID]\n");
		  printf("Enter the course index course-id [3-Alphas] [4-digits]: ");
          rc = 0;
        }
        else
		{  /*Store valid codes in the courses array*/
            strcpy(*(&courses[counter]), code);
        }/*end if-else */
	}/*end while*/
	  
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
    }   /*end inner-for */

	}/*end outer-for*/
	printf("\n");

	totalRows = numOfStudents * numOfCourses;
	populateRegistrationTable();

	return 1;
}

/***************************************************************************** 
 * Function Name:  getStudentId
 * Purpose: Take student ID to register a student into a course
 * Function in parameters: Integer 
 * Function out parameter: studentId
 * Version: 1 
 * Author: Neeraj Kumar Bansal
 * *****************************************************************************/
int getStudentId() {
    
	/*Local variable for taking ID*/
	int studentId;

	printf("Enter the student's Id to register a course: ");
	scanf("%d", &studentId);                          /*take ID input from user*/

	return studentId;
}

/***************************************************************************** 
 * Function Name:  CheckCourseCode
 * Purpose: Check integer input, if its other data type or not in order LLLNNNN respective process takes place in method
 * Function in parameters: Integer 
 * Function out parameter: rc
 * Version: 1 
 * Author: Neeraj Kumar Bansal
 * *****************************************************************************/
int CheckCourseCode(char code[])
{
  /*This the return code */
  int rc=0;

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
      for (size_t index = 0; index < strlen(code); index++)
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

/***************************************************************************** 
 * Function Name:  checkIntegerInput
 * Purpose: Check integer input, if its other data type respective process takes place in method
 * Function in parameters: Integer 
 * Function out parameter: number
 * Version: 1 
 * Author: Neeraj Kumar Bansal
 * *****************************************************************************/
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

/***************************************************************************** 
 * Function Name:  registerStudent
 * Purpose: Register student into course by taking student ID first
 * Function in parameters: void 
 * Function out parameter: NA
 * Version: 1 
 * Author: Neeraj Kumar Bansal
 * *****************************************************************************/
void registerStudent() {

	/*Local variable for counting through total rows */
    int counter;
    /*Local variable for student index */
    int studentIndex = -1;
	/*Local variable for course index */
	int courseCodeIndex = -1;
	/*Local variable to temporary store course code for verification*/
	char courseCode[8];

	printf("List of Student Ids\n");

	for(counter = 0; counter < numOfStudents; counter++){                    /*print all students with indexes*/
		printf("Index %d \t\t\t\t%d" , counter, students[counter]);
		printf("\n");
	}
    
	do{
		int studentId = getStudentId();                                /*take student id */
	    studentIndex = searchStudentId(studentId);                 /*calculate index of student ID*/
	}while (studentIndex == -1);

    printf("List of Available Course Id\n");

    for(counter = 0; counter < numOfCourses; counter++){                     /*print all courses with indexes*/
		printf("Index %d \t\t\t\t%s" , counter , courses[counter]);
		printf("\n");
	}

    do
	{	
	    printf("Enter the course id [3-Alphas][4-digits]: ");
	    scanf("%s", courseCode);                                       /*take course id */
		courseCodeIndex = searchCourseCodeId(courseCode);                  /*calculate index of course ID*/
	}while (courseCodeIndex == -1);
    
	setValueInRegistrationTable(studentIndex, courseCodeIndex, 1);  /*method called and value declared to 0 of value to set or status*/
}

/***************************************************************************** 
 * Function Name:  dropStudent
 * Purpose: Drop Student from the course
 * Function in parameters: void 
 * Function out parameter: NA
 * Version: 1 
 * Author: Neeraj Kumar Bansal
 * *****************************************************************************/
void dropStudent() {
    
    /*Local variable for student index */
    int studentIndex;
	/*Local variable for course index */
	int courseCodeIndex;
	/*Local variable for counting through total rows */
	int rowCounter;
    /*Local variable for taking index number from registration table */
	int number;

    /*Method called to print registration table*/
	printRegistrationTable();
	
	printf("Please select Index Number to drop student registration: ");
	scanf("%d", &number);                                                      /*take number from user*/
 
    for (rowCounter = 0; rowCounter < totalRows; rowCounter++) {
	    if(registrationTable[rowCounter][0] == number){                               /*execute only if condition is true*/
            studentIndex = registrationTable[rowCounter][1];                          /*get index number at position*/
	        courseCodeIndex = registrationTable[rowCounter][2];                       /*get index number at position*/
	    }/*end if*/
	}/*end for-statement*/
	
	if (studentIndex == -1 || courseCodeIndex == -1)
	{
		printf("Choose correct Index number...Try again\n");
		return;
	}

	setValueInRegistrationTable(studentIndex, courseCodeIndex, 0);     /*method called and value declared to 0 of value to set or status*/
	printf("\n");

    /*Method called to print registration table*/
	printRegistrationTable();

}

/***************************************************************************** 
 * Function Name:  menu
 * Purpose: Print menu and call method according to choice of user
 * Function in parameters: void 
 * Function out parameter: NA
 * Version: 1 
 * Author: Neeraj Kumar Bansal
 * *****************************************************************************/
void menu() {
    /*Local variable for input from user for the choice from menu options*/
	int userInput = 0;

	printf("Main Menu:\n");
	printf("\t[1] Register a student into a course.\n");
	printf("\t[2] Drop a student from a course.\n");
	printf("\t[3] Display Registration table.\n");
	printf("\t[4] Exit.\nEnter an option from the menu: ");

	scanf("%d", &userInput);                                 /*take value from user and store at address in variable*/

	switch (userInput) {                            /*run respective case according user input number*/
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
	default:
      printf("Choose valid number[1-4] only\n");
      break;
	}
	printf("\n");
	menu();
}

/***************************************************************************** 
 * Function Name:  searchStudentId
 * Purpose: Search student id Index from students array and return its index on which value will exist
 * Function in parameters: Integer 
 * Function out parameter: studentIndex
 * Version: 1 
 * Author: Neeraj Kumar Bansal
 * *****************************************************************************/
int searchStudentId(int idToSearch) {

    /*Local variable for countdown of index*/
	int counter;
	/*Local variable for course index and initialize it to -1 for failure */
	int studentIndex = -1;

	for (counter = 0; counter < numOfStudents; counter++) {
		if (students[counter] == idToSearch) {                            /*return success if both values are same*/
			studentIndex = counter;                                       /*set value of counter to index*/
			break;                                        /*break through function on success*/
		}
	}/*end for statement*/
	if (studentIndex == -1) {
		printf("No match with given student id.\n");
		return -1;                                            /*return failure and values will print again*/
	} else {
		return studentIndex;
	}  /*end if-else*/

	return studentIndex;                      /*return success and value pass to method from where it called*/
}

/***************************************************************************** 
 * Function Name:  deleteAllocatedMemory
 * Purpose: delete un-allcoated memory on exiting system
 * Function in parameters: void 
 * Function out parameter: NA
 * Version: 1 
 * Author: Neeraj Kumar Bansal
 * *****************************************************************************/
void deleteAllocatedMemory() {

    /*free memory from students integer array pointer*/
	free(students);
	/*free memory from courses string array pointer*/
	free(courses);
	/*free memory from students integer 2-dimension pointer to pointer array */
	free(registrationTable);
}

/***************************************************************************** 
 * Function Name:  searchCourseCodeId
 * Purpose: Search course Index from course array and return its index on which value will exist
 * Function in parameters: Integer 
 * Function out parameter: courseIndex
 * Version: 1 
 * Author: Neeraj Kumar Bansal
 * *****************************************************************************/
int searchCourseCodeId(char courseCodeToSearch[8]) {
	/*Local variable for countdown of index*/
	int counter;
	/*Local variable for course index and initialize it to -1 for failure*/
	int courseIndex = -1;

	for (counter = 0; counter < numOfCourses; counter++) {
		if (!strcmp(courseCodeToSearch, courses[counter])) {                   /*return 1 if both values are same*/
			courseIndex = counter;                                             /*set value of counter to index*/
			break;                                        /*break through function on success*/
		}
	}/*end for statement*/

	if (courseIndex == -1) {
		printf("No match with given course code.\n");
		return -1;                                          /*return failure and values will print again*/
	} else {
		return courseIndex;
	}/*end if-else*/

	return courseIndex;           /*return success and value pass to method from where it called*/
}

/***************************************************************************** 
 * Function Name:  setValueInRegistrationTable
 * Purpose: Set values in Registration Table to 1 or 0 with indexes of student IDs and courses IDs
 * Function in parameters: void 
 * Function out parameter: NA 
 * Version: 1 
 * Author: Neeraj Kumar Bansal
 * *****************************************************************************/
void setValueInRegistrationTable(int studentIndex, int courseCodeIndex, int valueToSet) {
	/*Local variable for countdown of index*/
    int counter;
	for (counter = 0; counter < totalRows; counter++) {
		if (registrationTable[counter][1] == studentIndex && registrationTable[counter][2] == courseCodeIndex) { /*proceed if index exist in array*/
		    if(registrationTable[counter][3] == 0){                                       /*Check if value is already dropped or not previously*/
				printf("Student id %d have dropped out from course %s.\n", students[studentIndex], courses[courseCodeIndex]);
				printf("Student id %d cannot register to course %s.\n", students[studentIndex], courses[courseCodeIndex]);
				printf("Registration Unsuccessful\n");
				break;
			}
			else if (registrationTable[counter][3] == -1 || registrationTable[counter][3] == 1)           /*set value to 1 or 0, if not initialized earlier*/
			{
				registrationTable[counter][3] = valueToSet;                    /*state value that passed in parameter on success of condition only*/
				if(valueToSet == 1){
					printf("Registration Successful\n");
				}
				else{
					printf("Drop Successful\n");
				}
			    break;                                                /*break through function on success*/
			}
			else{                                                        /*print if value already set to 1*/
			    printf("Already on record.\nStudent id %d cannot register to course %s.\n", students[studentIndex], courses[courseCodeIndex]);
				printf("Registration Unsuccessful\n");
				break;
			}/*end if-else*/
		}/*end if*/
	}/*end for statement*/
}

/***************************************************************************** 
 * Function Name:  printRegistrationTable
 * Purpose: Print Registration Table with Register or drop students in/from courses, will call from menu() method
 * Function in parameters: void 
 * Function out parameter: NA 
 * Version: 1 
 * Author: Neeraj Kumar Bansal
 * *****************************************************************************/
void printRegistrationTable() {

    /*Local variable for student Id Index initialize to 0*/
	int studentIndex = 0;
	/*Local variable for row Index displayed with every registered and dropped Id and course initialize to 0*/
	int rowIndex = 0;
    /*Local variable for counting of rows or first index*/
	int rowCounter;
    /*Local variable for counting of courses and initialize to 0*/
	int counter = 0;

	printf("\n\t\t\tRegistration Table\nRegistration Index\tStudent ID\tCourse ID\tRegistration Status\n\n"); /*Header line*/

		for (rowCounter = 0; rowCounter < totalRows; rowCounter++) {            /*count rows*/
		    if (counter != numOfCourses) {/*drop every number not equal to number of courses, basically after counter exceed numCourses*/
				registrationTable[rowCounter][0] = rowIndex;                       /*declare index from -1 to rowIndex value*/
		        if (registrationTable[rowCounter][3] == 1)                       /*print values with 1 at 2 dimension*/
				{
			    printf("  \t%d\t\t%d\t\t%s\t\tR\n", registrationTable[rowCounter][0], students[studentIndex], courses[counter]);
				rowIndex++;                                                       /*increment value at success of condition*/
				}
				else if (registrationTable[rowCounter][3] == 0)                   /*print values with 0 at 2 dimension*/
			    {
				printf("  \t%d\t\t%d\t\t%s\t\tD\n", registrationTable[rowCounter][0], students[studentIndex], courses[counter]);
				rowIndex++;                                                        /*increment value at success of condition*/
				}
				counter++;                                                         /*increment value at success of condition*/
		    }
			else{
				studentIndex++;                                                   /*increment value at success of condition*/
			    counter = 0;                                                      /*change value to 0 for starting again*/
		        rowCounter--;                                                     /*decrement value at success of condition*/
			}/*end if-else statement*/
		}/*end for statement*/	    
}

/***************************************************************************** 
 * Function Name:  initializeRegistrationTable
 * Purpose: Initialize Registration Table with -1 
 * Function in parameters: void 
 * Function out parameter: NA 
 * Version: 1 
 * Author: Neeraj Kumar Bansal
 * *****************************************************************************/
void initializeRegistrationTable() {
    /*Local variable for indexes*/
	int i;
	for (i = 0; i < totalRows; i++) {
		/*Local variable for indexes visible inside for-loop only*/
		int j;   
		for (j = 0; j < 4; j++) {
			registrationTable[i][j] = -1;             /*initializing table values to -1*/
		}/*end inner-for*/
	}/*end outer-for*/
}

/***************************************************************************** 
 * Function Name: main 
 * Purpose: Student Registration System 
 * Function in parameters: void 
 * Function out parameter: EXIT_SUCCESS 
 * Version: 1 
 * Author: Neeraj Kumar Bansal
 * *****************************************************************************/ 
int main() {

    /*Header print line*/
    printf("Welcome to Student Registration System.\n\n");

    /*addValue function callled which will take values for id's and courses and then menu() method called*/
	if (addValue()) {
		menu();
	}
	else {
		main();
	}


    /*free un-allocated memory from pointers*/
	deleteAllocatedMemory();

	return 1;

}/*exit main*/