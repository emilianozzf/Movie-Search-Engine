// Name: Emiliano Zhu
// Date: 2020.02.11
// File: deck.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "a4.h"

#define PRINT_DEBUG 1

// Creates the deck, initializing any fields necessary.
// Returns a pointer to the deck, which has been allocated on the heap.
Deck* CreateDeck() {
    Deck* deck;
    deck = malloc(sizeof(Deck));
    for (int i = 0; i < kNumCardsInDeck; i++) {
        deck->cards[i] = NULL;
    }
    deck->top_card = -1;
    return deck;
}

// Adds a card to the top of the deck.
// Returns a pointer to the deck.
Deck* PushCardToDeck(Card* card, Deck* deck) {
    if (deck->top_card == kNumCardsInDeck - 1) {
        return deck;
    }
    deck->top_card += 1;
    deck->cards[deck->top_card] = card;
    return deck;
}

// Shows the top card, but does not remove it from the stack.
// Returns a pointer to the top card.
// If the deck is empty, return NULL.
Card* PeekAtTopCard(Deck* deck) {
    if (IsDeckEmpty(deck)) {
        return NULL;
    }
    return deck->cards[deck->top_card];
}

// Removes the top card from the deck and returns it.
// The card should NOT be freed at this point; it is the
// responsibility of the caller to free the card at the
// appropriate time.
// Returns a pointer to the top card in the deck.
// If the deck is empty, return NULL.
Card* PopCardFromDeck(Deck* deck) {
    if (IsDeckEmpty(deck)) {
        return NULL;
    }
    Card* return_card = deck->cards[deck->top_card];
    deck->top_card -= 1;
    return return_card;
}

// Determines if the deck is empty.
// Returns 1 if the Deck is empty, 0 otherwise.
int IsDeckEmpty(Deck* deck) {
    if (deck->top_card == -1) {
        return 1;
    }
    return 0;
}

// Create a Deck for this game, and add any
// needed cards to the deck.
// Return a pointer to the deck to be used for the game
Deck* PopulateDeck() {
    Deck* deck = CreateDeck();
    for (int suit = HEARTS; suit <= DIAMONDS; suit++) {
        for (int name = NINE; name <= ACE; name++) {
            Card* card = CreateCard(suit, name);
            deck = PushCardToDeck(card, deck);
        }
    }
    return deck;
}

// Creates a card, initializing the suit and name to that specified.
// Returns a pointer to the new card, which has been allocated on the heap.
// It is the responsibility of the caller to call destroyCard()
// when it is done with the Card.
Card* CreateCard(Suit suit, Name name) {
    Card* card = malloc(sizeof(Card));
    card->suit = suit;
    card->name = name;
    card->value = -1;
    return card;
}

// Takes all the cards in the deck, rearrange
// them in random order, and push the cards back into the Deck.
void Shuffle(Deck* deck) {
    srand(time(0));
    int size = deck->top_card + 1;
    Card* rdm_cards[size];
    for (int i = 0; i < size; i++) {
        rdm_cards[i] = NULL;
    }

    int i = 0;
    while (i < size) {
        int rdm_idx = rand() % size;
        if (rdm_cards[i] == NULL) {
            rdm_cards[i] = PopCardFromDeck(deck);
            i += 1;
        }
    }

    for (int i = 0; i < size; i++) {
        PushCardToDeck(rdm_cards[i], deck);
    }
}

// Destroys the deck, freeing any memory allocated
// for this deck (the cards and the deck).
// DestroyDeck should call DestroyCard on all of the
// cards in the deck.
void DestroyDeck(Deck* deck) {
    for (int i = 0; i < deck->top_card + 1; i++) {
         DestroyCard(deck->cards[i]);
    }
    free(deck);
}

// Destroys the card, freeing any memory allocated for the card.
void DestroyCard(Card* card) {
    free(card);
}

// Given a deck (assume that it is already shuffled),
// take the top card from the deck and alternately give
// it to player 1 and player 2, until they both have
// kNumCardsInHand.
void Deal(Deck* deck, Hand* hand1, Hand* hand2) {
    for (int i = 0; i < kNumCardsInHand; i++) {
       AddCardToHand(PopCardFromDeck(deck), hand1);
       AddCardToHand(PopCardFromDeck(deck), hand2);
    }
}


