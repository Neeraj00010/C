#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************************
Function Name: inputALine()
Purpose: get a string of char of dynamic array by stdin
            while getting, end by a '\n' and this '\n' is not contained by the returned string
            result a string end of '\0' .
        caller should release the returned string.
Function in parameters: void
Function out parameter: char *
Version: 1
Author: Neeraj Kumar ,Ding Yi, Dutra Emilio
*****************************************************************************/
char *inputALine(void)
{
    int size = 0;
    char *s;
    int c;
    s=malloc(size);

    /* get char until EOF */
    while ((c = getchar()) != EOF)
    {
        /* if get a '\n', break the loop and this '\n' is not received. */
        if (c == '\n')
            break;

        /* increase the size and reallocate memory */
        size++;
        s = realloc(s, size);
        s[size - 1] = c;
    }

    /* add the tail '\0' */
    size++;
    s = realloc(s, size);
    s[size - 1] = '\0';
    return s;
}


/*****************************************************************************
Function Name: askYorN()
Purpose: print a message and let user input a 'Y' 'y' or 'N' 'n'
        otherwise repeat until input validly.
Function in parameters: const char msg[]
Function out parameter: int, 1 for 'Y' 'y' , 0 for 'N' 'n'
Version: 1
Author: Neeraj Kumar ,Ding Yi, Dutra Emilio
*****************************************************************************/
int askYorN(const char msg[])
{
    char *s;
    while (1)
    {
        int len;
        printf("%s",msg);

        /* get a string from stdin */
        s = inputALine();
        len = strlen(s);

        /* if input a single character */
        if (len == 1)
        {
            char c = s[0];
            if (c == 'Y' || c == 'y')
            {
                free(s);
                return 1;
            }
            if (c == 'N' || c == 'n')
            {
                free(s);
                return 0;
            }

            printf("Invalid option\n");
            continue;
        }

        /* if input multi-characters */
        printf("Invalid input\n");
        continue;
    }
    free(s);
}

/*****************************************************************************
Function Name: strToInt()
Purpose: convert a string to integer
            if the pointer "ok" is specified, the ok will be 1 for successfully or 0 for failure.
            returns the result integer
Function in parameters: const char s[], int *ok
Function out parameter: int
Version: 1
Author: Neeraj Kumar ,Ding Yi, Dutra Emilio
*****************************************************************************/
int strToInt(const char s[], int *ok)
{
    int len = strlen(s);
    int ret = 0;
    int i;
    for (i = 0; i<len;++i)
    {
        if (s[i] < '0' || s[i] > '9')
        {
            if (ok)
                *ok = 0;
            return -1;
        }
        ret = ret * 10 + (s[i] - '0');
    }
    if (ok)
        *ok = 1;
    return ret;
}

/*****************************************************************************
Function Name: askForBetting()
Purpose: ask user to input the betting money.
            argument "wallet" must be valid after calling this function.
            returns the betting money
Function in parameters: int wallet
Function out parameter: int
Version: 1
Author: Neeraj Kumar ,Ding Yi, Dutra Emilio
*****************************************************************************/
int askForBetting(int wallet)
{
    char *s;
    int ok;
    int amount;
    while (1)
    {
        int maxAmount=wallet/5;
        printf("You have $%d, minimum bet is $5, you can make %d total bet(s) ", wallet, maxAmount);

        s = inputALine();
        amount=strToInt(s,&ok);
        if (!ok)
        {
            printf("Invalid bet\n");
            continue;
        }

        if (amount<1 || amount>maxAmount)
        {
            printf("Please enter only number between 1-%d\n",maxAmount);
            continue;
        }

        printf("You bet $%d\n", amount*5);
        
        break;
    }
    free(s);
    return amount*5;
}