/*
 * Title: Lab Assessment #1- “Dice Game Implementation”
 * Course: CST8234 C Language
 * @Author: Bansal Neeraj Kumar ,Ding Yi, Dutra Emilio
 * Lab Section: Assigment 1
 * Professor: Surbhi Bahri
 * Due date: 03/13/22
 * Submission date: 03/13/22
 */

/*
 * Dice Game
 *
 * Status:
 * Requirement #1: complete
 * Requirement #2: complete
 * Requirement #3: complete
 *
 */

#include <stdio.h>
#include <stdlib.h> /* define for EXIT_SUCCESS */
#include "DiceHeader.h"


/*****************************************************************************
Function Name: main
Purpose: entry
Function in parameters: void
Function out parameter: EXIT_SUCCESS
Version: 1
Author: Neeraj Kumar ,Ding Yi, Dutra Emilio
*****************************************************************************/
int main()
{
    int totalWins = 0;
    int totalLosses = 0;

    int wallet = 50;

    /* firstly ask */
    int doPlay = askYorN("Please enter [y or Y] to play Dice or [n or N] to exit: ");
    if (doPlay == 0)
    {
        return EXIT_SUCCESS;
    }

    /* game loop */
    while (1)
    {
        /* Ask the user if (s)he wants to continue playing another game, keeping track of the
            numbers of Games lost and won */
        int betMoney=0;
        int result;
        int doBet;
        int doPlay;

        printf("Let's begin\n");
        doBet = askYorN("Would you like to bet? [y/n] ");
        if (doBet)
        {
            betMoney = askForBetting(wallet);
        }

        /* Call the function playGame() */
        result = playGame();

        /* if player choose to quit */
        if (result==TIE)
            break;
        
        /* change the wallet by game result */
        if (result==WON)
        {
            wallet+=3*betMoney;
            totalWins++;
        }
        else
        {
            wallet-=betMoney;
            totalLosses++;
        }

        /* Give the user an appropriate message depending on the number of wins or losses (s)he
            had while playing */
        if (wallet == 0)
        {
            int doStartOver = askYorN("You have no more funds. Start-over [y/n]? ");
            if (doStartOver)
            {
                wallet = 50;
                printf("Game have reset, game on.\n");
                continue;
            }
            break;
        }

        /* ask user whether want to play again */
        doPlay = askYorN("Play another game? [y/n] ");
        if (doPlay)
        {
            continue;
        }

        break;
    }

    /* When the user decides to finish playing, display the number of wins and losses he/she
        had. */
    printf("Thank you for playing!\n");
    printf("Games Won : %d\n", totalWins);
    printf("Games Lost: %d\n", totalLosses);
    printf("Money: %d\n", wallet);

    /* Return with a value of EXIT_SUCCESS */
    return EXIT_SUCCESS;
}
