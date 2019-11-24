#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state,
                int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3,
               struct gameState *state, int handPos, int *bonus);
int ambassadorEffect(int choice1, int choice2, int handPos, struct gameState * state, int currentPlayer);
int baronEffect(struct gameState * state, int choice1, int currentPlayer);
int minionEffect(struct gameState * state, int choice1, int choice2, int handPos, int currentPlayer);
int tributeEffect(struct gameState * state, int currentPlayer, int nextPlayer);
int mineEffect(struct gameState * state, int currentPlayer, int choice1, int choice2, int handPos);
void addActions(struct gameState * state, int toAdd);
void addBuys(struct gameState * state, int toAdd);
#endif