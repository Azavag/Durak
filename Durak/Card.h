#pragma once
class Card
{

public:
	//Номинал карт
	enum CardDenominal
	{
		Six=6,
		Seven=7,
		Eight=8,
		Nine=9,
		Ten=10,
		Jack = 11,
		Queen = 12,
		King = 13,
		Ace = 14
	};
	//Масти карт
	enum CardSuiting
	{
		Trumps = 10,	//Козыри
		Hearts = 3,		//Черви
		Diamonds = 4,	//Бубны
		Spades = 5,		//Пики
		Clubs = 6		//Трефы
	};
	char DenomImage=0;				//Знак номинала
	char SuitImage=0;					//Знак масти

	//Установка масти карты
	void setSuit(CardSuiting Suit);
	//Возвращает Масть карты
	CardSuiting getSuit();
	//Возвращает номинал карты
	CardDenominal getDenom();
	//Установка номинала карты
	void setDenom(CardDenominal Denom);	
	//Вывод изображения карты
	void CardImage(int numb);
	
	friend CardDenominal &operator++(CardDenominal &Den, int);
	friend CardSuiting &operator++(CardSuiting &Suit, int);


private:
	CardSuiting CardSuit;			//Масть карты
	CardDenominal CardDenom;		//Номинал карты

};
