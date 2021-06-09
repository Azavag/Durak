#pragma once
#include <vector>
#include "Card.h"
#include <iostream>

using namespace std;
class PlayerHand
{
	vector<Card> Hand;

public:
	//�����������
	PlayerHand()
	{
		Hand.reserve(6);
	}
	vector<Card> &getHand();
	//������ ����� �� ������(������ ������� + ����� �� 6 + ����� �� ����������)
	void TakingCard(std::vector<Card> &deck, int number);

	//��� ������
	void TurningCard(PlayerHand &OtherHand, int number);
	//�������� ���� ����
	void ShowHand();
	//�������� �� ����������� ������� �����
	bool Analysis(const PlayerHand table, Card card);
	//������� �����
	void KickCard(int number, PlayerHand &table);
	//������������ �����(��� ������)
	void PlayerThrowUP(PlayerHand &table);
	//������������ �����(��� "��")
	void AIThrowUP(PlayerHand &Table);
};

