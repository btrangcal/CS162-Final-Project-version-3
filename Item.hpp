#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>

class Item
{
private: std::string name;
		 std::string description;

public:
	Item()
	{
		name = "";
		description = "";
	}
	Item(std::string n, std::string d)
	{
		name = n;
		description = d;
	}
	std::string getName();
	std::string getDescription();
	void setDescription(std::string);
};


#endif