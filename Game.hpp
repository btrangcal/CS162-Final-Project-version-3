#ifndef GAME_HPP
#define GAME_HPP

#include "Entrance.hpp"
#include"Room.hpp"
#include "vector"
#include "Item.hpp"
class Game
{
	Room * entrance;
	Room * bar;
	Room * lounge;
	Room * vip;
	Room * backhall;
	Room * cardRoom;

	//player attributes
	int health;
	std::vector <Item> backPack;
	const int maxItems = 3;
	int itemCount = 0;
	bool gameOver;
	Room *playerLoc;

	//items
	//creating items

public:
	Game();
	~Game();
	void logic();
	void decreaseHealth();
	void addToBackPack(Item i);
	void displayBackPack();
	void removeItem(std::string n);
	int getHealth();
	void setHealth(int);
	void adjustHealth(int d);
	int gainHealth();
	void clearScreen();
	void hardPeterBattle();
	void harderBossBattle();
	void easierBossBattle();
	void easierPeterBattle();
	//events
	void ratBattle();
	bool searchBackPack(std::string val);
	bool gambling();
	bool wakeFriend();
};
#endif