// Durak.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iterator>
#include <string>
#include <limits>
#include "Card.h"
#include "Windows.h"
#include "DeckInitialization.h"
#include "PlayerHand.h"

using namespace std;

void RoundMessage(Card card);


//	♥ ♣ ♦ ♠
int main()
{	
	setlocale(0, "");
	srand(static_cast<unsigned int>(time(NULL)));
	
	vector<Card> Deck(36);	//Вектор колоды
	vector<Card> Beated;	//Вектор для отбитых карт(Бито)

	//Классы руки карт ирока, компьютера и стола
	PlayerHand Player;
	PlayerHand AI;
	PlayerHand Table;
	
	int choice;						//Переменная для выбора карты
	bool Kick = false;				//флаг битой карты
	bool EndGame = false;			//флаг конца игры
	bool BEATED = false;
	int turn = 0;					//ход игры

	//Создание колоды
	DeckInitialization(Deck);		

	//Шафл колоды
	random_shuffle(Deck.begin(), Deck.end());

	//Выбор козырной карты
	{
		auto iter1 = Deck.begin();
		Card::CardSuiting Trump = Deck.at(12).getSuit();

		Deck.emplace_back(*(iter1+12));

		auto iter2 = Deck.begin();
		Deck.erase((iter2+12));

		cout << "Козырная карта это "<<endl; 
		Deck.back().CardImage(24);

		
		for_each(Deck.begin(), Deck.end(), [Trump](Card &card1)
		{
			if (card1.getSuit() == Trump)
				card1.setSuit(Card::CardSuiting::Trumps);
		});
	}
	
	
	//Раздача карт игроку и компьютеру
	for (int i = 0; i < 6; i++)
	{
		Player.TakingCard(Deck, 1);
		AI.TakingCard(Deck, 1);
	}
	Deck.shrink_to_fit();
	//Сортировка карт компьютера по пордяку(для удобства)
	sort(AI.getHand().begin(), AI.getHand().end(), []( Card &card1, Card &card2 )
	{
		return card1.getDenom() < card2.getDenom();
	});
	//проверка на наименьший козырь
	{
		int PlayerLow = 15, AILow = 15;
		//находим наименьший козырь у Игрока
		for (auto elem : Player.getHand())
		{
			if (elem.getSuit() == Card::CardSuiting::Trumps && elem.getDenom() < PlayerLow)
				PlayerLow = elem.getDenom();
		}
		//находим наименьший козырь у Компьютера
		for (auto elem : AI.getHand())
		{
			if (elem.getSuit() == Card::CardSuiting::Trumps && elem.getDenom() < AILow)
				AILow = elem.getDenom();
		}

		if (AILow < PlayerLow)
		{
			turn = 1;
			cout << "Компьютер ходит первым, так как у него меньший козырь." << endl;
		}
		else if (AILow > PlayerLow)
		{
			turn = 0;
			cout << "Игрок ходит первым, так как у него наименьший козырь." << endl;
		}
		else if (AILow == PlayerLow)
		{
			turn = rand() % 2 + 1;
			cout << "У обоих игроков нет козырных карт, поэтому первый игрок выбирается случайно." << endl;
		}
	}

		while (EndGame == false)
		{
			RoundMessage(Deck.back());
			static int GameTurn = turn;
			if (GameTurn % 2 == 0)
			{
				//Ход игрока
				{
					cout << "Вот ваши карты: " << endl;
					Player.ShowHand();
					cout << "Какой картой вы хотите походить? " << endl;
					(cin >> choice).get();
					cin.sync();
					cin.clear();

					cout << "Вы положили на стол карту " << endl;
					Player.getHand().at(choice - 1).CardImage(choice);
					Player.TurningCard(Table, choice - 1);

				}
				//Компьютер отбивается
				{
					BEATED = false;
					while (BEATED == false)
					{
						Kick = false;
						
						for (int j = 0; j < AI.getHand().size(); j++)
						{
							if (AI.Analysis(Table, AI.getHand().at(j)) == true)		//Проверка, может ли карта побить карту на столе
							{
								cout << "Компьютер отбился картой " << endl;
								AI.getHand().at(j).CardImage(j + 1);

								//Перемещение отбитых карт в "Бито"
								Beated.emplace_back(AI.getHand().at(j));
								Beated.emplace_back(Table.getHand().front());

								Player.PlayerThrowUP(Table);
								AI.KickCard(j, Table);

								Kick = true;
								break;
							}
						}
						if (Kick == false)
						{
							cout << "Компьютер не может отбиться и забирает карты." << endl;
							Player.PlayerThrowUP(Table);
							while (Beated.size() != 0)
							{
								static int c = 0;
								Table.TakingCard(Beated, 1);
							}
							while(Table.getHand().size() != 0)
								AI.TakingCard(Table.getHand(), 1);		//забрать все карты со стола	
							GameTurn--;
						}
			
						if (!Table.getHand().size())
						{
							BEATED = true;
							Beated.clear();
						}
					}

				}

				GameTurn++;
			}
			else
			{
			//Ход компьютера(Выбор случайной карты)
				BEATED = false;
				{
					for (auto it = AI.getHand().begin(); it != AI.getHand().end(); it++)
					{
						choice = rand() % (AI.getHand().size());
						if (AI.getHand().at(choice).getSuit() == Card::CardSuiting::Trumps)
							choice = 0;
						else break;
					}
					cout << "Компьютер положил на стол карту" << endl;
					AI.getHand().at(choice).CardImage(choice + 1);
					AI.TurningCard(Table, choice);
				}
				{
					while (BEATED == false)
					{						
							string taking;
							//Kick = false;
							cout << "Вот ваши карты: " << endl;
							Player.ShowHand();
							//Выбор: брать карту домой или нет, если нет, то предлагается выбрать карту для отбития
							cout << "\nНапишите TAKE, если вы хотите взять карту домой, BEAT, если хотите отбиться." << endl;
							getline(cin, taking);

							if (taking == "TAKE")
							{
								//Player.TakingCard(Table.getHand(), 1);
								cout << "Игрок берёт карты домой." << endl;
								AI.AIThrowUP(Table);
								while (Beated.size() != 0)
								{
									static int c = 0;
									Table.TakingCard(Beated, 1);
								}
								while (Table.getHand().size() != 0)
									Player.TakingCard(Table.getHand(), 1);		//забрать все карты со стола	
								//Kick = true;
								BEATED = true;


								GameTurn--;
								break;
							}
							else if (taking == "BEAT")
							{
								cout << "Какой картой вы хотите отбиться? " << endl;
								(cin >> choice).get();
								//Проверить какой из методов работает
								cin.sync();
								cin.clear();
								if (Player.Analysis(Table, Player.getHand().at(choice - 1)) == true)
								{
									cout << "Вы отбили карту компьютера своей" << endl;
									//Перемещение отбитых карт в "Бито"
									Beated.emplace_back(Player.getHand().at(choice - 1));
									Beated.emplace_back(Table.getHand().front());

									AI.AIThrowUP(Table);
									Player.KickCard(choice - 1, Table);
								}
								else
									cout << "Этой картой отбиться не получится, выберите другую!" << endl;
								if (!Table.getHand().size())
								{
									BEATED = true;
									Beated.clear();
								}
							}
							else
								cout << "Неизвестная команда, подумайте ещё раз." << endl;
					}
				}

				GameTurn++;
			}
			//ДОБОР карты
			//Пока в руках меньше 6 карт и в колоде есть карты, каждый берёт по одной
			while (Deck.size() != 0 && (Player.getHand().size() < 6 || AI.getHand().size() < 6))
			{
				if (Player.getHand().size() < 6)
				{
					Player.TakingCard(Deck, 1);
					cout << "Игрок добирает карту" << endl;
					Player.getHand().back().CardImage(Player.getHand().size());
				}
				if (AI.getHand().size() < 6)
				{
					AI.TakingCard(Deck, 1);
					//cout << "Компьютер добирает карту" << endl;
				}
			}
			if (Deck.size() == 0 && (Player.getHand().size() == 0 || AI.getHand().size() == 0))
				EndGame = true;
		}

		{
		if (Player.getHand().size() == 0 && AI.getHand().size() != 0)
			cout << "Поздравляем вы победили!!!" << endl;
		else cout << "К сожалению, вы проиграли(" << endl;
		}
	
	
	return 0;
}

void RoundMessage(Card card)
{
	static int round = 1;
	static char sign = card.SuitImage;
	for (int i = 0; i < 45; i++)
		cout << "_";
	cout <<"\n"<< round++ << "-ый кон" << endl;

	cout << "Козырная масть - " << sign << endl<<endl;
}