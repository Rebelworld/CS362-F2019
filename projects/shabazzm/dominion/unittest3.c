/* -----------------------------------------------------------------------
 * Name: Maryum Shabazz
 * Date: 11/8/2019
 * Description: Unit Test File for CS 362 Fall 2019
 * unittest1: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, minion};
    struct gameState G, testG;
   
    
    //initialize game 
    initializeGame(2,k,seed,&G);
    //copy the game state to a test case
    memcpy (&testG, &G, sizeof(struct gameState));

    int currentPlayer=whoseTurn(&testG);


    //Printing output to test baron card
    printf ("TESTING Card Test 3: BARON:\n\n");
    //set one card in test as estate
    testG.hand[0][0]=estate;
    //check number of estates in hand. 
    int numEstates=0;
    for(int i=0; i<testG.handCount[0]; i++)
    {
        if(testG.hand[0][i]==estate)
        {
            numEstates++;
        }
    }
    

    //test to see if number of buys has been incremented as expected after playing baron
    int numberOfBuysBefore=G.numBuys;
    int coinsBeforeBaron=testG.coins;
    printf("Number of buys before playing baron is %d\n",numberOfBuysBefore);
    baronPlay(1,currentPlayer,&testG);

    if(assertValues((numberOfBuysBefore+1),testG.numBuys))
    {
        printf("PASS: number of buys was increased after baron card was played\n");
        printf("number of buys after playing baron %d\n\n",testG.numBuys);
    }
    else
    {
        printf("FAIL: number of buys not increased after baron card was played.\n");
        printf("number of buys after playing baron %d\n\n",testG.numBuys);

    }

    //test to see if number of coins was increased when baron card was played
    if(assertValues((coinsBeforeBaron+4),testG.coins))
    {
        printf("PASS: coins increased by 4 after baron card played with estate chosen to be trashed\n");
        printf("coins before baron %d\n",coinsBeforeBaron);
        printf("coins after baron %d\n\n",testG.coins);
    }
    else
    {
        printf("FAIL: coins not increased by 4 after baron card played with estate chosen to be trashed\n");
        printf("coins before baron %d\n",coinsBeforeBaron);
        printf("coins after baron %d\n\n",testG.coins);
    }



    //test to see if number of estates in supply remains same after baron played. 
    int estatesInSupplyAfter=testG.supplyCount[estate];
    int estatesInSupplyBefore=G.supplyCount[estate];

    if(assertValues(estatesInSupplyBefore,estatesInSupplyAfter))
    {
        printf("PASS: #estates in Supply are not changed after baron card is played and estates present in hand\n\n");
    }
    else
    {
        printf("FAIL: #estates in Supply are changed after baron card is played and estates present in hand\n\n");
    }

    //test to see if number of estates in hand changes after baron played. 
    int numEstatesBeforeBaron=0;
    for(int i=0; i<G.handCount[0];i++)
    {
        if(G.hand[0][i]==estate)
        {
            numEstatesBeforeBaron++;
        }
    }
    
    for(int i=0; i<testG.handCount[0]; i++)
    {
        if(testG.hand[0][i]==estate)
        {
            numEstates++;
        }
    }

    if(assertValues(numEstates,(numEstatesBeforeBaron-1)))
    {
        printf("PASS:#estates in hand decremented by 1 after choosing to discard estate \n\n");
    }
    else
    {
        printf("FAIL:#estates in hand not decremented by 1 after choosing to discard estate \n");
        printf("number of estates in hand before baron card played is %d\n",numEstatesBeforeBaron);
        printf("number of estates in hand after baron card played is %d\n\n",numEstates);
    }

    //copy the game state to  test case
    memcpy (&testG, &G, sizeof(struct gameState));
    numEstatesBeforeBaron = G.supplyCount[estate];

    int preNumEstatesInDiscard=0;
    //estates in discard before baron
    for(int i=0; i<testG.discardCount[0]; i++)
    {
        if(testG.discard[0][i]==estate)
        {
            preNumEstatesInDiscard++;
        }
    }

    //test if player has an estate and chooses not to discard estate and estate should be gained from supply
     baronPlay(0,currentPlayer,&testG);
     numEstates=testG.supplyCount[estate];
     if(assertValues(numEstates,(numEstatesBeforeBaron-1)))
     {
        printf("PASS: Supply of barons decremented correctly after user has chosen not to discard an estate\n\n");
     }
     else
     {
        printf("FAIL: Supply of estates not decremented correctly after user has chosen not to discard an estate\n");
        printf("number of estates in supply before playing baron %d\n",numEstatesBeforeBaron);
        printf("number of estates in supply  after playing baron %d\n\n",numEstates );
     }

    //test to see if baron has been added to discard pile
    int postNumEstatesInDiscard=0;

     //estates in discard after baron
    for(int i=0; i<testG.discardCount[0]; i++)
    {
        if(testG.discard[0][i]==estate)
        {
            postNumEstatesInDiscard++;
        }
    }   

    if(assertValues((preNumEstatesInDiscard+1),postNumEstatesInDiscard))
    {
         printf("PASS: estate added to discard pile pile from supply\n\n");

    }
    else
    {
        printf("FAIL: estate not added to discard pile pile from supply\n\n");
    }        
    //test to see if estate supply counts is 0 after final card removed(estate will be made zero by baron)
    
     memcpy(&testG,&G,sizeof(struct gameState));
     testG.supplyCount[estate]=1;    //sets two supply counts at zero
     testG.supplyCount[duchy]=0;
     testG.supplyCount[curse]=0;
        
     baronPlay(0,currentPlayer,&testG);
     if(assertValues(testG.supplyCount[estate],0))
     {
         printf("PASS: supply count for estate is now zero after final card removed\n\n");
     }
     else
     {
         printf("FAIL: supply count for estate is not 0 after what should be final card removed\n"); 
         printf("supply count for estate now %d\n\n",testG.supplyCount[estate]);
     }
   //test to see if can gain estate even if no estates in supply
     memcpy(&testG,&G,sizeof(struct gameState));
     testG.supplyCount[estate]=0;
     //discard count of estates before playing baron
      numEstatesBeforeBaron=0;
      numEstates=0;
     for(int i=0; i<testG.discardCount[0]; i++)
     {
         if((testG.discard[0][i])==estate)
         {
             numEstatesBeforeBaron++;
         }
     }
     baronPlay(0,currentPlayer,&testG);
    
     //discard count of estates after playing baron 
     for(int i=0; i<testG.discardCount[0]; i++)
     {
         if((testG.discard[0][i])==estate)
         {
             numEstates++;
         }
     }

     if(assertValues(numEstates,numEstatesBeforeBaron))
     {
         printf("PASS:No additional estates added to discard pile, when estate supply empty\n\n");
     }
     else
     {
         printf("FAIL:Mismatch in number of estates in discard pile after baron played and estate supply empty\n\n"); 
     }
     
     //checking if no estates in hand and attempt to discard an estate
     memcpy(&testG,&G,sizeof(struct gameState));
     numEstatesBeforeBaron=0;
     for(int i=0; i<testG.handCount[0]; i++)
     {
         if((testG.hand[0][i])==estate)
         {
            testG.supplyCount[estate]++;
            testG.hand[0][i]=curse;
            testG.supplyCount[curse]--;
         }
         
         //counts estates in discard pile before playing baron 
         if(testG.discard[0][i]==estate)
         {
             numEstatesBeforeBaron++;
         }
         
     }


    //test estate should be gained even if attempting discard and no estates to discard from hand.
    baronPlay(1,currentPlayer,&testG);
    numEstates=0;
    for(int i=0; i<testG.discardCount[0];i++)
    {
        if((testG.discard[0][i])==estate)
        {
            numEstates++;
        }
    }
    if(assertValues(numEstates,(numEstatesBeforeBaron+1)))
    {
        printf("PASS:player has gained estate to discard pile, after attempting to discard estate with none in hand\n\n");
    }
    else
    {
        printf("FAIL:player has not gained another estate after attempting to discard and no estate to discard\n");
        printf("supply still has estates\n\n");
    }
    printf("END OF TEST BARON CARD\n");
    printf("********************************************************************************************************\n");
    return 0;
}

/*int baronPlay(int choice1, int currentPlayer, struct gameState *state)
{


        if (choice1 > 0) { //Boolean true or going to discard an estate
            int p = 0;//Iterator for hand!
            int card_not_discarded = 1;//Flag for discard set!
            while(card_not_discarded) {
                if (state->hand[currentPlayer][p] == estate) { //Found an estate card!
                    state->coins += 4;//Add 4 coins to the amount of coins
                    state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
                    state->discardCount[currentPlayer]++;
                    for (; p < state->handCount[currentPlayer]; p++) {
                        state->hand[currentPlayer][p] = state->hand[currentPlayer][p+1];
                    }
                    state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
                    state->handCount[currentPlayer]--;
                    card_not_discarded = 0;//Exit the loop
                }
                else if (p > state->handCount[currentPlayer]) {
                    if(DEBUG) {
                        printf("No estate cards in your hand, invalid choice\n");
                        printf("Must gain an estate if there are any\n");
                    }
                    if (supplyCount(estate, state) > 0) {
                        gainCard(estate, state, 0, currentPlayer);

                        
                        if (supplyCount(estate, state) == 0) {
                            isGameOver(state);
                        }
                    }
                    card_not_discarded = 0;//Exit the loop
                }

                else {
                    p++;//Next card
                }
            }
        }

        else {
            if (supplyCount(estate, state) > 0) {
                gainCard(estate, state, 0, currentPlayer);//Gain an estate

                state->supplyCount[estate]--;//Decrement Estates
                if (supplyCount(estate, state) == 0) {
                    isGameOver(state);
                }
            }
        }

    return 0;
}*/
