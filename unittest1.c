/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
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
    int handpos=0, choice1=0, choice2=0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
        
    initializeGame(2,k,seed,&G);
    //copy the game state to a test case
    memcpy (&testG, &G, sizeof(struct gameState));

    /*You may trash a Treasure from your hand . Gain a
    treasure to your hand costing up to 3 more than it*/

    //Printing output to test mine card Card
    printf ("TESTING Card Test 1: Mine:\n");
    int currentPlayer=whoseTurn(&testG);
    int buyTurns=testG.numBuys;
    int handCountBefore=testG.handCount[0];
    minePlay(choice1,choice2,handpos,currentPlayer,&testG);

    //cardEffect(mine,choice1,choice2,choice3,&testG, handPos,&bonus);
   //testing to see if number of buys is discounted incorrectly. 
    if(assertValues(buyTurns,testG.numBuys))
    {
        printf("PASS:Correct Number of buys after mine card played.\n");
    }
    else
    {
        
        printf("FAIL:incorrect number of buys after mine card played\n");
	printf("Buys before mine card %d\n", buyTurns);
	printf("Buys After mine card %d\n\n",testG.numBuys);
    }

    //testing to see if card discarded was removed from hand.
    if(assertValues(testG.handCount[0],handCountBefore))
    {
        printf("PASS:Card removed from hand\n\n");
    }
    else if(testG.handCount[0]!=handCountBefore)
    {
        printf("FAIL:Failed to remove card from hand\n\n");
    }
    
    //copy over state of game to new test case    
    memcpy(&testG,&G,sizeof(struct gameState));

    //ensure first card in currentPlayer hand is 0;
    testG.hand[0][0]=silver;
    choice1=testG.hand[0][0];

    int numGold=0;

    for(int i=0; i<testG.handCount[0]; i++)
    {
        if(testG.hand[0][i]==gold)
        {
            numGold++;
        }
    }
    currentPlayer=whoseTurn(&testG);
    choice2=6;
    minePlay(choice1,choice2,handpos,currentPlayer,&testG);

    int numGoldBefore=numGold;

    numGold=0;

    for(int i=0; i<testG.handCount[0]; i++)
    {
    	if(testG.hand[0][i]==gold)
        {
       	    numGold++;
        }
    }
    //checks to see if mine works by adding another a gold to hand in place of silver 
    if(assertValues(numGold,(numGoldBefore+1)))
    {
    	printf("PASS:gold has been added in place of siver \n\n");
    }
    else if(numGold==numGoldBefore)
    {
        printf("FAIL:gold has not been added in place of silver \n\n");
    }

    //checks to see if treasure to be trashed has been added to discard pile
    int preMineSilver=0, postMineSilver=0;

    //counts silver in hand post mine card
    for(int i=0; i<testG.handCount[0]; i++)
    {
        if(testG.discard[0][i]==silver)
        {
            postMineSilver++;
        }
    }
    
    //counts silver in hand before mine card
    for(int i=0; i<G.handCount[0]; i++)
    {
        if(G.discard[0][i]==silver)
        {
            preMineSilver++;
        }
    }

    if(assertValues(preMineSilver,postMineSilver))
    {
        printf("PASS: silver has not been added to discard pile as expected\n\n");
    }
    else
    {
        printf("FAIL: Silver has been added to discard pile as not expected\n\n");
    }
    //copy the game state to test case
    memcpy(&testG,&G,sizeof(struct gameState));
    choice2=30;
    //checks to see if -1 is returned when choice 2 is a more than treasure_map 
    int m=minePlay(choice1,choice2,handpos,currentPlayer,&testG);
    if(assertValues(m,-1))    
    {
       printf("PASS: -1 returned as expected when choice2 is more than treasure_map\n\n");
    }
    else
    {
        printf("FAIL: -1 not returned as expected when choice2 more than treasure_map\n\n");
    }

    //checks to see if -1 is returned when choice 2 is less than curse
    memcpy(&testG,&G,sizeof(struct gameState));
    choice2=-3;
    m=minePlay(choice1,choice2,handpos,currentPlayer,&testG);
    if(assertValues(m,-1))
    {
        printf("PASS: -1 returned as expected when choice2 <curse 2\n\n");
    }
    else
    {
        printf("FAIL:-1 not returned as expected when choice2 is less than curse\n\n");
    }
	
    //check to see if card to be added is gold as expected. 
    memcpy(&testG,&G,sizeof(struct gameState));
    int numSilverBefore=0;
    int numSilver=0;
    testG.hand[0][0]=copper;
    choice1=copper;
    
    for(int i=0; i<testG.handCount[0]; i++)
    {
       if(testG.hand[0][i]==silver)
       {
           numSilverBefore++;
       }
    }
    choice2=3;
    minePlay(choice1,choice2,handpos,currentPlayer,&testG);

    for(int i=0; i<testG.handCount[0];i++)
    {
        if(testG.hand[0][i]==gold)
        {
            numSilver++;
        }
    }

    if(assertValues(numSilver,(numSilverBefore+1)))
    {
       printf("PASS:number of silver has increased after attempting to add silver\n\n");
    }
    else
    {
       printf("FAIL: number of silver has not increased after attempting to add silver\n\n");
    }
    printf("END MINE CARD TEST\n");
    printf("***************************************************************\n");
    return 0;
}

/*int minePlay(int choice1, int choice2,int handPos, int currentPlayer, struct gameState *state)
{
   int j;
   j = state->hand[currentPlayer][choice1];  //store card we will trash
state->numBuys++;
        if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
        {
            return -1;
        }

        if (choice2 > treasure_map || choice2 < curse)
        {
            return -1;
        }

        if ( (getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2) )
        {
            return -1;
        }

        gainCard(choice2, state, 2, currentPlayer);

        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);
    
    int i;
        //discard trashed card
        for (i = 0; i < state->handCount[currentPlayer]; i++)
        {
            if (state->hand[currentPlayer][i] == j)
            {
                discardCard(i, currentPlayer, state, 0);
                break;
            }
        }
 return 0;
}*/
