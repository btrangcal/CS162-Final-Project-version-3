#include "Vip.hpp"
#include <iostream>

char Vip::sequence()
{
	int userInput;
	std::cout << "You see yourself in the VIP room.\n";
	std::cout << "It is a mess in here.\n";
	std::cout << "You see a litter of glass liquor bottles and vomit on the carpet.\n";
	std::cout << "\nPlease make a selection below.\n";
	std::cout << "---------------------------------\n";
	std::cout << "(1) Search pile of bottles for your friend's stuff.\n";
	std::cout << "(2) Search the couch cushions for your friend's stuff.\n";
	std::cout << "(3) Eat friend's left over sandwich.\n";
	std::cout << "(4) Check back pack.\n";
	std::cout << "(5) Go to back hall.\n";
	std::cout << "(6) Quit the game.\n";

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

	if (userInput == 1)
		return 'e';
	if (userInput == 2)
		return 'n';
	if (userInput == 3)
		return 'i';
	if (userInput == 4)
		return 'b';
	if (userInput == 5)
		return 'a';
		if (userInput == 6)
			return 'q';
}

void Vip::settingDescription()
{
	std::cout << "You are at the " << this->getName() << std::endl;
}
