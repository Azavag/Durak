#include "PlayerHand.h"
#include "Card.h"
#include <vector>
#include <iostream>
#include <string>

vector<Card>  &PlayerHand::getHand()	{ return Hand; }

//�������� ���������
//������ ����� �� ������(number ��� ���������� �������� (���������� ������)
void PlayerHand::TakingCard(std::vector<Card> &deck, int number)
{
	auto iter = deck.begin();
	advance(iter, number - 1);

	Hand.emplace_back(*iter);   
	deck.erase(iter);
}

//��� ������
void PlayerHand::TurningCard(PlayerHand &OtherHand, int number)
{
	auto iter = Hand.begin();
	advance(iter,number);
	OtherHand.Hand.emplace_back(*iter);
	Hand.erase(iter);
}
//�������� ��� ���� ����
void PlayerHand::ShowHand()
{
	int count = 1;
	for (auto elem : Hand)
	{	
		elem.CardImage(count);
		++count;
	}
}

//�������� �� ����������� ������� ����� (table - ����� �� �����, card - �����, ������� ���������)		!!!!!!�������� ������ � ��������� �������
bool PlayerHand::Analysis(PlayerHand table, Card card) //���� ���� ���������� � �������� ����� �����
{	//���� ����� ��������� ����� ��������� � ������ ����� �� ����� � � ������� ������ ��� ��������� ����� ������
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
//������� �����
void PlayerHand::KickCard(int number, PlayerHand &table)		//number - ����� ����� �� ����, table - ������ ������(�� ����� �� ���������)
{
	auto iter = this->Hand.begin();
	iter += number;
	Hand.erase(iter);
	table.getHand().erase(table.getHand().begin());
}
//������� ������������ � ������
void PlayerHand::PlayerThrowUP(PlayerHand &Table)
{	
	string answer;
	int i = 0;
	for (auto elem : this->getHand())
	{
		if (elem.getDenom() == Table.getHand().front().getDenom())
		{
				cout << "�� ������ ��������� ����� ���������."<<endl;
				elem.CardImage(i + 1);
				cout << "������� YES ��� NO." << endl;
				getline(cin, answer);
				if (answer == "YES")
				{
					this->TurningCard(Table, i);
					cout << "�� ��������� ����� ���������." << endl;
				}
				else if (answer == "NO")
					cout << "�� ���������� ����� � ����." << endl;
				break;
		}
		i++;
	}
}
//������� ��� ������������ � ��
void PlayerHand::AIThrowUP(PlayerHand &Table)
{
	int i = 0;
	for (auto elem : this->getHand())
	{
		if (elem.getDenom() == Table.getHand().front().getDenom() && elem.getSuit() != Card::CardSuiting::Trumps)
		{
			cout << "��������� ����������� ��� �����." << endl;
			elem.CardImage(i + 1);
			this->TurningCard(Table, i);
			break;
		}
		i++;
	}
}
