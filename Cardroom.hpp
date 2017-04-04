#ifndef CARDROOM_HPP
#define CARDROOM_HPP
#include "Room.hpp"

class Cardroom:public Room
{
public:
	Cardroom(std::string sv):Room(sv)
	{
		
	}
	
	char sequence();
	void settingDescription();
};
#endif
