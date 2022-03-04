/*Name- Neeraj Kumar Bansal
Student id #041000185
Course- CST8234_011
Assessment- Lab2
Professor - Surbhi Bahri
*/
/*header file for input and output */
#include <stdio.h>  
/*header file for standard C programming library */        
#include <stdlib.h>   
/*header file for string */
#include <string.h>         
/*header file for character */
#include <ctype.h>          

/*defines maximum length of message and act as a constant */
#define MAX_MESSAGE 80        

/*main function*/
int main()                 
{
/*string array with MAX_LENGTH as a parameter*/
char str[MAX_MESSAGE]; 
/*variable declaration */
int key = -1, i;      

/* Prompt to take message to encrypt */
printf("Enter message to Encrypt:\n");
scanf("%[^\n]*c", str);

/* Checks if message contains more than 80 characters and ask for message again if so*/
while (strlen(str) > MAX_MESSAGE || strlen(str) == 0)
{
    printf("Error - Message cannot be empty or more than 80 characters long, try again\n");
    printf("Enter message to Encrypt:\n");
    scanf("%[^\n]*c", str);
}

/* Prompt to take key for rotation 0-26 */
printf("Enter rotation key:\n");
scanf("%d", &key);

/* checks value if it is between 0 and 26 otherwise print error message and ask for value again*/
while (key < 0 || key > 26)
{
    printf("Error - key must be in range 0 and 26. Try again.\n");
    printf("Enter rotation key:\n");
    scanf("%d", &key); 
}

printf("\nEncrypting message (key = %i): %s\n", key, str);

/* Loops through the message until last index reached */
for (i = 0; i < strlen(str); i++)
    {
        /* Encrypts message if character is lowercase and between a and z */
        if (islower(i) == 0 && str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = ((str[i] + key) - 'a') % 26 + 'a';
        }
        /* Encrypts message if character is uppercase and between A and Z */
        else if (isalpha(i) == 0 && str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = ((str[i] + key) - 'A') % 26 + 'A';
        }
    }

printf("\n%s\n", str);
exit(EXIT_SUCCESS);
}