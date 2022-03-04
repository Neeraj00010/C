/*Name- Neeraj Kumar Bansal
Course- CST8234_011
Assessment- Lab1
*/
# include<stdio.h>       //header file for input and output
#include <math.h>        //header file for math functions

int main()
{
    int number, decimal_num=0, rem;    //variable declaration

    printf("Enter a binary number: ");
    scanf("%d", &number);               //takes input and stores  in number named variable

    /*loop runs until 2nd condition becomes false*/
    for (int i = 0; number != 0; ++i)  
    {  
        rem = number % 10;     //calculating remainder by dividing the digit with 10
        number = number / 10;  
        decimal_num = decimal_num + (rem) * (pow(2, i));      //calculating decimal number using power function of math.h header class
    }//loop exits 

    printf("The decimal equivalent is %d\n", decimal_num);
    
    return 0;            //returns with 0
}//end main