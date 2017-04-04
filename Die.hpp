#ifndef DIE_HPP_
#define DIE_HPP_

#include <iostream>
#include <ctime>
#include <cstdlib>

class Die
{
protected: int numSides;		//number of sides for a dice
public: Die();
		Die(int);				//custom number of sides for dice
		virtual int roll() ;				//returns a result based on a roll
		virtual ~Die();
		virtual int getSides();
		

};

#endif
