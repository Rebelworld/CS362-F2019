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
    tributePlay(choice1,choice2,nextPlayer,handPos,currentPlayer,&testG,testG.hand[1]);

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

    tributePlay(choice1,choice2,nextPlayer,handPos,currentPlayer,&testG,testG.hand[1]);

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

    tributePlay(choice1,choice2,nextPlayer,handPos,currentPlayer,&testG,testG.hand[1]);

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
