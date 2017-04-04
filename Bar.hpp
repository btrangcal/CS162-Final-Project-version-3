#ifndef BAR_HPP
#define BAR_HPP
#include "Room.hpp"

class Bar: public Room
{
public:
	Bar(std::string sv):Room(sv)
	{
		
	}
	char sequence();

	void settingDescription();
};
#endif