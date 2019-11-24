/* -----------------------------------------------------------------------
 * Name: Maryum Shabazz
 * Date: 11/8/2019
 * Description: Unit Test File for CS 362 Fall 2019
 * unittest5: unittest5.c dominion.o rngs.o
 *      gcc -o unittest5 -g  unittest5.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//compare function 
int assertValues(int paramOne, int paramTwo)
{
    if(paramOne==paramTwo)
    {
        return 1;
    }
    
    else
    {
        return 0;
    }
}


int main() {
    int seed = 1000;
    int handPos=0, nextPlayer=1, choice1=0, choice2=0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, tribute};
    struct gameState G, testG;
       
    //Printing output to test Tribute 
    printf ("TESTING Card Test 5: TRIBUTE:\n\n");
    
    //initialize game 
    initializeGame(2,k,seed,&G);
    //copy the game state to a test case
    memcpy (&testG, &G, sizeof(struct gameState));
    int currentPlayer=whoseTurn(&testG);

    for(int i=0; i<testG.handCount[0]; i++)
    {
         testG.hand[0][i]=silver;
    }


    for(int i=0; i<testG.handCount[1]; i++)
    {
        testG.hand[1][i]=silver;
    }
    int coinsPre=testG.coins;
    tributeEffect(&testG,currentPlayer,1);

    // BUG TEST: checks to see if correct coin amount after  two treasure cards are revealed
    if(assertValues((2+coinsPre),testG.coins))
    {
        printf("PASS: Coins was incremented correctly for player 1 after playing tribute and 2 treasure cards revealed\n");
        printf("coins before tribute  %d\n ",coinsPre);
        printf("coins after tribute   %d\n\n",testG.coins );
    }
    else
    {
        printf("FAIL: Coins was not incremented correctly for player 1 after playing tribute and 2 treasure cards revealed\n");
        printf("coins before tribute  %d\n ",coinsPre);
        printf("coins after tribute   %d\n\n",testG.coins );
    }

    //copy the game state to a test case
    memcpy (&testG, &G, sizeof(struct gameState));
    currentPlayer=whoseTurn(&testG);

    for(int i=0; i<testG.handCount[0]; i++)
    {
         testG.hand[0][i]=silver;
    }


    for(int i=0; i<testG.handCount[1]; i++)
    {
        testG.hand[1][i]=mine;
    }
    int actionsPre=testG.numActions;

   tributeEffect(&testG,currentPlayer,1);

     // BUG TEST: checks to see if correct actions after 2 action cards revealed 
    if(assertValues((2+actionsPre),testG.numActions))
    {
        printf("PASS: Actionss was incremented  for player 1 correctly after playing tribute and 2 action cards revealed\n");
        printf("actions before tribute  %d\n ",actionsPre);
        printf("actions after tribute   %d\n\n",testG.numActions );
    }
    else
    {
        printf("FAIL: Action was not incremented for player 1 correctly after playing tribute and 2 action cards revealed\n");
        printf("actions before tribute  %d\n ",actionsPre);
        printf("actions after tribute   %d\n\n",testG.numActions);
    }

      //copy the game state to a test case
    memcpy (&testG, &G, sizeof(struct gameState));
    currentPlayer=whoseTurn(&testG);

    for(int i=0; i<testG.handCount[0]; i++)
    {
         testG.hand[0][i]=silver;
    }


    for(int i=0; i<testG.handCount[1]; i++)
    {
        testG.hand[1][i]=estate;
    }
    int player2Count=testG.handCount[1];

    tributeEffect(&testG,currentPlayer,1);

     // BUG TEST: checks to see if correct handCount after 2 victory cards revealed 
    if(assertValues((2+G.handCount[0]),testG.handCount[0]))
    {
        printf("PASS: Cards added to hand correctly after playing tribute and 2 victory cards revealed\n");
        printf("Hand count of player 1 before tribute  %d\n ",G.handCount[0]);
        printf("Hand count of player 1 after tribute   %d\n\n",testG.handCount[0] );
    }
    else
    {
        printf("FAIL: Cards added to hand incorrectly after playing tribute and 2 victory cards revealed\n");
        printf("Hand Count player 1 before tribute  %d\n ",G.handCount[0]);
        printf("Hand Count  player 1 after tribute   %d\n\n",testG.handCount[0]);
    }
   
   //TEST: checks to see if hand count for player 2 is changed
    if(assertValues(player2Count,testG.handCount[1]))
    {
        printf("PASS: Cards added to hand correctly after playing tribute and 2 victory cards revealed\n");
        printf("Hand count of player 2 before tribute  %d\n ",player2Count);
        printf("Hand count of player 2 after tribute   %d\n\n",testG.handCount[1] );
    }
    else
    {
        printf("FAIL: Cards added to hand incorrectly after playing tribute and 2 victory cards revealed\n");
        printf("Hand Count player 2 before tribute  %d\n ",player2Count);
        printf("Hand Count  player 2 after tribute   %d\n\n",testG.handCount[1]);
    }


    printf("END OF TEST TRIBUTE CARD\n");
    printf("*********************************************************************************************\n");
    return 0;
}

