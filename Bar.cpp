#include "Bar.hpp"
#include <iostream>

char Bar::sequence()
{
	int userInput;

	if(!spokeLady)	//didn't speak to lady yet
	{
		std::cout << "Please make a selection below.\n";
		std::cout << "---------------------------------\n";
		std::cout << "You take a step into that La Belle Luna Bar.\n";
		std::cout << "Cheap whiskey fills the air.\n";
		std::cout << "At the bar, you see a gorgeous woman at the bar, staring at you attentively.\n";
		std::cout << "(1) Redeem your drink.\n";
		std::cout << "(2) Talk to the Woman.\n";
		std::cout << "(3) Eat peanuts at the bar.\n";
		std::cout << "(4) Check backpack.\n";
		std::cout << "(5) Go to the lounge.\n";
		std::cout << "(6) Quit the game.\n";

		//needs validation
		
	}
	else
	{
		std::cout << "Please make a selection below.\n";
		std::cout << "---------------------------------\n";
		std::cout << "You take a step into that La Belle Luna Bar.\n";
		std::cout << "Cheap whiskey fills the air.\n";
		std::cout << "The lady is noticeably missing.\n";
		std::cout << "Please make a choice below.\n\n";
		std::cout << "(1) Redeem your drink.\n";
		std::cout << "(2) Talk to the bartender.\n";
		std::cout << "(3) Eat peanuts at the bar.\n";
		std::cout << "(4) Check backpack.\n";
		std::cout << "(5) Go to the lounge.\n";
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
	while(userInput<1 || userInput>6)
	{
		std::cout << "Please make a valid choice.\n";
		std::cin >> userInput;
	}
	
	if (userInput == 1)
		return 'i';
	if (userInput == 2)
		return 'n';
	if (userInput == 3)
		return 'e';
	if (userInput == 4)
		return 'b';
	if (userInput == 5)
		return 's';
	if (userInput == 6)
		return 'q';
	
}

void Bar::settingDescription()
{
	std::cout << "You are at the " << this->getName() << std::endl;
}

