#include "Lounge.hpp"
#include <iostream>

char Lounge::sequence()
{
	int userChoice;

	//rat is still alive and didn't speak to hostess
	if(!ratDead && !spokeHostess )
	{
		std::cout << "\nPlease make a selection below.\n";
		std::cout << "---------------------------------\n";
		std::cout << "(1) Talk to the hostess.\n";
		std::cout << "(2) Return to the entrance.\n";
		std::cout << "(3) Interact with the terrifying rat.\n";
		std::cout << "(4) Go to the card room.\n";
		std::cout << "(5) Go to the bar.\n";
		std::cout << "(6) Check the backpack.\n";
		std::cout << "\n";

		std::cin >> userChoice;

		while(userChoice<0 || userChoice>6)
		{
			std::cout << "Please pick a valid choice.\n";
			std::cin >> userChoice;
		}
		std::cout << "\n";

		if (userChoice == 1)
			return 'e';
		else if (userChoice == 2)
			return 's';
		else if (userChoice == 3)
			return 'n';
		else if (userChoice == 4)
			return 'd';
		else if (userChoice == 5)
			return 'w';
		else if (userChoice == 6)
			return 'b';
		

	}
	else if(!ratDead &&spokeHostess)		//if rat is not dead and you already spoke to hostess
	{
		std::cout << "\nPlease make a selection below.\n";
		std::cout << "---------------------------------\n";
		std::cout << "(1) Talk to the hostess.\n";
		std::cout << "(2) Return to the entrance.\n";
		std::cout << "(3) Interact with the terrifying rat.\n";
		std::cout << "(4) Go to the card room.\n";
		std::cout << "(5) Go to the bar.\n";
		std::cout << "(6) Check backpack.\n";
		std::cout << "(7) Quit the game.\n";
		std::cout << "\n";

		std::cin >> userChoice;

		while (userChoice<0 || userChoice>7)
		{
			std::cout << "Please pick a valid choice.\n";
			std::cin >> userChoice;
		}
		std::cout << "\n";

		if (userChoice == 1)
			return 'p';				//event pending
		else if (userChoice == 2)
			return 's';					//go south
		else if (userChoice == 3)
			return 'n';					//npc
		else if (userChoice == 4)
			return 'd';					//go east
		else if (userChoice == 5)			//go north
			return 'w';
		else if (userChoice == 6)
			return 'b';
		else if (userChoice == 7)
			return 'q';
	}
	else if(ratDead && spokeHostess)			//if rat is dead and hostess quest activated
	{

		std::cout << "\nPlease make a selection below.\n";
		std::cout << "---------------------------------\n";
		std::cout << "(1) Talk to the hostess.\n";
		std::cout << "(2) Return to the entrance.\n";
		std::cout << "(3) Interact with the dead rat.\n";
		std::cout << "(4) Go to the card room.\n";
		std::cout << "(5) Go to the bar.\n";
		std::cout << "(6) Check the backpack.\n";
		std::cout << "(7) Quit the game.\n";
		std::cout << "\n";

		std::cin >> userChoice;

		//input validation
		while (!std::cin)
		{
			std::cout << "You didn't enter an integer.\n";
			std::cin.clear();
			std::cin.ignore();
			std::cin >> userChoice;
		}
		while (userChoice<0 || userChoice>7)
		{
			std::cout << "Please pick a valid choice.\n";
			std::cin >> userChoice;
		}
		std::cout << "\n";

		if (userChoice == 1)
			return 'f';				//event finished
		else if (userChoice == 2)
			return 's';					//go south
		else if (userChoice == 3)
			return 'n';				//npc finished
		if (userChoice == 4)		//go east
			return 'd';
		if (userChoice == 5)
			return 'w';
		if (userChoice == 6)
			return 'b';
		if (userChoice == 7)
			return 'q';
	}

	//
}
