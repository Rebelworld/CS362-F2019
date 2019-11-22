/*
Name: Maryum Shabazz
Date: 11/14/2019
Description: Test for Tribute card
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




int main() {
    int seed = 1000;
    int testPassed=0;
    int failedTest=0;

	//seed random number generator
	srand(time(0));
    int handPos=0, choice1=0, choice2=0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, tribute};
    struct gameState G, testG;
      
    
   
	
	//Printing output to test tribute card Card
    printf ("TESTING Card Test 3: TRIBUTE:\n");
    

    //for loop used to repeat tests over and over for coverage with different variables each time. 
    for(int i=0; i<100; i++)
    {

        printf("TEST SERIES RUN #%d\n",(i+1));
        int testFailed=0;
        int passTest=0;

    	int upper =4, lower =2;
    	//randomizes number of players (code referenced from https://www.geeksforgeeks.org/generating-random-number-range-c/)
    	int numPlayers=(rand() % (upper - lower + 1)) + lower; 

                

             
    	//initialize game 
   		initializeGame(numPlayers,k,seed,&G);
    	int currentPlayer=whoseTurn(&testG);
        int nextPlayer=currentPlayer+1;

    	//copy the game state to a test case
    	memcpy (&testG, &G, sizeof(struct gameState));
	//set hand count of player 1
        testG.handCount[1]=5;
        //15 cards via enums nused to fill decks with randomcards of players
       

        for(int i=0; i<testG.handCount[1]; i++)
        {
            
            
                //used to randomize card added to deck of player1
                int num2=(rand() % (6 - 0 + 1)) + 0;
                if(num2==0)
                {
                    testG.hand[1][i]=copper;
                }
                else if(num2==1)
                {
                    testG.hand[1][i]=silver;
                }
                else if(num2==2)
                {
                    testG.hand[1][i]=gold;
                }
                else if(num2==3)
                {
                    testG.hand[1][i]=baron;
                }
                else if(num2==4)
                {
                    testG.hand[1][i]=mine;
                }
                else if(num2==5)
                {
                    testG.hand[1][i]=estate;
                }
                else if(num2==6)
                {
                    testG.hand[1][i]=duchy;
                }

                //removes card from supply count 
                testG.supplyCount[num2]--;
            
        }

        //prints number of card revealed for user to see, used for writing test
        /* for(int i=0; i<3; i++)
         {
            printf("Card in second player's hand to be revealed is  number %d\n",testG.hand[1][i]);
         }*/
      

        //counts actions before tribute card played.
        int actionsPre=testG.numActions;

        //counts hand count of player 2
        int player2Count=testG.handCount[1];

        //counts hand of player 1
	    int player1Count=testG.handCount[0];    

        //runs test if both are a treasure card 
        if((testG.hand[1][0]<=6 && testG.hand[1][0]>=4)||(testG.hand[1][1]<=6 && testG.hand[1][1]>=4))
        {
            int coinsPre=testG.coins;
            
            tributeEffect(&testG,currentPlayer,nextPlayer);
            // BUG TEST: checks to see if correct coin amount after  two treasure cards are revealed
            if(assertValues((2+coinsPre),testG.coins) )
            {
                printf("PASS: Coins was incremented correctly for player 1 after playing tribute and 2 treasure cards revealed\n");
                printf("coins before tribute  %d\n ",coinsPre);
                printf("coins after tribute   %d\n\n",testG.coins );
                passTest++;
            }
            else    
            {
                printf("FAIL: Coins was not incremented correctly for player 1 after playing tribute and 2 treasure cards revealed\n");
                printf("coins before tribute  %d\n ",coinsPre);
                printf("coins after tribute   %d\n\n",testG.coins );
                testFailed++;
            }

	   }    		
    

        if((testG.hand[1][0]==11 && testG.hand[1][1]==15)||(testG.hand[1][0]==15 && testG.hand[1][1]==11))
        {

            tributeEffect(&testG,currentPlayer,nextPlayer);
             // BUG TEST: checks to see if correct actions after 2 action cards revealed 
            if(assertValues((2+actionsPre),testG.numActions))
            {
                printf("PASS: Actions was incremented  for player 1 correctly after playing tribute and 2 action cards revealed\n");
                printf("actions before tribute  %d\n ",actionsPre);
                printf("actions after tribute   %d\n\n",testG.numActions );
                passTest++;
            }
            else
            {
                printf("FAIL: Action was not incremented for player 1 correctly after playing tribute and 2 action cards revealed\n");
                printf("actions before tribute  %d\n ",actionsPre);
                printf("actions after tribute   %d\n\n",testG.numActions);
                testFailed++;
            }
        }


        //TEST to see if number of cards is incremented correctly when two victory cards revealed
        if((testG.hand[1][0]==1 && testG.hand[1][1]==2)||(testG.hand[1][0]==2 && testG.hand[1][1]==1))
        {
            
            tributeEffect(&testG,currentPlayer,nextPlayer);
            // BUG TEST: checks to see if correct handCount after 2 victory cards revealed 
            if(assertValues((2+player1Count),testG.handCount[0]))
            {
                printf("PASS: Cards added to hand correctly after playing tribute and 2 victory cards revealed\n");
                printf("Hand count of player 1 before tribute  %d\n ",player1Count);
                printf("Hand count of player 1 after tribute   %d\n\n",testG.handCount[0] );
                passTest++;
            }
            else
            {
                printf("FAIL: Cards added to hand incorrectly after playing tribute and 2 victory cards revealed\n");
                printf("Hand Count player 1 before tribute  %d\n ",player1Count);
                printf("Hand Count  player 1 after tribute   %d\n\n",testG.handCount[0]);
                testFailed++;
            }
           
           //TEST: checks to see if hand count for player 2 is changed
            if(assertValues(player2Count,testG.handCount[1]))
            {
                printf("PASS: Cards added to correct hand after playing tribute and 2 victory cards revealed\n");
                printf("Hand count of player 2 before tribute  %d\n ",player2Count);
                printf("Hand count of player 2 after tribute   %d\n\n",testG.handCount[1] );
                passTest++;
            }
            else
            {
                printf("FAIL: Cards added to hand incorrectly after playing tribute and 2 victory cards revealed\n");
                printf("Hand Count player 2 before tribute  %d\n ",player2Count);
                printf("Hand Count  player 2 after tribute   %d\n\n",testG.handCount[1]);
                testFailed++;
            }
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
printf("END TEST TRIBUTE\n");
printf("******************************************************************************************************\n");
return 0;   

}

/*int tributePlay(int choice1, int choice2,int nextPlayer, int handPos, int currentPlayer, struct gameState *state, int tributeRevealedCards[])
{
    int i;
   if ((state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1) {
            if (state->deckCount[nextPlayer] > 0) {
                tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
                state->deckCount[nextPlayer]--;
            }
            else if (state->discardCount[nextPlayer] > 0) {
                tributeRevealedCards[0] = state->discard[nextPlayer][state->discardCount[nextPlayer]-1];
                state->discardCount[nextPlayer]--;
            }
            else {
                //No Card to Reveal
                if (DEBUG) {
                    printf("No cards to reveal\n");
                }
            }
        }

        else {
            if (state->deckCount[nextPlayer] == 0) {
                for (i = 0; i < state->discardCount[nextPlayer]; i++) {
                    state->deck[nextPlayer][i] = state->discard[nextPlayer][i];//Move to deck
                    state->deckCount[nextPlayer]++;
                    state->discard[nextPlayer][i] = -1;
                    state->discardCount[nextPlayer]--;
                }

                shuffle(nextPlayer,state);//Shuffle the deck
            }
            tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
            state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
            state->deckCount[nextPlayer]--;
            tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
            state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
            state->deckCount[nextPlayer]--;
        }

        if (tributeRevealedCards[0] == tributeRevealedCards[1]) { //If we have a duplicate card, just drop one
            state->playedCards[state->playedCardCount] = tributeRevealedCards[1];
            state->playedCardCount++;
            tributeRevealedCards[1] = -1;
        }

        for (i = 0; i <= 3; i ++) {
            if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold) { //Treasure cards
                state->coins += 4;
            }

            else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) { //Victory Card Found
                drawCard(currentPlayer, state);
                drawCard(currentPlayer, state);
            }
            else { //Action Card
                state->numActions = state->numActions + 2;
            }
        }

        return 0; 
}*/
