// Name: Emiliano Zhu
// Date: 2020.02.05
// File: a4.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "a4.h"

#define kPrintDebug 1

// Creates a Hand struct and initializes any necessary fields.
// Returns a pointer to the new Hand, which has been allocated on the heap.
Hand* CreateHand() {
    return NULL;
}

// Adds a card to the hand.
void AddCardToHand(Card *card, Hand *hand) {
}

// Removes a card from the hand.
// Does not free the card; it is the responsibility
// of the caller to free the card at the appropriate
// time.
// Returns a pointer to the card that is no longer in the hand.
Card* RemoveCardFromHand(Card *card, Hand *hand) {
    return NULL;
}

// Determines if there are any cards in the hand.
// Return 1 if the hand is empty; 0 otherwise.
int IsHandEmpty(Hand* hand) {
    return 0;
}

// Destroys the hand, freeing any memory allocated for it.
void DestroyHand(Hand* hand) {
}

// Given a lead card, a players hand, and the card the player wants
// to play, is it legal?
// If the player has a card of the same suit as the ledCard, they
// must play a card of the same suit.
// If the player does not have a card of the same suit, they can
// play any card.
// Returns 1 if the move is legal; 0 otherwise.
int IsLegalMove(Hand *hand, Card *lead_card, Card *played_card) {
    return 0;
}

// Given two cards that are played in a hand, which one wins?
// If the suits are the same, the higher card name wins.
// If the suits are not the same, player 1 wins, unless player 2 played trump.
// Returns 1 if the person who led won, 0 if the person who followed won.
int WhoWon(Card *lead_card, Card *followed_card, Suit trump) {
     return 0;
}

// Take all the cards out of a given hand, and put them
// back into the deck.
void ReturnHandToDeck(Hand *hand, Deck *deck) {
}
