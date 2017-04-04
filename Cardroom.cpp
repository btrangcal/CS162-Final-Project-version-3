#include "Cardroom.hpp"
#include <iostream>

char Cardroom::sequence()
{
	int userInput;
	if(!this->getBribeGuard() && !this->getDeadPeter())	//bribed guard and no dead peter
	{
		std::cout << "You see people chatting and laughing.\n";
		std::cout << "You see a big band playing on the side.\n";
		std::cout << "A card dealer beckons you towards his table.\n";
		std::cout << "A man with spectacles is also at the table.\n";
		std::cout << "\nPlease make a selection below.\n";
		std::cout << "---------------------------------\n";
		std::cout << "(1) Talk to man with spectacles.\n";
		std::cout << "(2) Play the game at the table.\n";
		std::cout << "(3) Go to the Lounge.\n";
		std::cout << "(4) Check backpack.\n";
		std::cout << "(5) Go to back hall. There is a bodyguard in the way.\n";
		std::cout << "(6) Quit the game.\n";
	}
	else if(this->getBribeGuard() &&!this->getDeadPeter())	//no dead peter and bribed guard
	{
		std::cout << "You see people chatting and laughing.\n";
		std::cout << "You see a big band playing on the side.\n";
		std::cout << "A card dealer beckons you towards his table.\n";
		std::cout << "A man with spectacles is also at the table.\n";
		std::cout << "\nPlease make a selection below.\n";
		std::cout << "---------------------------------\n";
		std::cout << "(1) Talk to man with spectacles.\n";
		std::cout << "(2) Play the game at the table.\n";
		std::cout << "(3) Go to the Lounge.\n";
		std::cout << "(4) Check backpack.\n";
		std::cout << "(5) Go to back hall. \n";
		std::cout << "(6) Quit the game.\n";
	}
	else if (!this->getBribeGuard() && this->getDeadPeter())		//dead peter and no bribed guard
	{
		std::cout << "You see people gasping and yelling.\n";
		std::cout << "You see a big band looking at Peter on with worried expressions.\n";
		std::cout << "\nPlease make a selection below.\n";
		std::cout << "---------------------------------\n";
		std::cout << "(2) Play the game at the table.\n";
		std::cout << "(3) Go to the Lounge.\n";
		std::cout << "(4) Check backpack.\n";
		std::cout << "(5) Go to back hall. There is a bodyguard in the way.\n";
		std::cout << "(6) Quit the game.\n";
	}
	else if(this->getBribeGuard() && this->getDeadPeter())//dead peter and bribed guard
	{
		std::cout << "You see people gasping and yelling.\n";
		std::cout << "You see a big band looking at Peter on with worried expressions.\n";
		std::cout << "\nPlease make a selection below.\n";
		std::cout << "---------------------------------\n";
		std::cout << "(2) Play the game at the table.\n";
		std::cout << "(3) Go to the Lounge.\n";
		std::cout << "(4) Check backpack.\n";
		std::cout << "(5) Go to back hall. \n";
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

	while(userInput<0 || userInput>6)
	{
		std::cout << "Please make a valid choice.\n";
		std::cin >> userInput;
	}
if(!this->getBribeGuard())
{
	if (userInput == 1)
		return 'n';
	if (userInput == 2)
		return 'e';
	if (userInput == 3)
		return 'a';
	if (userInput == 4)
		return 'b';
	if (userInput == 5)
		return 'p';
	if (userInput == 6)
		return 'q';
}
 else if(this->getBribeGuard())
{
	 if (userInput == 1)
		 return 'n';
	 if (userInput == 2)
		 return 'e';
	 if (userInput == 3)
		 return 'a';
	 if (userInput == 4)
		 return 'b';
	 if (userInput == 5)
		 return 'd';
	 if (userInput == 6)
		 return 'q';
}

}

void Cardroom::settingDescription()
{
	std::cout << "You are at the Card room.\n";
}
