#include "Item.hpp"

std::string Item::getName()
{
	return name;
}

std::string Item::getDescription()
{
	return description;
}

void Item::setDescription(std::string d)
{
	description = d;
}
