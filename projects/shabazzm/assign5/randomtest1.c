/*
Name: Maryum Shabazz
Date: 11/14/2019
Description: Test for Baron  card
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
void checkChoices(int cho1)
{

	//prints choice chosen by user this turn 
	if(cho1==1)
	{
		printf("Player has chosen to discard an estate in exchange for 4 coins\n");
	}

	//prints choice chosen by user this turn
	if(cho1==0)
	{
		printf("Player has chosen to gain an estate\n");
	}

}


int main() {
    int seed = 1000;
    int testPassed=0;
    int failedTest=0;
    
	//seed random number generator
	srand(time(0));
    int choice1=0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, minion};
    struct gameState G, testG;
      
    
   
	
	//Printing output to test Baron Card
    printf ("TESTING Card Test 1: Baron:\n");
    

    //for loop used to repeat tests over and over for coverage with different variables each time. 
    for(int i=0; i<50; i++)
    {


         printf("TEST RUN #%d\n",(i+1));

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
            	
    	} 
    	else
    	{
    		choice1=0;
    		
    	}
    
    	//initialize game 
   		initializeGame(numPlayers,k,seed,&G);
    	int currentPlayer=whoseTurn(&testG);

        int estatesInSupplyBefore=testG.supplyCount[estate];
    	//copy the game state to a test case
    	memcpy (&testG, &G, sizeof(struct gameState));

        
	checkChoices(choice1);

        //used to randomize choice1 and choice2
        num1=(rand() % (5 - 2 + 1)) + 2;
        //randomizes player hand count
        testG.handCount[0]=num1;

        //fills hand with random cards
        for(int i=0; i<testG.handCount[0];i++)
        {
            
            num1=(rand() % (5 - 1 + 1)) + 1;
            if(num1==1 && num1==2)
            {
                testG.hand[0][i]=estate;
            }
            else
            {
                testG.hand[0][i]=num1;
            }
        }

        //coints number of estates in hand before baron
        //test to see if number of estates in hand changes after baron played. 
        int numEstatesBeforeBaron=0;
        for(int i=0; i<testG.handCount[0];i++)
        {
            if(testG.hand[0][i]==estate)
            {
                numEstatesBeforeBaron++;
            }
        }

         int preNumEstatesInDiscard=0;
       
        //estates in discard of player 1 before baron
        for(int i=0; i<testG.discardCount[0]; i++)
        {
            if(testG.discard[0][i]==estate)
            {
                preNumEstatesInDiscard++;
            }
        }

        int numEstatesBeforeBaronInSupply = testG.supplyCount[estate];
        int numberOfBuysBefore=testG.numBuys;

        baronEffect(&testG,choice1,currentPlayer);

        printf("Number of buys before playing baron is %d\n",numberOfBuysBefore);
            

            if(assertValues((numberOfBuysBefore+1),testG.numBuys))
            {
                printf("PASS: number of buys was increased after baron card was played\n");
                printf("number of buys after playing baron %d\n\n",testG.numBuys);
                passTest++;
            }
            else
            {
                printf("FAIL: number of buys not increased after baron card was played.\n");
                printf("number of buys after playing baron %d\n\n",testG.numBuys);
                testFailed++;
            }

        
        

        //if user chooses to discard estate 
        if(choice1==1)
        {
             //test to see if number of buys has been incremented as expected after playing baron
            
            int coinsBeforeBaron=testG.coins;
            


            //test to see if number of coins was increased when baron card was played
            if(assertValues((coinsBeforeBaron+4),testG.coins) && numEstatesBeforeBaron>0)
            {
                printf("PASS: coins increased by 4 after baron card played with estate chosen to be trashed\n");
                printf("coins before baron %d\n",coinsBeforeBaron);
                printf("coins after baron %d\n\n",testG.coins);
                passTest++;
            }
            else
            {
                printf("FAIL: coins not increased by 4 after baron card played with estate chosen to be trashed\n");
                printf("coins before baron %d\n",coinsBeforeBaron);
                printf("coins after baron %d\n\n",testG.coins);
                testFailed++;
            }


             //test to see if number of estates in supply remains same after baron played. 
            int estatesInSupplyAfter=testG.supplyCount[estate];
            if(assertValues(estatesInSupplyBefore,estatesInSupplyAfter))
            {
                printf("PASS: #estates in Supply are not changed after baron card is played, & player chooses to discard estate\n\n");
                passTest++;
            }
            else
            {
                printf("FAIL: #estates in Supply are changed after baron card is played & player chooses to discard estate \n\n");
                testFailed++;
            }

            int numEstates=0;
            if(numEstatesBeforeBaron>0)
            {
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
                    passTest++;
                }
                else
                {
                    printf("FAIL:#estates in hand not decremented by 1 after choosing to discard estate \n");
                    printf("number of estates in hand before baron card played is %d\n",numEstatesBeforeBaron);
                    printf("number of estates in hand after baron card played is %d\n\n",numEstates);
                    testFailed++;
                }
            }

            //test if player has an estate and chooses not to discard estate and estate should be gained from supply
    
             numEstates=testG.supplyCount[estate];
             
             if(choice1==0)
             {
                 if(assertValues(numEstates,(numEstatesBeforeBaronInSupply-1)))
                 {
                    printf("PASS: Supply of estates decremented correctly after user has chosen not to discard an estate\n\n");
                    passTest++;
                 }
                 else
                 {
                    printf("FAIL: Supply of estates not decremented correctly after user has chosen not to discard an estate\n");
                    printf("number of estates in supply before playing baron %d\n",numEstatesBeforeBaronInSupply);
                    printf("number of estates in supply  after playing baron %d\n\n",numEstates );
                    testFailed++;
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
                     passTest++;

                }
                else
                {
                    printf("FAIL: estate not added to discard pile pile from supply\n\n");
                    testFailed++;
                }        


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
printf("END TEST BARON\n");
printf("******************************************************************************************************\n");
return 0;   

}
