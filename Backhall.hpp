#ifndef BACKHALL_HPP
#define BACKHALL_HPP
#include "Room.hpp"

class Backhall:public Room
{
public:
	Backhall(std::string sv):Room(sv)
	{
		
	}
	char sequence();

	void settingDescription();
};
#endif 
