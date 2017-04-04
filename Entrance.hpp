//needs description


#ifndef ENTRANCE_HPP
#define ENTRANCE_HPP
#include "Room.hpp"
#include <iostream>
class Entrance : public Room
{

public:
	Entrance(std::string sv):Room( sv)
	{
		
	}
	char sequence();
	void settingDescription();
};
#endif

