/*
Name: Maryum Shabazz
Date: 11/14/2019
Description: Test for  Minion Card 
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>


//Values to compare functions
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

//checks what user has chose to do. 
void checkChoices(int cho1,int cho2)
{

	//prints choice chosen by user this turn 
	if(cho2==1)
	{
		printf("User has chosen to discard hand and redraw 4\n");
	}

	//prints choice chosen by user this turn
	if(cho1==1)
	{
		printf("Player has chosen to discard gain 2 coins\n");
	}


}


int main() {
    int seed = 1000;
    int testPassed=0;
    int failedTest=0;

	//seed random number generator
	srand(time(0));
    int handpos=0, choice1=0, choice2=0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, minion};
    struct gameState G, testG;
      
    
   
	
	//Printing output to test minion card Card
    printf ("TESTING Card Test 2: Minion:\n");
    

    //for loop used to repeat tests over and over for coverage with different variables each time. 
    for(int i=0; i<50; i++)
    {
        printf("TEST  SERIES RUN #%d\n",(i+1));

        int testFailed=0;
        int passTest=0;
    	int upper =4, lower =2;
    	//randomizes number of players (code referenced from https://www.geeksforgeeks.org/generating-random-number-range-c/)
    	int numPlayers=(rand() % (upper - lower + 1)) + lower; 

        int num1=choice1=(rand() % (5 - 2 + 1)) + 2;
	//changes choice1 to either 0 or 1
	if(num1==5 || num1==4)
   	{
       		choice1=1;
        	choice2=0;
	} 
	else
	{
		choice1=0;
		choice2=1;
	}
         
    	//initialize game 
   		initializeGame(numPlayers,k,seed,&G);
    	int currentPlayer=whoseTurn(&testG);

    	//copy the game state to a test case
    	memcpy (&testG, &G, sizeof(struct gameState));

    	int preMinionActions=testG.numActions;
    	//TEST:check to ensure number of action turns is increased after playing minion card. 

   		 minionPlay(choice1,choice2,handpos,currentPlayer,&testG);
   		 

   		 //prints what conditions have been selected for test. 
   		 checkChoices(choice1,choice2);
        
		 minionPlay(choice1,choice2,handpos,currentPlayer,&testG);

		    if(assertValues(testG.numActions,(preMinionActions+1)))
		    {
		        printf("PASS: number of actions has increased correctly\n\n");
                passTest++;

		    }
		    else
		    {
		        printf("FAIL:number of actions has not increased correctly\n\n");
		        printf("Actions before minion played %d\n",preMinionActions);
		        printf("Actions after  minion played %d\n",testG.numActions);
                testFailed++;
		    }

            //copy the original game state to a test case
            memcpy (&testG, &G, sizeof(struct gameState));
            int preCoins=testG.coins;

            //TEST:check to see if user chooses to take coins instead of draw cards, coins are increased.
            
            minionPlay(choice1,choice2,handpos,currentPlayer,&testG);

            if(assertValues(testG.coins,(preCoins+2))&& choice1==1)
            {
                printf("PASS:coins have increased correctly by 2\n");
                printf("coins before minion played are%d\n",preCoins);
                printf("coins after minion is played are %d\n\n",testG.coins);
                passTest++;
            }
            else if (choice1==1)
            {
		        printf("FAIL:coins have not increased correctly as expected by 2\n\n");
               	printf("coins before minion played are%d\n",preCoins);
               	printf("coins after minion is played are %d\n\n",testG.coins);
                testFailed++;
		
		
            }

            //TEST:check to see if first player chooses to draw cards cards new cards are drawn 

            //copy the original game state to a test case
            memcpy (&testG, &G, sizeof(struct gameState));
            minionPlay(choice1,choice2,handpos,currentPlayer,&testG);
            for(int i=0; i<testG.handCount[0]; i++)
            {
                if(assertValues(G.hand[0][i],testG.hand[0][i])&& choice2==1)
                {
                    printf("FAIL:First player has not received all new cards\n\n");
                    testFailed++;
                    i=4;
                }
                else if (assertValues(i,4))
                {
                    printf("PASS:First player has drawn all new cards\n\n");
                    passTest++;
                }

            }


            //copy the original game state to a test case
            memcpy (&testG, &G, sizeof(struct gameState));

            //TEST:checks to see of other player has 5 cards in their hand before minion played
            //then checks to see
            testG.handCount[1]=(rand() % (5 - 2 + 1)) + 2;
            printf("Hand count for player two is %d\n",testG.handCount[1]);
            
            minionPlay(choice1,choice2,handpos,currentPlayer,&testG);
            if(testG.handCount[1]>4)
            {
                printf("second player has more then 4 cards in hand before minion played\n\n");
                for(int i=0; i<4; i++)
                {
                    if(assertValues(G.hand[1][i],testG.hand[1][i]))
                    {
                        printf("FAIL:Second player has not received new cards\n\n");
                        testFailed++;
                        i=4;
                    }
                    else if(assertValues(i,4))
                    {
                        printf("PASS:second player has drawn new cards\n\n");
                        passTest++;
                    }
                }
            }
            else
            {
                printf("PASS:second player does not have more than 4 cards in their hand before minion is played\n");
                printf("second payer does not have to discard hand and draw 4 new cards\n\n");
                passTest++;
            }
   

         if(passTest==0 && testFailed==0)
        {
            printf("Insufficient conditions for any test to be triggered \n");
        }

       testPassed=testPassed+passTest;
       failedTest=testFailed+failedTest;

    }


//prints number of test failed and number of test passed.
printf("Total test passed: %d\n",testPassed);
printf("Total test failed: %d\n",failedTest);
printf("END TEST MINION\n");
printf("******************************************************************************************************\n");
return 0;   

}
   /*

    

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
}*/


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
