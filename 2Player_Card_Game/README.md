This project covers the design of a user interface, and the background storage / management of cards for a two player card game similar to ‘Poker’, ‘Bridge’, ‘Heathstone’, ‘Pokemon’, ‘Magic the Gathering’, or ‘Fluxx’.

PROGRAM TASK

Implement a set of components for a card game consisting of:
•	Deck – a stack of 0 or more cards, order of cards matters
•	Hand – a linked list of 0 or more cards, order of cards is irrelevant
•	Card – a collection of values representing a card in the game, at a minimum an ID and a Value. 


•	Generate an ordered Deck of 52 cards
  o	  Each Card has a unique ID
  o	  Each Card shares a value with no more than 3 other cards in the Deck (so 4 of a single card value per deck)
  o	  The Deck is ordered with the Card values ascending (e.g. if the values 1,2,3, 1,2,3 are used the order will be: 1,1,2,2,3,3)
  
•	Output the order of the Deck

•	Shuffle the Deck using a shuffling algorithm of your own choice, at a minimum perform Deck size * 100 random two card swaps.

•	Output the order of the Deck

•	Draw two Hands of cards from the Deck

•	Have players take turns until there are no cards in the deck:
  o	  Play the highest valued Card from their Hand (display value, remove from hand)
  o	  Draw a card from the Deck

