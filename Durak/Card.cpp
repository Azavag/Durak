#include "Card.h"
#include <iostream>


//Установка масти карты
void Card::setSuit(CardSuiting Suit)
{
	CardSuit = Suit;
	if (CardSuit == Hearts)
		SuitImage = 3;
	if (CardSuit == Diamonds)
		SuitImage = 4;
	if (CardSuit == Spades)
		SuitImage = 5;
	if (CardSuit == Clubs)
		SuitImage = 6;
}

//Установка номинала карты
void Card::setDenom(CardDenominal Denom) 
{
		CardDenom = Denom;
		if (CardDenom == Six)
			DenomImage = '6';
		if (CardDenom == Seven)
			DenomImage = '7';
		if (CardDenom == Eight)
			DenomImage = '8';
		if (CardDenom == Nine)
			DenomImage = '9';
		if (CardDenom == Ten)
			DenomImage = static_cast<char>('10');
		if (CardDenom == Jack)
			DenomImage = 'J';
		if (CardDenom == Queen)
			DenomImage = 'Q';
		if (CardDenom == King)
			DenomImage = 'K';
		if (CardDenom == Ace)
			DenomImage = 'A';
}
//Вывод рисунка карты
void Card::CardImage(int numb)
{
	if (CardDenom == Ten)
	{
		std::cout<<numb << ") ______" << std::endl
				  << "  |   10" << SuitImage << "|" << std::endl
				  << "  |      |" << std::endl
			 	  << "  |10"<< SuitImage << "   |" << std::endl
				  << "  |______|" << std::endl;
	}
	else
	{
		std::cout <<numb<< ") ______" << std::endl
			<< "  |    " << DenomImage << SuitImage << "|" << std::endl
			<< "  |      |" << std::endl
			<< "  |" << DenomImage << SuitImage << "    |" << std::endl
			<< "  |______|" << std::endl;
	}
}

Card::CardSuiting Card::getSuit()
{
	return CardSuit;
}

Card::CardDenominal Card::getDenom()
{
	return CardDenom;
}

Card::CardDenominal &operator++(Card::CardDenominal &Den, int)
{
	Card::CardDenominal old = Den;
	Den = static_cast<Card::CardDenominal>(static_cast<int>(Den) + 1);
	return Den;
}

Card::CardSuiting &operator++(Card::CardSuiting & Suit, int)
{
	Card::CardSuiting old = Suit;
	Suit = static_cast<Card::CardSuiting>(static_cast<int>(Suit) + 1);
	return Suit;
}
