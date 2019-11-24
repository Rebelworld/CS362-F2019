/* -----------------------------------------------------------------------
 * Name: Maryum Shabazz
 * Date: 11/8/2019
 * Description: Unit Test File for CS 362 Fall 2019
 * unittest1: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


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
    int handPos=0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, ambassador};
    struct gameState G, testG;
       
    //Printing output to test Ambassador 
    printf ("TESTING Card Test 4: AMBASSADOR:\n\n");
    
    //initialize game 
    initializeGame(2,k,seed,&G);
    //copy the game state to a test case
    memcpy (&testG, &G, sizeof(struct gameState));
    int currentPlayer=whoseTurn(&testG);

    for(int i=0; i<testG.handCount[0]; i++)
    {
         testG.hand[0][i]=curse;
    }


    for(int i=0; i<testG.handCount[1]; i++)
    {
        testG.hand[1][i]=estate;
    }
    testG.supplyCount[estate]=3;
    testG.supplyCount[curse]=3;

    //Test: attempt to enter invalid number for cards to be returned to supply pile
    ambassadorEffect(1,3,handPos,&testG,currentPlayer);

    if(assertValues(testG.handCount[0],G.handCount[0]))
    {
	if(assertValues(G.handCount[1],testG.handCount[1]))
	{
            printf("PASS: hand count for both players remain unchanged after user attempted to return 3 cards to supply \n\n");
    	}
    }
    else
    {
        printf("FAIL: Hand count changed for a player after player 1 attempted to returned 3 cards to supply pile\n\n");
    }

    if(assertValues(testG.supplyCount[curse],3))
    {
        printf("PASS: Supply count of card player 1 tried to return to pile unchanged after user tried to return invalid number\n\n");
    
    }
    else
    {
        printf("FAIL: supply count changed after user tried to add invalid number of cards to supply \n\n");
    }

    ambassadorEffect(1,2,handPos,&testG,currentPlayer);

    testG.supplyCount[curse]=3;
    //for loop counts number of curses in other players hands
    int numCurses=0;
    for(int i=0; i<testG.handCount[1]; i++)
    {
        if(testG.hand[1][i]==curse)
        {
            numCurses++;
        }
    }

    //BUG TEST will find supply count increased correctly
    if(assertValues(testG.supplyCount[curse],5))
    {
        printf("PASS: supply count correct after playing ambassador \n\n");
    }
    else
    {
        printf("FAIL:incorrect number of cards has been added to supply pile after playing Ambassador\n\n");
    }

   
    
    //initialize game 
    initializeGame(3,k,seed,&G);
    //copy the game state to a test case
    memcpy (&testG, &G, sizeof(struct gameState));
    currentPlayer=whoseTurn(&testG);
 
    ambassadorEffect(1,3,handPos,&testG,currentPlayer);
    //fills player 0's hand with curses, player 1's hands with estate, player 2's hands with copper. 
    for(int i=0; i<testG.handCount[0]; i++)
    {
         testG.hand[0][i]=curse;
         testG.hand[1][i]=estate;
         testG.hand[2][i]=copper;
    }
    //sets supply counts of estates and curses
    testG.supplyCount[estate]=3;
    testG.supplyCount[curse]=3;

    //checks to see if curses have been added to every other player hand.
    int playerTwoCards=0, playerThreeCards=0;
    for(int i=0; i<testG.handCount[1]; i++)
    {
        if(testG.hand[1][i]==curse)
        playerTwoCards++;
    }
    
    for(int i=0; i<testG.handCount[1]; i++)
    {
        if(testG.hand[2][i]==curse)
        playerThreeCards++;
    }

    //BUG TEST to see if extra card was added to all players. 
    if(assertValues(playerThreeCards,1)&& assertValues(playerTwoCards,1))
    {
        printf("PASS: Card to be returned to supply also one was given to each other player\n\n");
    }
    else
    {
        printf("FAIL: Card to be returned to supply not given to other player(s)\n");
    }



    printf("END OF TEST AMBASSADOR CARD\n");
    printf("***************************************************************************************************\n");
    return 0;
}

