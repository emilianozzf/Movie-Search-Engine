#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "a4.h"

#define PRINT_DEBUG 1

// Put your deck functions in here
Deck* CreateDeck() {
    Deck* deck;
    deck = malloc(sizeof(Deck));
    for (int i = 0; i < kNumCardsInDeck; i++) {
        deck->cards[i] = NULL;
    }
    deck->top_card = -1;
    return deck;
}

void DestroyDeck(Deck* deck) {
    for (int i = 0; i < kNumCardsInDeck; i++) {
        free(deck->cards[i]);
	deck->cards[i] = NULL;
	deck->top_card -= 1;
    } 
}

Deck* PushCardToDeck(Card* card, Deck* deck) {
    if (deck->top_card == kNumCardsInDeck - 1) {
        return deck;
    }
    deck->top_card += 1;
    deck->cards[deck->top_card] = card;
    return deck;
}

Card* PeekAtTopCard(Deck* deck) {
    if (deck->top_card == -1) {
        return NULL;
    }
    return deck->cards[deck->top_card];
}

Card* PopCardFromDeck(Deck* deck) {
    if (IsDeckEmpty(deck)) {
        return NULL;
    }
    Card* return_card = deck->cards[deck->top_card];
    deck->cards[deck->top_card] = NULL;
    deck->top_card -= 1;
    return return_card;
}

int IsDeckEmpty(Deck* deck) {
    if (deck->top_card == -1) {
        return 1;
    }
    return 0;
}

Deck* PopulateDeck() {
    Deck* deck = CreateDeck();
    for (int suit = HEARTS; suit <= DIAMONDS; suit++) {
	for (int name = NINE; name <= ACE; name++) {
	    Card* card = malloc(sizeof(Card));
	    card->name = name;
	    card->suit = suit;
	    card->value = -1;
	    deck = PushCardToDeck(card, deck);
	}
    }
    return deck;
}

void Shuffle(Deck* deck) {
    srand(time(0));
    for (int i = 0; i <= deck->top_card; i++) {
	int min_idx = i;
	int max_idx = deck->top_card;
        Card* tmp = deck->cards[i];
	deck->cards[i] = deck->cards[min_idx + (rand() % (max_idx - min_idx + 1))];
        deck->cards[min_idx + (rand() % (max_idx - min_idx + 1))] = tmp;
    }
}

void Deal(Deck* deck, Hand* hand1, Hand* hand2) {
}
