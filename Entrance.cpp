#include "Entrance.hpp"

char Entrance::sequence()
{
	int userChoice;

	if(!batFound)
	{
		std::cout << "You see a wooden bat to your left against the wall.\n\n";
		std::cout << "Up ahead, you see the entrance to the La Belle Luna Speakeasy.\n\n";
		std::cout << "\nPlease make a selection below.\n";
		std::cout << "---------------------------------\n";
		std::cout << "(1) Grab the wooden bat.\n";
		std::cout << "(2) Go inside La Bella Luna.\n";
		std::cout << "(3) Check backpack.\n";
		std::cout << "(4) Quit the game\n";
		std::cout << "\n";
	}
	else if(batFound)
	{
		std::cout << "Up ahead, you see the entrance to the La Belle Luna Speakeasy.\n";
		std::cout << "Pick a command below.\n";
		std::cout << "(1) Grab the wooden bat.\n";
		std::cout << "(2) Go inside La Bella Luna.\n";
		std::cout << "(3) Check backpack.\n";
		std::cout << "(4) Quit the game\n";
		std::cout << "\n";
	}

	//needs input validation
	std::cin >> userChoice;

	//input validation
	while(!std::cin)
	{
		std::cout << "You didn't enter an integer.\n";
		std::cin.clear();
		std::cin.ignore();
		std::cin >> userChoice;
	}
	while(userChoice<1 || userChoice >4)
	{
		std::cout << "Please make a valid choice.\n";
		std::cin >> userChoice;
	}


	if (userChoice == 1)			//investigation options 
		return 'i';
	else if (userChoice == 2)		//go up
		return 'w';
	else if (userChoice == 3)
		return 'b';
	else if (userChoice == 4)
		return 'q';
}

void Entrance::settingDescription()
{
	
	std::cout << "You are currently in the " << this->name << "\n\n";
	
}
