#pragma once
#include <vector>
#include "Card.h"
#include <iostream>

using namespace std;
class PlayerHand
{
	vector<Card> Hand;

public:

	PlayerHand()
	{
		Hand.reserve(6);
	}
	vector<Card> &getHand();
	//Взятие карты из колоды(Первая раздача + Добор до 6 + карта от противника)
	void TakingCard(std::vector<Card> &deck, int number);

	//Ход картой
	void TurningCard(PlayerHand &OtherHand, int number);
	//Показать руку карт
	void ShowHand();
	//Проверка на возможность отбития карты
	bool Analysis(const PlayerHand table, Card card);
	//Отбитие карты
	void KickCard(int number, PlayerHand &table);
	//Подкидывание карты(для игрока)
	void PlayerThrowUP(PlayerHand &table);
	//Подкидывание карты(для "ИИ")
	void AIThrowUP(PlayerHand &Table);
};

