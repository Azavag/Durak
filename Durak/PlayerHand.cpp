#include "PlayerHand.h"
#include "Card.h"
#include <vector>
#include <iostream>
#include <string>

vector<Card>  &PlayerHand::getHand()	{ return Hand; }

//ПРОВЕРКИ КОДИРОВКИ
//Взятие карты из колоды(number для возможного будущего (подкидного дурака)
void PlayerHand::TakingCard(std::vector<Card> &deck, int number)
{
	auto iter = deck.begin();
	advance(iter, number - 1);

	Hand.emplace_back(*iter);   
	deck.erase(iter);
}

//Ход картой
void PlayerHand::TurningCard(PlayerHand &OtherHand, int number)
{
	auto iter = Hand.begin();
	advance(iter,number);
	OtherHand.Hand.emplace_back(*iter);
	Hand.erase(iter);
}
//Показать всю руку карт
void PlayerHand::ShowHand()
{
	int count = 1;
	for (auto elem : Hand)
	{	
		elem.CardImage(count);
		++count;
	}
}

//Проверка на возможность отбития карты (table - карта на столе, card - карта, которую проверяем)		!!!!!!ПОЧИНИТЬ АНАЛИЗ С КОЗЫРНЫМИ КАРТАМИ
bool PlayerHand::Analysis(PlayerHand table, Card card) //надо было передавать в параметр сразу карту
{	//Если масть выбранной карты совпадает с мастью карты на столе и её номинал больше или выбранная карта козырь
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
//Отбитие карты
void PlayerHand::KickCard(int number, PlayerHand &table)		//number - номер карты из руки, table - откуда отбить(со стола по умолчанию)
{
	auto iter = this->Hand.begin();
	iter += number;
	Hand.erase(iter);
	table.getHand().erase(table.getHand().begin());
}
//функция подкидывания у игрока
void PlayerHand::PlayerThrowUP(PlayerHand &Table)
{	
	string answer;
	int i = 0;
	for (auto elem : this->getHand())
	{
		if (elem.getDenom() == Table.getHand().front().getDenom())
		{
				cout << "Вы можете подкинуть карту сопернику."<<endl;
				elem.CardImage(i + 1);
				cout << "Введите YES или NO." << endl;
				getline(cin, answer);
				if (answer == "YES")
				{
					this->TurningCard(Table, i);
					cout << "Вы подкинули карту сопернику." << endl;
				}
				else if (answer == "NO")
					cout << "Вы оставляете карту в руке." << endl;
				break;
		}
		i++;
	}
}
//Функция для подкидывания у АИ
void PlayerHand::AIThrowUP(PlayerHand &Table)
{
	int i = 0;
	for (auto elem : this->getHand())
	{
		if (elem.getDenom() == Table.getHand().front().getDenom() && elem.getSuit() != Card::CardSuiting::Trumps)
		{
			cout << "Компьютер подкидывает вам карту." << endl;
			elem.CardImage(i + 1);
			this->TurningCard(Table, i);
			break;
		}
		i++;
	}
}
