#include "DeckInitialization.h"
#include "Card.h"
#include <vector>
#include <iostream>
void DeckInitialization(std::vector<Card> &deck)
{
	for (Card::CardDenominal den = Card::CardDenominal::Six; den <=Card::CardDenominal::Ace; den++)
	{
		static int i = 0;
		for (Card::CardSuiting suit = Card::CardSuiting::Hearts; suit <= Card::CardSuiting::Clubs; suit++)
		{
			deck.at(i).setDenom(den);
			deck.at(i).setSuit(suit);
			i++;
		}
	}
}
