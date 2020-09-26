#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 52

// Suggested Struct Values
typedef struct stack {
	struct Card* stk[MAX_SIZE];
}stack;

typedef struct list {
	struct Card* value;
	struct list* nextNode;
}list;

typedef struct Card
{
	int value;

	int id;

} Card;

typedef struct Deck
{
	int size;

	stack* deckCards;

} Deck;

typedef struct Hand
{

	int size;

	list* handCards;

} Hand;

// Create a new card generating a random ID (0-10,000) and value from 0-100

Card* createCard();

// Creates a new deck and sets the size to 0, creates an empty stack within the deck

Deck* createDeck();

// Creates a new hand and sets the size to 0, creates an empty list within the hand

Hand* createHand();

// Adds a created card to a deck, returns 1 if card was added, 0 if card wasn't, -1 if a duplicate id, or more than 4 copies were detected

int addCard(Card* card, Deck* deck);

// Determines if a card exists within a deck given an id, value, or card* returns the number of copies, otherwise 0

int cardExists(int id, Deck* deck);

int cardExistsV(int value, Deck* deck);

int cardExistsC(Card* card, Deck* deck);

// Shuffles deck - size*100 randoms swaps, or a shuffling algorithm

void shuffle(Deck* deck);

// Returns the first card from a deck

Card* drawCard(Deck* deck);

// Moves the top (size-current_hand_size) cards of the deck to the hand structure returns hand size

int fillHand(int size, Hand* hand, Deck* deck);

// prints the hand to the console showing ID and value, one card per line in the format ###\tID-Value

void showHand(Hand* hand);

// Removes the card from hand and displays the card ID and Value in the format ***ID-Value, a value of -1 in id indicates a random card, returns played card id

int playCard(int id, Hand* hand, Deck* deck);

int myRand(int upperLimit);
list* createList();


int main(int argc, char** argv)

{
	// Initialise seed for random number generator
	srand(time(NULL));
	int playable = 1;

	Deck* deck = createDeck();
	Hand* player1 = createHand();
	Hand* player2 = createHand();

	if (deck == NULL || player1 == NULL || player2 == NULL)
	{
		if (deck != NULL)
			free(deck);
		if (player1 != NULL)
			free(player1);
		if (player2 != NULL)
			free(player2);
		playable = 0;
	}

	if (!playable)
	{
		return -1;
	}
	else
	{
		int i = 0;
		for (i = 0; i < 52; i++)
		{
			Card* temp = createCard();
			addCard(temp, deck);
		}

		shuffle(deck);

		fillHand(7, player1, deck);
		fillHand(7, player2, deck);

		for (i = 0; i < 7; i++)
		{// show each player's hand then each player's move
			printf("PLAYER 1 HAND\n");
			showHand(player1);
			printf("PLAYER 2 HAND\n");
			showHand(player2);
			printf("PLAYER 1 PLAY\n");
			playCard(-1, player1, deck);
			printf("PLAYER 2 PLAY\n");
			playCard(-1, player2, deck);
			if (deck->deckCards->stk[0] != NULL) {//draw more cards if possible
				fillHand(7, player1, deck);
				fillHand(7, player2, deck);
			}
		}

		free(deck);
		free(player1);
		free(player2);
	}

	printf("Press Enter to exit");
	while (getchar() == NULL) {
		printf("Invalid option");
	}
	return 0;
}

int myRand(int upperLimit) {
	return rand() % (upperLimit + 1);
}

Card* createCard() {
	Card* c = malloc(sizeof(Card));
	Card card;
	card.value = myRand(100);
	card.id = myRand(10000);
	*c = card;
	return c;
}

Deck*createDeck() {
	Deck* d = malloc(sizeof(Deck));
	Deck deck;
	deck.size = 0;
	stack* s = malloc(sizeof(stack));
	deck.deckCards = s;
	for (int i = 0; i < MAX_SIZE; ++i) {
		deck.deckCards->stk[i] = NULL;
	}
	*d = deck;
	return d;
}

Hand* createHand() {
	Hand* h = malloc(sizeof(Hand));
	Hand hand;
	hand.size = 0;
	hand.handCards = createList();
	*h = hand;
	return h;
}

list* createList() {
	list* l = malloc(sizeof(list));
	list list;
	list.nextNode = NULL;
	list.value = NULL;
	*l = list;
	return l;
}

int addCard(Card* card, Deck* deck) {
	if (cardExists(card->id, deck) > 0) {
		return -1;
	}
	else if (cardExistsV(card->value, deck) >= 4) {
		return -1;
	}
	else if (cardExistsC(card, deck) > 0) {
		return -1;
	}
	else {
		for (int i = 0; i < MAX_SIZE; ++i) {
			if (deck->deckCards->stk[i] == NULL) {
				deck->deckCards->stk[i] = card;
				return 1;
			}
		}
		return 0;
	}
}

int cardExists(int id, Deck* deck) {
	int count = 0;
	for (int i = 0; i < MAX_SIZE; ++i) {
		if (deck->deckCards->stk[i] == NULL) {
			return count;
		}
		if (deck->deckCards->stk[i]->id == id) {
			++count;
		}
	}
	return count;
}

int cardExistsV(int value, Deck* deck) {
	int count = 0;
	for (int i = 0; i < MAX_SIZE; ++i) {
		if (deck->deckCards->stk[i] == NULL) {
			return count;
		}
		if (deck->deckCards->stk[i]->value == value) {
			++count;
		}
	}
	return count;
}

int cardExistsC(Card* card, Deck* deck) {
	int count = 0;
	for (int i = 0; i < MAX_SIZE; ++i) {
		if (deck->deckCards->stk[i] == NULL) {
			return count;
		}
		if (deck->deckCards->stk[i] == card) {
			++count;
		}
	}
	return count;
}

void shuffle(Deck* deck) {
	Card* temp;
	int i;
	for (int n = 0; n < 100; ++n) {
		i = myRand(MAX_SIZE - 2);
		temp = deck->deckCards->stk[i + 1];
		deck->deckCards->stk[i + 1] = deck->deckCards->stk[i];
		deck->deckCards->stk[i] = temp;
	}
}

Card* drawCard(Deck* deck) {
	Card* temp;
	for (int i = 0; i < 52; ++i) {
		if (deck->deckCards->stk[i] == NULL) {
			temp = deck->deckCards->stk[i - 1];
			deck->deckCards->stk[i - 1] = NULL;
			return temp;
		}
	}
	temp = deck->deckCards->stk[51];
	deck->deckCards->stk[51] = NULL;
	return temp;
}

int fillHand(int size, Hand* hand, Deck* deck) {
	list* temp = hand->handCards;
	for (int i = 1; i < size; ++i) {
		if (deck->deckCards->stk[0] != NULL)
		{
			temp->value = drawCard(deck);
			temp->nextNode = createList();
			temp = temp->nextNode;
		}
	}
	return size;
	/*temp = hand->handCards;
	int count = 0;
	while (temp->nextNode->value != NULL) {
	++count;
	temp = temp->nextNode;
	}
	return count;*/
}

void showHand(Hand* hand) {
	list* temp = hand->handCards;
	while (temp->nextNode != NULL) {
		printf("###\tID: %d VALUE: %d\n", temp->value->id, temp->value->value);
		temp = temp->nextNode;
	}
}

int playCard(int id, Hand* hand, Deck* deck) {
	list* temp = hand->handCards;
	list* temp2 = NULL;
	if (id == -1) {
		for (int i = 0; rand() % 2 == 0 && i < 8; ++i) {
			temp2 = temp;
			temp = temp->nextNode;
		}
		if (temp2 == NULL) {
			hand->handCards = temp->nextNode;
		}
		else {
			temp2->nextNode = temp->nextNode;// sets the previous node's next node to be the node after the current node (to allow it's deletion/removal)
		}
		printf("###\tID: %d VALUE: %d\n", temp->value->id, temp->value->value);
		return temp->value->id;
	}
	do {
		if (temp->value->id == id) {
			printf("###\tID: %d VALUE: %d\n", temp->value->id, temp->value->value);
			if (temp2 == NULL) {
				hand->handCards = temp->nextNode;
			}
			else {
				temp2->nextNode = temp->nextNode;// sets the previous node's next node to be the node after the current node (to allow it's deletion/removal)
			}
			return temp->value->id;
		}
		temp2 = temp;
		temp = temp->nextNode;
	} while (temp->nextNode != NULL);
	return -1;
}