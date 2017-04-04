#ifndef VIP_HPP
#define VIP_HPP
#
#include "Room.hpp"

class Vip:public Room
{
public:
	Vip(std::string sv) :Room(sv)
	{

	}
	char sequence();

	void settingDescription();
};
#endif
