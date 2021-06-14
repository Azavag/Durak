#include "PlayerHand.h"
#include "Card.h"
#include <vector>
#include <iostream>
#include <string>

vector<Card>  &PlayerHand::getHand()	{ return Hand; }
//Проверка
//Âçÿòèå êàðòû èç êîëîäû(number äëÿ âîçìîæíîãî áóäóùåãî (ïîäêèäíîãî äóðàêà)
void PlayerHand::TakingCard(std::vector<Card> &deck, int number)
{
	auto iter = deck.begin();
	advance(iter, number - 1);

	Hand.emplace_back(*iter);   
	deck.erase(iter);
}

//Õîä êàðòîé
void PlayerHand::TurningCard(PlayerHand &OtherHand, int number)
{
	auto iter = Hand.begin();
	advance(iter,number);
	OtherHand.Hand.emplace_back(*iter);
	Hand.erase(iter);
}
//Ïîêàçàòü âñþ ðóêó êàðò
void PlayerHand::ShowHand()
{
	int count = 1;
	for (auto elem : Hand)
	{	
		elem.CardImage(count);
		++count;
	}
}

//Ïðîâåðêà íà âîçìîæíîñòü îòáèòèÿ êàðòû (table - êàðòà íà ñòîëå, card - êàðòà, êîòîðóþ ïðîâåðÿåì)		!!!!!!ÏÎ×ÈÍÈÒÜ ÀÍÀËÈÇ Ñ ÊÎÇÛÐÍÛÌÈ ÊÀÐÒÀÌÈ
bool PlayerHand::Analysis(PlayerHand table, Card card) //íàäî áûëî ïåðåäàâàòü â ïàðàìåòð ñðàçó êàðòó
{	//Åñëè ìàñòü âûáðàííîé êàðòû ñîâïàäàåò ñ ìàñòüþ êàðòû íà ñòîëå è å¸ íîìèíàë áîëüøå èëè âûáðàííàÿ êàðòà êîçûðü
	//if (table.Hand.at(number).getSuit() == Card::CardSuiting::Trumps && card.getSuit() == Card::CardSuiting::Trumps)
	//	return true;
	//else
	if(table.Hand.front().getSuit() != Card::CardSuiting::Trumps)
	{
		if ((card.getSuit() == table.getHand().front().getSuit() && card.getDenom() > table.getHand().front().getDenom())
			|| (card.getSuit() == Card::CardSuiting::Trumps && card.getDenom()))//< Card::CardDenominal::Jack))
			return true;
	}
	else
	{
		if (card.getSuit() == table.getHand().front().getSuit() && card.getDenom() > table.getHand().front().getDenom())
			return true;
	}
	return false;
}
//Îòáèòèå êàðòû
void PlayerHand::KickCard(int number, PlayerHand &table)		//number - íîìåð êàðòû èç ðóêè, table - îòêóäà îòáèòü(ñî ñòîëà ïî óìîë÷àíèþ)
{
	auto iter = this->Hand.begin();
	iter += number;
	Hand.erase(iter);
	table.getHand().erase(table.getHand().begin());
}
//ôóíêöèÿ ïîäêèäûâàíèÿ ó èãðîêà
void PlayerHand::PlayerThrowUP(PlayerHand &Table)
{	
	string answer;
	int i = 0;
	for (auto elem : this->getHand())
	{
		if (elem.getDenom() == Table.getHand().front().getDenom())
		{
				cout << "Âû ìîæåòå ïîäêèíóòü êàðòó ñîïåðíèêó." << endl;
				elem.CardImage(i + 1);
				cout << "Ââåäèòå YES èëè NO." << endl;
				getline(cin, answer);
				if (answer == "YES")
				{
					this->TurningCard(Table, i);
					cout << "Âû ïîäêèíóëè êàðòó ñîïåðíèêó." << endl;
				}
				else if (answer == "NO")
					cout << "Âû îñòàâëÿåòå êàðòó â ðóêå." << endl;
				break;
		}
		i++;
	}
}
//Ôóíêöèÿ äëÿ ïîäêèäûâàíèÿ ó ÀÈ
void PlayerHand::AIThrowUP(PlayerHand &Table)
{
	int i = 0;
	for (auto elem : this->getHand())
	{
		if (elem.getDenom() == Table.getHand().front().getDenom() && elem.getSuit() != Card::CardSuiting::Trumps)
		{
			cout << "Êîìïüþòåð ïîäêèäûâàåò âàì êàðòó." << endl;
			elem.CardImage(i + 1);
			this->TurningCard(Table, i);
			break;
		}
		i++;
	}
}
