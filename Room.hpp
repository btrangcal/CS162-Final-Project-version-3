#ifndef ROOM_HPP
#define ROOM_HPP
#include <string>
class Room
{
protected:
	//entrance
	bool batFound;

	//lounge
	bool spokeHostess;
	bool ratDead;

	//cardroom
	bool pokerChipFound;
	bool jackpot;
	bool bribeGuard;
	bool deadPeter;

	//bar
	bool spokeLady;
	bool atePeanuts;

	//backhall
	bool firstDoorOpen;
	bool secondDoorOpen;
	bool thirdDoorOpen;

	//vip
	bool foundFriend;
	bool vipKeyFound;
	bool sandwichAte;
	bool beatBoss;
	
	std::string name;

public:
	Room(std::string n);
	virtual char sequence() = 0;				//game sequence for room
	virtual void settingDescription() = 0;		//setting description

	//directional pointers
	//direction
	Room * north;
	Room * south;
	Room * west;
	Room * east;
	//setters
	void setPath(char way, Room * loc);
	void setBatFound(bool b)
	{
		this->batFound = b;
	}
	void setRatDead(bool b)
	{
		this->ratDead = b;
	}
	void setPokerChipFound(bool b)
	{
		this->pokerChipFound = b;
	}
	void setVIPkeyFound(bool b)
	{
		this->vipKeyFound = b;
	}

	void setSpokeHostess(bool b)
	{
		this->spokeHostess = b;
	}
	//bar states
	void setSpokeLady(bool b)
	{
		this->spokeLady = b;
	}
	void setAtePeanuts(bool b)
	{
		this->atePeanuts = b;
	}
	//card room states
	void setJackPot(bool b)
	{
		this->jackpot = b;
	}
	void setBribeGuard(bool b)
	{
		this->bribeGuard = b;
	}
	void setFoundFriend(bool b)
	{
		this->foundFriend = b;
	}
	void setDeadPeter(bool b)
	{
		this->deadPeter = b;
	}
	//backhall states
	void setFirstDoorOpen(bool b)
	{
		this->firstDoorOpen = b;
	}
	void setSecondDoorOpen(bool b)
	{
		this->secondDoorOpen = b;
	}
	void setThirdDoorOpen(bool b)
	{
		this->thirdDoorOpen = b;
	}
	void setSandwichAte(bool b)
	{
		this->sandwichAte = b;
	}
	void setBeatBoss(bool b)
	{
		this->beatBoss = b;
	}

	//vip states
	bool getSandwichAte()
	{
		return sandwichAte;
	}
	bool getBeatBoss()
	{
		return beatBoss;
	}
	//getters
	Room * getNorth()
	{
		return north;
	}
	Room * getSouth()
	{
		return south;
	}
	Room * getWest()
	{
		return west;
	}
	Room* getEast()
	{
		return east;
	}
	bool getBatFound()
	{
		return batFound;
	}
	bool getRatDead()
	{
		return ratDead;
	}
	bool getSpokeLady()
	{
		return spokeLady;
	}
	bool getSpokeHostess()
	{
		return spokeHostess;
	}
	bool getAtePeanuts()
	{
		return atePeanuts;
	}
	bool getJackPot()
	{
		return jackpot;
	}
	bool getBribeGuard()
	{
		return bribeGuard;
	}
	bool getDeadPeter()
	{
		return deadPeter;
	}
	bool getFirstDoorOpen()
	{
		return firstDoorOpen;
	}
	bool getSecondDoorOpen()
	{
		return secondDoorOpen;
	}
	bool getThirdDoorOpen()
	{
		return thirdDoorOpen;
	}
	bool getFoundFriend()
	{
		return foundFriend;
	}
	std::string getName();
};
#endif