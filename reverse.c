/*Name- Neeraj Kumar Bansal
Course- CST8234_011
Assessment- Lab1
*/
# include<stdio.h>       //header file for input and output

int main()
{
    int digit, remainder, reverse=0;        //variable declaration

    printf("Enter an integer: ");
    scanf("%d", &digit);                  //takes input and stores in digit named variable

    /*loop executes until digit value is non-zero*/
    while (digit != 0) 
    {
        remainder = digit % 10;                  //value divided by 10 and remainder stored in variable
        reverse = reverse * 10 + remainder;      //calculating reverse of number 
        digit /= 10;  
    }//loop exit

    printf("The reverse number is %d\n", reverse);

    return 0;                //returns with 0
}//end main