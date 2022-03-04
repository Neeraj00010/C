/*Name- Neeraj Kumar Bansal
Course- CST8234_011
Assessment- Lab1
*/
# include<stdio.h>             //header file for input and output

void main ()
{
	int i, times=100;        //variable declaration
	
	/*loop starts with i=1 and continue until it turns 100*/
	for(i = 1; i <= times; i++){
		
		if((i % 3 == 0) && (i % 5 == 0)){      //checks if the variable value is multiple of 3 and 5
			printf("%d ", i);
			printf("I'm a multiple of 3 && 5!!!\n");
		}
		else if(i % 5 == 0){              //check if the variable is multiple of 5
			printf("%d ", i);
			printf("I'm a multiple of 5!\n");
		}
		else if(i % 3 == 0){             //check if the variable is multiple of 3
			printf("%d ", i);
			printf("I'm a multiple of 3!\n");
		}
		else{                           //if above conditions are false, else will executes
			printf("%d\n",i);
		}
	}//exit for loop
}//end main