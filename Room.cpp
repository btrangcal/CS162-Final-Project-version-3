#include "Room.hpp"

Room::Room(std::string n)
{
	//allocate one of the room names to the name field
	if (n == "Entrance")
		this->name = n;
	else if (n == "Lounge")
		this->name = n;
	else if (n == "CardRoom")
		this->name = n;
	else if (n == "Bar")
		this->name = n;
	else if (n == "Back Hall")
		this->name = n;
	else if (n == "VIP")
		this->name = n;

	//set pointers to null
	this->north = nullptr;
	this->south = nullptr;
	this->west = nullptr;
	this->east = nullptr;

	//set objectives to false
	this->batFound = false;
	this->ratDead = false;
	this->pokerChipFound = false;
	this->vipKeyFound = false;
	this->spokeHostess = false;
	this->spokeLady = false;
	this->atePeanuts = false;
	this->bribeGuard = false;
	this->foundFriend = false;
	this->firstDoorOpen = false;
	this->secondDoorOpen = false;
	this->thirdDoorOpen = false;
	this->sandwichAte = false;
	this->beatBoss = false;
}

void Room::setPath(char way, Room * loc)
{
	char input;

	input = tolower(way);

	if (input == 'w')
		this->north = loc;
	else if (input == 's')
		this->south = loc;
	else if (input == 'a')
		this->west = loc;
	else if (input == 'd')
		this->east = loc;
}

std::string Room::getName()
{
	return name;
}
