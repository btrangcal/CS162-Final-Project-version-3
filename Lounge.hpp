#ifndef LOUNGE_HPP
#define LOUNGE_HPP
#include "Room.hpp"
#include <iostream>

class Lounge: public Room
{
public:
	Lounge(std::string sv): Room( sv)
	{
		
	}
	char sequence();
	void settingDescription()
	{
		std::cout << "You are at " << this->getName() << std::endl;
	}
};
#endif