#include "Backhall.hpp"
#include <iostream>

void Backhall::settingDescription()
{
	std::cout << "You are in the " << this->getName() << std::endl;
}
char Backhall::sequence()
{
	int userInput;
	if(!this->getFirstDoorOpen()&&!this->getFoundFriend())
	{
		std::cout << "You see a yourself in a dark hallway, in front of you you see 3 closed doors.\n";
		std::cout << "Behind you is the door back to the card room. \n ";
		std::cout << "Find the right door and find your friend.\n";
		std::cout << "\nPlease make a selection below.\n";
		std::cout << "---------------------------------\n";
		std::cout << "(1) Open first door.\n";
		std::cout << "(2) Open second door.\n";
		std::cout << "(3) Open third door.\n";
		std::cout << "(4) Return to cardroom.\n";
		std::cout << "(5) Check backpack.\n";
		std::cout << "(6) Quit the game.\n";
	}
	else if (this->getFirstDoorOpen() && !this->getFoundFriend())
	{
		std::cout << "You see a yourself in a dark hallway, in front of you you see 3 closed doors.\n";
		std::cout << "You definitely don't want to open the first door unless you want the gangsters \n";
		std::cout<< "to rail on you again.\n";
		std::cout << "Behind you is the door back to the card room.\n ";
		std::cout << "Find the right door and find your friend.\n";
		std::cout << "\nPlease make a selection below.\n";
		std::cout << "---------------------------------\n";
		std::cout << "(2) Open second door.\n";
		std::cout << "(3) Open third door.\n";
		std::cout << "(4) Return to cardroom.\n";
		std::cout << "(5) Check backpack.\n";
		std::cout << "(6) Quit the game.\n";
	}
	else if(this->getFirstDoorOpen() && this->getFoundFriend() && !this->getBeatBoss())
	{
		std::cout << "You see a yourself in a dark hallway, in front of you you see 3 closed doors.\n";
		std::cout << "You definitely don't want to open the first door unless you want the gangsters \n";
		std::cout << "to rail on you again.\n";
		std::cout << "Your friend is next to you, barely able to stand.\n";
		std::cout << "Hey buddy, can we go back into the VIP room? I need to grab my keys and wallet. I totally forgot them.\n";
		std::cout << "\nPlease make a selection below.\n";
		std::cout << "---------------------------------\n";
		std::cout << "(2) Open second door.\n";
		std::cout << "(3) Go back into VIP room.\n";
		std::cout << "(4) Return to card room.\n";
		std::cout << "(5) Check back pack.\n";
		std::cout << "(6) Quit the game.\n";
	}
	else if(!this->getFirstDoorOpen() && !this->getFoundFriend())
	{
		std::cout << "You see a yourself in a dark hallway, in front of you you see 3 closed doors.\n";
		std::cout << "Behind you is the door back to the card room. \n ";
		std::cout << "Find the right door and find your friend.\n";
		std::cout << "\nPlease make a selection below.\n";
		std::cout << "---------------------------------\n";
		std::cout << "(1) Open first door.\n";
		std::cout << "(2) Open second door.\n";
		std::cout << "(3) Go back into VIP room.\n";
		std::cout << "(4) Return to card room.\n";
		std::cout << "(5) Check back pack.\n";
		std::cout << "(6) Quit the game.\n";
	}
	else if(!this->getFirstDoorOpen() && this->getFoundFriend() &&!this->getBeatBoss())
	{
		std::cout << "Your friend is next to you, barely able to stand.\n";
		std::cout << "Hey buddy, can we go back into the VIP room? I need to grab my keys and wallet. I totally forgot them.\n";
		std::cout << "\nPlease make a selection below.\n";
		std::cout << "---------------------------------\n";
		std::cout << "(1) Open first door.\n";
		std::cout << "(2) Open second door.\n";
		std::cout << "(3) Go back into VIP room.\n";
		std::cout << "(4) Return to card room.\n";
		std::cout << "(5) Check back pack.\n";
		std::cout << "(6) Quit the game.\n";
	}
	else if(!this->getFirstDoorOpen() && this->getFoundFriend() && this->getBeatBoss())
	{
		std::cout << "\nWow what a fight. Let's get out of here through the back hall door.\n";
		std::cout << "\nPlease make a selection below.\n";
		std::cout << "---------------------------------\n";
		std::cout << "(1) Open first door.\n";
		std::cout << "(2) Open second door.\n";
		std::cout << "(3) Go back into VIP room.\n";
		std::cout << "(4) Return to card room.\n";
		std::cout << "(5) Check back pack.\n";
		std::cout << "(6) Quit the game.\n";
	}
	else if(this->getFirstDoorOpen() && this->getFoundFriend() && this->getBeatBoss())
	{
		std::cout << "\nWow what a fight. Let's get out of here through the back hall door.\n";
		std::cout << "\nPlease make a selection below.\n";
		std::cout << "---------------------------------\n";
		std::cout << "(2) Open second door.\n";
		std::cout << "(3) Go back into VIP room.\n";
		std::cout << "(4) Return to card room.\n";
		std::cout << "(5) Check back pack.\n";
		std::cout << "(6) Quit the game.\n";
	}

	std::cin >> userInput;

	while (!std::cin)
	{
		std::cout << "You didn't enter an integer.\n";
		std::cin.clear();
		std::cin.ignore();
		std::cin >> userInput;
	}

	while (userInput<0 || userInput>6)
	{
		std::cout << "Please make a valid choice.\n";
		std::cin >> userInput;
	}
	if(!this->getFirstDoorOpen() &&!this->getSecondDoorOpen() && !this->getFoundFriend())
	{
		if (userInput == 1)
			return 'e';
		if (userInput == 2)
			return 'p';
		if (userInput == 3)
			return 'i';
		if (userInput == 4)
			return 'a';
		if (userInput == 5)
			return 'b';
		if (userInput == 6)
			return 'q';
	}
	else if(!this->getFirstDoorOpen() && !this->getSecondDoorOpen() && !this->getFoundFriend())
	{
		if (userInput == 1)
			return 'e';
		if (userInput == 2)
			return 'p';
		if (userInput == 3)
			return 'i';
		if (userInput == 4)
			return 'a';
		if (userInput == 5)
			return 'b';
		if (userInput == 6)
			return 'q';
	}
	else if(this->getFirstDoorOpen() && !this->getSecondDoorOpen() && !this->getFoundFriend())
	{
		if (userInput == 2)
			return 'p';
		if (userInput == 3)
			return 'i';
		if (userInput == 4)
			return 'a';
		if (userInput == 5)
			return 'b';
		if (userInput == 6)
			return 'q';
	}
	else if (!this->getFirstDoorOpen() && this->getFoundFriend() && !this->getSecondDoorOpen())
	{
		if (userInput == 1)
			return 'e';
		if (userInput == 2)
			return 'p';
		if (userInput == 3)
			return 'd';
		if (userInput == 4)
			return 'a';
		if (userInput == 5)
			return 'b';
		if (userInput == 6)
			return 'q';
	}
	else if(this->getFirstDoorOpen() && this->getFoundFriend())
	{
		if (userInput == 2)
			return 'p';
		if (userInput == 3)
			return 'd';
		if (userInput == 4)
			return 'a';
		if (userInput == 5)
			return 'b';
		if (userInput == 6)
			return 'q';
	}
	
}

