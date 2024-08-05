#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


static void printDeck(CardDeck deck)
{
  int ind;
  for (ind = 0; ind < deck.size; ind ++)
    {
      printf("%c ", deck.cards[ind]);
    }
  printf("\n");
}

void interleaveHelp(CardDeck leftDeck, CardDeck rightDeck, CardDeck destDeck, int leftind, int rightind, int newind, int round)
{
  if(newind == destDeck.size) //deck has been completed
  {
    if(round == 1)
    {
        printDeck(destDeck);
    }
    shuffle(destDeck, round-1);
  }
    
  if(leftind < leftDeck.size)
  {
    destDeck.cards[newind] = leftDeck.cards[leftind];
    interleaveHelp(leftDeck, rightDeck, destDeck, leftind+1,rightind,newind+1, round);
  }
  if(rightind < rightDeck.size)
  {
    destDeck.cards[newind] = rightDeck.cards[rightind];
    interleaveHelp(leftDeck, rightDeck, destDeck, leftind,rightind+1,newind+1, round);
  }
  
  
}

void interleave(CardDeck leftDeck, CardDeck rightDeck, int round)
{
  CardDeck destDeck = 
    {
      .size = leftDeck.size + rightDeck.size,
      .cards = {0} 
    };
  interleaveHelp(leftDeck, rightDeck, destDeck, 0,0,0, round);
}

void divide(CardDeck origDeck, CardDeck * leftDeck, CardDeck * rightDeck, int round)
{
  for(int i = 1; i < origDeck.size; i++)
  {
    memcpy(&leftDeck->cards[0], origDeck.cards, i * sizeof(char));
    memcpy(&rightDeck->cards[0], origDeck.cards + i, (origDeck.size - i) * sizeof(char));
    leftDeck->size = i;
    rightDeck->size = origDeck.size-i;
    interleave(*leftDeck, *rightDeck, round);
  }
}

void shuffle(CardDeck origDeck, int round)
{
    if (round > 0)
    {
        int poss = origDeck.size - 1;
        CardDeck * leftDeck = (CardDeck *) malloc(poss * sizeof(CardDeck));
        CardDeck * rightDeck = (CardDeck *) malloc(poss * sizeof(CardDeck));
        divide(origDeck, leftDeck, rightDeck, round);
        free(leftDeck);
        free(rightDeck);
    }
    
    
}

