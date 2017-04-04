/*********************************************************************

** Author: Brian Trang

** Date: 1/27/2017

** Description: Class defintions for the die class

*********************************************************************/
#include "Die.hpp"

Die::Die()			//default constructor six sided dice
{
	numSides = 6;
}

Die::Die(int num)		//custom die 
{
	numSides = num;
}


int Die::roll()				//roll a six sided dice for result
{
	
	
		int result;

		result = rand() % (numSides - 1 + 1) + 1;
		return result;
	
}

int Die::getSides()
{
	return numSides;
}


Die::~Die()
{
	
}
