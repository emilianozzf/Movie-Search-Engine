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
    Hand* hand = malloc(sizeof(Hand));
    hand->num_cards_in_hand = 0;
    hand->first_card = NULL;
    return hand;
}

// Adds a card to the hand.
void AddCardToHand(Card* card, Hand* hand) {
    CardNode* new_card = malloc(sizeof(CardNode));
    new_card->this_card = card;
    new_card->prev_card = NULL;
    new_card->next_card = NULL;

    if (hand->first_card == NULL) {
        hand->first_card = new_card;
    } else {
        hand->first_card->prev_card = new_card;
        new_card->next_card = hand->first_card;
        hand->first_card = new_card;
    }
    hand->num_cards_in_hand += 1;
}

// Removes a card from the hand.
// Does not free the card; it is the responsibility
// of the caller to free the card at the appropriate
// time.
// Returns a pointer to the card that is no longer in the hand.
Card* RemoveCardFromHand(Card *card, Hand *hand) {
    CardNode* cur = hand->first_card;
    while (cur != NULL) {
        if (cur->this_card == card) {
             if (cur->prev_card == NULL && cur->next_card == NULL) {
                 hand->first_card = NULL;
             } else if (cur->prev_card != NULL && cur->next_card == NULL) {
                 cur->prev_card->next_card = NULL;
                 cur->prev_card = NULL;
             } else if (cur->prev_card == NULL && cur->next_card != NULL) {
                 hand->first_card = cur->next_card;
                 cur->next_card->prev_card = NULL;
                 cur->next_card = NULL;
             } else {
                 cur->prev_card->next_card = cur->next_card;
                 cur->next_card->prev_card = cur->prev_card;
                 cur->next_card = NULL;
                 cur->prev_card = NULL;
             }
             free(cur);
             break;
         }
         cur = cur->next_card;
    }
    hand->num_cards_in_hand -= 1;
    return card;
}

// Determines if there are any cards in the hand.
// Return 1 if the hand is empty; 0 otherwise.
int IsHandEmpty(Hand* hand) {
    if (hand->num_cards_in_hand == 0) {
        return 1;
    }
    return 0;
}

// Destroys the hand, freeing any memory allocated for it.
void DestroyHand(Hand* hand) {
     free(hand);
}

// Given a lead card, a players hand, and the card the player wants
// to play, is it legal?
// If the player has a card of the same suit as the ledCard, they
// must play a card of the same suit.
// If the player does not have a card of the same suit, they can
// play any card.
// Returns 1 if the move is legal; 0 otherwise.
int IsLegalMove(Hand *hand, Card *lead_card, Card *played_card) {
    CardNode* cur = hand->first_card;
    while (cur != NULL) {
        if (cur->this_card->suit == lead_card->suit) {
             if (lead_card->suit == played_card->suit) {
                 return 1;
             }
             return 0;
        }
        cur = cur->next_card;
    }
    return 1;
}

// Given two cards that are played in a hand, which one wins?
// If the suits are the same, the higher card name wins.
// If the suits are not the same, player 1 wins, unless player 2 played trump.
// Returns 1 if the person who led won, 0 if the person who followed won.
int WhoWon(Card *lead_card, Card *followed_card, Suit trump) {
     if (lead_card->suit == followed_card->suit) {
         if (lead_card->name > followed_card->name) {
             return 1;
         } else {
             return 0;
         }
     } else {
         if (followed_card->suit == trump) {
             return 0;
         } else {
             return 1;
         }
     }
}

// Take all the cards out of a given hand, and put them
// back into the deck.
void ReturnHandToDeck(Hand *hand, Deck *deck) {
     CardNode* cur = hand->first_card;
     while (cur != NULL) {
         PushCardToDeck(cur->this_card, deck);
         cur = cur->next_card;
     }
}
