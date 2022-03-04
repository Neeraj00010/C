/*Name- Neeraj Kumar Bansal
Course- CST8234_011
Assessment- Lab1
*/
# include<stdio.h>       //header file for input and output

int main()
{
    int digit;     //variable for taking integer input

    int digitLen=0;   //variable to count length of digit

    printf("Enter an integer: ");
    scanf("%d", &digit);         //take input from user

    /*loop executes if digit value is not equals to 0*/
    while(digit!=0)  
   {  
       digit=digit/10;     //divide value by 10 and count will increase by 1 on next step
       digitLen++;  
   }//exit while loop  

    printf("Number of digits is %d\n",1 digitLen);       //print statement

    return 0;              //returns with 0
}//end main