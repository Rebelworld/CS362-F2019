/* -----------------------------------------------------------------------
 * Name: Maryum Shabazz
 * Date: 11/8/2019
 * Description: Unit Test File for CS 362 Fall 2019
 * unittest1: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
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
               , remodel, smithy, village, baron, minion};
    struct gameState G, testG;
      
    //initialize game 
    initializeGame(2,k,seed,&G);
    //copy the game state to a test case
    memcpy (&testG, &G, sizeof(struct gameState));

    int currentPlayer=whoseTurn(&testG);


    //Printing output to test mine card Card
    printf ("TESTING Card Test 2: Minion:\n");

    //TEST:check to ensure number of action turns is increased after playing minion card. 

    minionPlay(choice1,choice2,handpos,currentPlayer,&testG);

    if(assertValues(testG.numActions,(G.numActions+1)))
    {
        printf("PASS: number of actions has increased correctly\n\n");
    }
    else
    {
        printf("FAIL:number of actions has not increased correctly\n\n");
    }

    //check to see if user can draw3 cards or 4 (expected is 4).

    //copy the original game state to a test case
    memcpy (&testG, &G, sizeof(struct gameState));

    //TEST:check to see if user chooses to take coins instead of draw cards, coins are increased.
    choice1=1;
    minionPlay(choice1,choice2,handpos,currentPlayer,&testG);
    if(assertValues(testG.coins,(G.coins+2)))
    {
        printf("PASS:coins have increased correctly by 2\n\n");
    }
    else
    {
        printf("FAIL:coins have not increased correctly as expected by 2\n\n");
    }
    

    //TEST:check to see if player chooses to draw cards cards for other player changes (ie new cards drawn)

    //copy the original game state to a test case
    memcpy (&testG, &G, sizeof(struct gameState));
    choice1=0;
    choice2=1;
    minionPlay(choice1,choice2,handpos,currentPlayer,&testG);
     for(int i=0; i<4; i++)
        {
            if(assertValues(G.hand[0][i],testG.hand[0][i]))
            {
                printf("FAIL:First player has not received all new cards\n\n");
                i=4;
            }
            else if (assertValues(i,4))
            {
                printf("PASS:First player has drawn all new cards\n\n");
            }
        }


    //copy the original game state to a test case
    memcpy (&testG, &G, sizeof(struct gameState));

    //TEST:checks to see of other player has 5 cards in their hand before minion played
    //then checks to see
    testG.handCount[1]=4;
    minionPlay(choice1,choice2,handpos,currentPlayer,&testG);
    if(testG.handCount[1]>4)
    {
        printf("second player has more then 4 cards in hand before minion played\n\n");
        for(int i=0; i<4; i++)
        {
            if(assertValues(G.hand[1][i],testG.hand[1][i]))
            {
                printf("FAIL:Second player has not received new cards\n\n");
                i=4;
            }
            else if(assertValues(i,4))
            {
                printf("PASS:second player has drawn new cards\n\n");
            }
        }
    }
    else
    {
        printf("PASS:second player does not have more than 4 cards in their hand before minion is played\n");
        printf("second payer does not have to discard hand and draw 4 new cards\n\n");
    }

    //copy the orginal game state to a test case
    memcpy(&testG,&G,sizeof(struct gameState));
    
    // checks to see if other player has 5 cards in their hand and if so checks to see if
    //new cards drawn
    testG.handCount[1]=5;  
    G.handCount[1]=5;
    printf("hand count before minionPlay is %d\n", testG.handCount[1]);
    //draws 5 cards for second player
    for(int i=0; i<5; i++)
    {
        drawCard(1,&testG);
        G.hand[1][i]=testG.hand[1][i];
    }
    choice2=1;
    minionPlay(choice1,choice2,handpos,currentPlayer,&testG);
   
	for(int i=0; i<testG.handCount[1];i++)
        {
            if(assertValues(testG.hand[1][i],G.hand[1][i+1]))
            {
                printf("FAIL:other player has not drawn new cards\n\n");
                i=testG.handCount[1];
            }
            else if(assertValues(i,((testG.handCount[1])-1)))
            {
                printf("PASS:other player has drawn all new cards\n\n");
            }
        }

    printf("END TEST MINION\n");
    printf("******************************************************************************************************\n");
    return 0;
}


/*int minionPlay(int choice1, int choice2,int handPos, int currentPlayer, struct gameState *state)
{
        int i,j;
      

        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);

        if (choice1)
        {
            state->coins = state->coins + 2;
        }
        else if (choice2)       //discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
        {
            //discard hand
            while(numHandCards(state) > 0)
            {
                discardCard(handPos, currentPlayer, state, 0);
            }
            
            //draw 3
            for (i = 0; i < 3; i++)
            {
                drawCard(currentPlayer, state);
            }

            //other players discard hand and redraw if hand size > 4
            for (i = 0; i < state->numPlayers; i++)
            {
                if (i != currentPlayer)
                {
                    if ( state->handCount[i] > 4 )
                    {
                        //discard hand
                        while( state->handCount[i] > 0 )
                        {
                            discardCard(handPos, i, state, 0);
                        }

                        //draw 4
                        for (j = 0; j < 4; j++)
                        {
                            drawCard(i, state);
                        }
                    }
                }
            }

        }
        return 0;
 
}*/
