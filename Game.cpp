#include "Game.hpp"
#include "Lounge.hpp"
#include "Bar.hpp"
#include "Item.hpp"
#include "Die.hpp"
#include <vector>
#include <stdio.h>
#include "Cardroom.hpp"
#include "Backhall.hpp"
#include "Vip.hpp"
#include <future>

Game::Game()
{
	//establish the Rooms
	entrance = new Entrance("Entrance");
	bar = new Bar("Bar");
	lounge = new Lounge("Lounge");
	cardRoom = new Cardroom("Cardroom");
	backhall = new Backhall("Back Hall");
	vip = new Vip("VIP");

	//creating paths
	entrance->setPath('w', lounge);			//entrance connects to lounge from up/down
	lounge->setPath('s', entrance);
	lounge->setPath('d', cardRoom);
	lounge->setPath('w', bar);
	bar->setPath('s', lounge);
	cardRoom->setPath('a', lounge);
	cardRoom->setPath('d', backhall);
	backhall->setPath('d', vip);
	backhall->setPath('a', cardRoom);
	vip->setPath('a', backhall);

	//creating user stats
	health = 50;
	playerLoc = entrance;
	gameOver = false;
	
	//seed die for combat
	srand(time(0));
	
}
Game::~Game()
{
	delete entrance;
	delete bar;
	delete lounge;
	delete cardRoom;
	delete backhall;
	delete vip;
}
void Game::decreaseHealth()
{
	health--;
}

void Game::addToBackPack(Item i)
{
	backPack.push_back(i);
	itemCount++;
}

void Game::displayBackPack()
{
	if (itemCount == 0)
	{
		std::cout << "Nothing to display.\n";
		return;
	}
	for (int i = 0; i < itemCount; i++)
	{
		
		std::cout << std::endl;
		std::cout << backPack[i].getName() << std::endl;
		std::cout << backPack[i].getDescription() << std::endl;
	}
}
//remove item from backpack
void Game::removeItem(std::string n)
{
	for(int i =0; i<backPack.size();i++)
	{
		if (backPack[i].getName() == n)
		{
			backPack.erase(backPack.begin() + i);
			itemCount--;
		}
	}
	
}
//getter for health
int Game::getHealth()
{
	return health;
}

void Game::setHealth(int c)
{
	health = c;
}

void Game::adjustHealth(int d)
{
	int currentStrength;
	

	currentStrength = this->getHealth() - d;

	this->setHealth(currentStrength);


}
//gameplay sequence for the entire game
void Game::logic()
{
	Item bat("bat", "is a oak wooden bat, with a nice varnish finish");
	Item voucher("voucher", "it is a ticket for a free drink at the bar");
	Item drink("martini", "is an alcoholic drink");
	Item key("key", "is a shiny key");
	Item pokerChip("poker chip", "a plastic chip, says La Belle Luna on the back");
	Item envelope("envelope", "given by the lady, she told you not to open it, it smells nice");
	char userValue;
	bool fightPeter=false;			//determines if you face peter or speakeasy boss for final battle


	std::cout << "Welcome to the game The House Always Wins.\n";
	std::cout << "----------------------------------------------\n\n";
	std::cout << "Your drunk friend called you while intoxicated, unaware of where he is.\n";
	std::cout << "You decided to try to find him at the local speakeasy La Belle Luna.\n\n";
	std::cout << "OBJECTIVE: FIND YOUR FRIEND.\n";

	do
	{
		//display current location
		playerLoc->settingDescription();

		//start room sequence
		userValue = playerLoc->sequence();
		
		clearScreen();
		//controls
		switch(userValue)
		{//go north
		case 'w':
		{
			playerLoc = playerLoc->getNorth();
			decreaseHealth();
			break;
		}//go west
		case'a':
			{
			playerLoc = playerLoc->getWest();
			decreaseHealth();
			break;
			}
			//go south
		case 's':
			{
			playerLoc = playerLoc->getSouth();
			decreaseHealth();
			break;
			}
		case 'd':
			{
			playerLoc = playerLoc->getEast();
			decreaseHealth();
			break;
			}//check backpack
		case'b':
			{
			std::cout << "Displaying backpack.\n";
			this->displayBackPack();
			decreaseHealth();
			break;
			}//activate events
		case'e':
			{
				if(playerLoc==lounge)//speak to hostess
				{
					char ratChoice;
					std::cout << "Hey fella, you look like a nice guy.\n";
					std::cout << "You mind doing me a favor?\n\n";
					std::cout << "Do you want to help the hostess?\n";
					std::cout << "(enter y or n )\n";
					std::cin >> ratChoice;
					while(ratChoice !='y'&& ratChoice!='n')
					{
						std::cout << "Please enter a valid choice.\n";
						std::cin >> ratChoice;
					}
					clearScreen();
					if(ratChoice=='y')
					{
						std::cout << "\nThanks pal, see that rat over there? Make him sleep with the fishes.\n";
						playerLoc->setSpokeHostess(true);
						decreaseHealth();
					}
					else if(ratChoice=='n')
					{
						std::cout << "C'mon pal, I will throw in a gift for ya. If you change your mind, come see me.\n";
						decreaseHealth();
					}
					break;
				}//peanuts at bar
				else if(playerLoc==bar && !playerLoc->getAtePeanuts())
				{
					std::cout << "You see a bowl of stale looking peanuts.\n";
					std::cout << "You eat some.\n";
					std::cout << "The crunch texture seems different..\n";
					std::cout << "You gain some health.\n";
					this->setHealth(this->getHealth()+gainHealth());
					playerLoc->setAtePeanuts(true);
					break;
				}
				if(playerLoc==bar && playerLoc->getAtePeanuts())
				{
					std::cout << "There are no more stale peanuts.\n";
					break;
				}	
				if(playerLoc==cardRoom && !playerLoc->getJackPot())
				{
					playerLoc->setJackPot(gambling());
					if(playerLoc->getJackPot())
					{
						std::cout << "You collect your poker chips.\n";
						this->addToBackPack(pokerChip);
					}
					break;
				}
				else if (playerLoc==cardRoom && playerLoc->getJackPot())
				{
					std::cout << "You already won the jackpot you addict.\n";
					std::cout << "You should probably go look for your friend.\n";
					break;
				}
				if(playerLoc==backhall && !playerLoc->getFirstDoorOpen())
				{
					std::cout << "You walk in on a group of mafioso gambling.\n";
					std::cout << "The rough you up.\n";
					Die *dPtr = new Die;

					int healthLoss;
					healthLoss = dPtr->roll();
					this->setHealth(this->getHealth() - healthLoss);
					std::cout << "You took " << healthLoss << " of damage.\n";
					std::cout << "They slam the door shut, you probably shouldn't bother them again.\n";
					playerLoc->setFirstDoorOpen(true);
					delete dPtr;
					break;
				}
				if(playerLoc==vip && !this->searchBackPack("key"))
				{
					clearScreen(); //trying to get better screen
					//activate boss battle				
					if(fightPeter && this->searchBackPack("envelope"))			//you fight peter and you talked to the lady in bar
					{
						hardPeterBattle();
						if(this->getHealth()>0)
						{
							std::cout << "you have defeated spectacles man.\n";
							std::cout << "You should never trust pretty women at the bar.\n";
							std::cout << "\nYOU SEE THAT KEY ON HIM said your friend?!\n";
							std::cout << "Grab it and lets go through that locked door in the back hall\n";
							std::cout << "You grab the KEY.\n";
							std::cout << "You should head back to the back hall.\n";
							playerLoc->west->setBeatBoss(true);
							this->addToBackPack(key);
							break;
						}
						break;
					}
					
					//don't fight peter
					else if(!fightPeter)
					{
						harderBossBattle();
						if (this->getHealth()>0)
						{
							std::cout << "you have defeated boss man.\n";
							std::cout << "You should never go to shady speakeasies.\n";
							std::cout << "\nYOU SEE THAT KEY ON HIM said your friend?!\n";
							std::cout << "Grab it and lets go through that locked door in the back hall\n";
							std::cout << "You grab the key.\n";
							std::cout << "You should head back to the back hall.\n";
							playerLoc->west->setBeatBoss(true);
							this->addToBackPack(key);
							break;
						}
						break;
					}
					
				}
				if (playerLoc == vip && this->searchBackPack("key"))
				{
					std::cout << "You found the key already.\n";
					break;
				}
			}//investigate events
		case 'i':
			{
				//entrance events
				if(playerLoc==entrance && !playerLoc->getBatFound())//if in entrance
				{
					
					std::cout << "You pick up the bat.\n";
					this->addToBackPack(bat);
					playerLoc->setBatFound(true);
					decreaseHealth();
					break;
				}
				else if(playerLoc==entrance && playerLoc->getBatFound())
				{
					std::cout << "You have the bat already.\n";
					decreaseHealth();
					break;
				}
				//bar events 
				if(playerLoc==bar && this->searchBackPack("voucher") &&!this->searchBackPack("martini"))	//didn't speak to lady in bar 
				{
					std::cout << "Greetings sir, welcome to the bar.\n";
					std::cout << "Ahhh, you have voucher, let me take that...\n";
					std::cout << "Hmmm? No I haven't seen a individual like that around here.\n";
					std::cout << "I say you should start asking around for your friend at the cardroom.\n";
					this->addToBackPack(drink);
					this->removeItem("voucher");
					decreaseHealth();
					break;
				}
				else if (playerLoc==bar && !this->searchBackPack(("voucher")))
				{
					std::cout << "You should get a drink voucher from the hostess in the lounge.\n";
					decreaseHealth();
					break;
				}
				if(playerLoc==bar && this->searchBackPack("martini"))
				{
					std::cout << "You are an alcoholic,\n";
					std::cout << "You should be looking for your friend.\n";
					decreaseHealth();
					break;
				}
			
				if(playerLoc==backhall && !playerLoc->getFoundFriend())
				{
					std::cout << "You open the third door.\n";
					std::cout << "You are in the VIP room. It looks like chaos in here.\n";
					std::cout << "Surrounded by litter and empty bottles of liquor, you see your friend passed out on the couch.\n";
					std::cout << "You try to wake him up.\n";

					if(this->searchBackPack("martini"))
					{
						this->removeItem("martini");
						std::cout << "You pour your alcoholic drink on your friend.\n";
						std::cout << "He wakes up coughing, uhh where am I...?\n";
						std::cout << "You explained the situation to him.\n";
						std::cout << "Oh my god... thanks for coming to get me, I just drank too much and...\n";
						std::cout << "*Heavy groaning*. My head is killing me, lets get out of here before I collapse.\n";
						playerLoc->setFoundFriend(true);
						break;
					}
					else if (!this->searchBackPack("martini"))
					{
						playerLoc->setFoundFriend(wakeFriend());
						if(!playerLoc->getFoundFriend())
						{
							std::cout << "Your friend is dead.\n";
							gameOver = true;
							break;
						}
						std::cout << "You found your friend, hungover but safe.\n";
						break;
					}
					break;
				}
				if(playerLoc==vip  &&!playerLoc->getSandwichAte())
				{
					std::cout << "**You grab the half bitten sandwich**.\n";
					std::cout << "Why do you always eat random food you find buddy, its simply not sanitary..\n";
					this->setHealth(this->getHealth() + gainHealth());
					playerLoc->setSandwichAte(true);
					break;
				}
				else if(playerLoc == vip  && playerLoc->getSandwichAte())
				{
					std::cout << "Lets get going pal,\n";
					std::cout << "Stop trying to eat old leftovers.\n";
					break;
				}
			}
		case 'n':			//npc events
			{
				if(playerLoc==lounge && !playerLoc->getRatDead() && !this->searchBackPack("bat") && playerLoc->getSpokeHostess())
				{
					std::cout << "The rat snarls at you\n";
					std::cout << "Perhaps you should had grab a weapon first.\n";
					std::cout << "Battle beginning!\n";
					this->ratBattle();
					if(playerLoc->getRatDead())
					{
						std::cout << "You have shattered your bat.\n";
						this->removeItem("bat");
					}
					decreaseHealth();
					break;
				}
				else if (playerLoc == lounge && !playerLoc->getRatDead() && this->searchBackPack("bat") && playerLoc->getSpokeHostess())
				{
					std::cout << "The rat glares at you\n";
					std::cout << "Lucky you have a bat...\n";
					std::cout << "Battle beginning!\n\n";
					this->ratBattle();
					if (playerLoc->getRatDead())
					{
						std::cout << "You have shattered your bat.\n";
						this->removeItem("bat");
					}
					decreaseHealth();
					break;
				}
				else if (playerLoc==lounge && playerLoc->getRatDead())
				{
					std::cout << "The rat is already dead.\n";
					std::cout << "You see splatters of blood everywhere\n";
					std::cout << "Everyone in the lounge is looking at you funny... (probably because you ate some random rodent off the ground..)\n";
					decreaseHealth();
					break;
				}
				if(playerLoc == lounge && !playerLoc->getSpokeHostess() && !playerLoc->getRatDead())
				{
					std::cout << "The rat glares at you.\n";
					decreaseHealth();
					break;

				}//bar events
				if(playerLoc==bar && !playerLoc->getSpokeLady() && this->searchBackPack("martini"))
				{
					std::cout << "\nHello there sugar, what brings you to the La Belle Luna?\n";
					std::cout << "Ahh looking for your friend, I haven't seen him around the bar unfortunately.\n";
					std::cout << "She leans in close to you nearly knocking over your drink,"<<" \nyou are such a strappling young lad. The men around here are animals.\n";
					std::cout << "You are taken back, you have never been so close to a beauty like this woman.\n";
					std::cout << "\nShe gives you a envelope.\n";
					std::cout << "Don't open it yet, its a surprise.\n";
					std::cout << "\nYou are simply speechless, the lady is simply stunning.\n";
					std::cout << "I will see you later darling, I have to head to the lady's room.\n";
					fightPeter = true;
					this->addToBackPack(envelope);

					decreaseHealth();
					playerLoc->setSpokeLady(true);
					break;
				}
				else if (playerLoc==bar && !playerLoc->getSpokeLady() && !this->searchBackPack("martini") )
				{
					std::cout << "You see a beautiful lady writing a letter of some sort, better not bother her.\n";
					break;
				}
				else if(playerLoc==bar && playerLoc->getSpokeLady() &&this->searchBackPack("martini"))
				{
					std::cout << "Ah the lady just left, she told me to send you her regards. You lucky lad.\n";
					break;
				}
				//didn't win jackpot yet
				if(playerLoc==cardRoom && !playerLoc->getJackPot() && !this->searchBackPack("martini"))
				{
					std::cout << "You see a spectacle man gambling.\n";
					std::cout << "He looks like he doesn't want to be bothered and is concentrating on the card game.\n";
					decreaseHealth();
					break;
				}
				
				else if(playerLoc == cardRoom && !playerLoc->getJackPot() && !this->searchBackPack("martini"))
				{
					std::cout << "You should join me for a quick game says the man in glasses.\n";
					break;
				}
				else if (playerLoc == cardRoom && !playerLoc->getJackPot() && this->searchBackPack("martini"))
				{
					std::cout << "You have drinks?\n";
					std::cout << "Join me for a game sir.\n";
					break;

				}
				else if(playerLoc==cardRoom && playerLoc->getJackPot() && !this->searchBackPack("martini"))
				{
					std::cout << "Awesome win sir, Mr. Jackpot you should grab us some drinks at the bar.\n";
					break;
				}
				else if(playerLoc == cardRoom && playerLoc->getJackPot() && this->searchBackPack("martini"))
				{
					std::cout << "Thanks for the drink.\n";
					std::cout << "The name's Peter Clover. What brings you to La Belle Luna?\n";
					std::cout << "Oh you're looking for him? Yeah I've seen him, he's in the VIP room,\n";
					std::cout << "he went crazy last night and got very drunk,\n";
					std::cout<< "the bodyguards had to restraint him.\n\n";
					this->removeItem("martini");
					if(this->searchBackPack("envelope"))
					{
						std::cout << "\nAfter taking a sip of the martini, Peter Clover starts choking.\n";
						std::cout << "The card dealer shouts in a panic, GET HELP ! HE's CHOKING!, GET HELP\n\n";
						std::cout << "\nWith the commotion pouring towards your table, you step out of the way.\n";
						std::cout << "You get a glimpse of Peter as you get out of the way, seeing a empty look in his eyes, foam pouring out of his mouth.\n ";
						playerLoc->setDeadPeter(true);
						fightPeter = false;
						break;
					}
					std::cout << "Looks like you should talk to the bodyguard to get access to the VIP room.\n";
					break;
				}//easier boss fight with die 8 instead of 6
				else if(playerLoc==vip && !this->searchBackPack("key"))
				{
					if (!fightPeter)
					{
						easierBossBattle();
						if (this->getHealth()>0)
						{
							std::cout << "you have defeated boss man.\n";
							std::cout << "You should never go to shady speakeasies.\n";
							std::cout << "\nYOU SEE THAT KEY ON HIM said your friend?!\n";
							std::cout << "Grab it and lets go through that locked door in the back hall\n";
							std::cout << "You grab the key.\n";
							std::cout << "You should head back to the back hall.\n";
							playerLoc->west->setBeatBoss(true);
							this->addToBackPack(key);
							break;
						}
					}
						
					else
					{
						easierPeterBattle();
						if (this->getHealth()>0)
						{
							std::cout << "you have defeated spectacles man.\n";
							std::cout << "You should never trust pretty women at the bar.\n";
							std::cout << "\nYOU SEE THAT KEY ON HIM said your friend?!\n";
							std::cout << "Grab it and lets go through that locked door in the back hall\n";
							std::cout << "You grab the KEY.\n";
							std::cout << "You should head back to the back hall.\n";
							playerLoc->west->setBeatBoss(true);
							this->addToBackPack(key);
							break;
						}
						break;
					}
						
				}
			}
		case 'f':			//finished events
			{
				if(playerLoc==lounge && playerLoc->getRatDead() && !this->searchBackPack("voucher"))
				{
					std::cout << "Wow Mister, take it easy on the rat... I just wanted you to kill it, not eat it!\n";
					std::cout << "Please take this drink voucher on us!  You can redeem it at the bar." 
					<<"\nWash that taste of rat down...\n";
					std::cout << "Your friend? hmm I have no idea... try asking around at the bar.\n";
					this->addToBackPack(voucher);
					decreaseHealth();
					break;

				}
				else if (playerLoc==lounge && playerLoc->getRatDead() && this->searchBackPack("voucher"))
				{
					std::cout << "I suggest you look for your friend at the bar.\n";
					break;
				}
		
			}
		case 'p':	//pending events
			{
				if(playerLoc==lounge && !playerLoc->getRatDead())
				{
					std::cout << "Uh buddy, the rat? As soon as you can please.\n";
					break;
				}
				if(playerLoc==cardRoom && this->searchBackPack("poker chip"))
				{
					char choice;
					std::cout << "You looking for HIM!? Oh my god he was trouble last night.\n";
					std::cout << "No you cannot see him, we locked him up in the VIP room to sober up. He was insane.\n\n";
					std::cout << "Do you want to bribe the guard? (y/n)\n";
					std::cin >> choice;
					while(tolower(choice) != 'y' && tolower(choice) !='n')
					{
						std::cout << "Please enter y or n \n";
						std::cin >> choice;
					}
					if(tolower(choice)=='y')
					{
						std::cout << "you hand over your winnings to the guard.\n\n";
						this->removeItem("poker chip");
						std::cout << "Wow you really care about your friend, here go on in, this totally makes up for last night's mess.\n";
						playerLoc->setBribeGuard(true);
						break;
					}
					else if(tolower(choice)=='n')
					{
						std::cout << "Stop wasting my time and get out of the way, I am not letting you into the back hall.\n";
						break;
					}
				}
				else if(playerLoc == cardRoom && !this->searchBackPack("poker chip"))
				{
					std::cout << "Step out of the way sir.\n";
					std::cout << "Back hall to the VIP room is currently restricted.\n";
					break;
				}
				if(playerLoc==backhall && !this->searchBackPack("key"))
				{
					std::cout << "The second door is locked.\n";
					std::cout << "You will need a key.\n";
					decreaseHealth();
					break;
				}
				else if(playerLoc==backhall && this->searchBackPack("key"))
				{
					std::cout << "You unlocked the door with the key you found.\n";
					gameOver = true;
					break;
				}
			}
		case 'q':		//quit events
			{
			gameOver = true;
			break;
			}

		}
		std::cout << "\n\n";
		std::cout << "PLAYER HAS " << this->getHealth() <<" health left"<< std::endl << std::endl;
		if(this->getHealth()<=0)
		{
			gameOver = true;
		}
	} while (this->getHealth() > 0 && !gameOver);

	//game endings

	if(gameOver && !playerLoc->getFoundFriend() &&this->getHealth()<=0)
	{
		std::cout << "You lose.\n";
		std::cout << "You didn't find your friend and he's probably dead.\n";
		std::cout << "You find yourself overcome with guilt and you just can't bear it any longer.\n";
		std::cout << "Thank you for playing The House Always Wins.\n";
	}
	if(gameOver && !playerLoc->getFoundFriend() && this->getHealth()>0)
	{
		std::cout << "Your friend is dead.\n";
		std::cout << "You have failed\n";
	}
	if(gameOver && playerLoc->getFoundFriend() && this->getHealth()>0)
	{
		std::cout << "You found your friend.\n";
		std::cout << "You win the game.\n";
		if(this->searchBackPack("envelope"))
		{
			std::cout << "You are at home.\n";
			std::cout << "You finally open that envelope at home.\n";
			std::cout <<"You start reading it.\n";
			std::cout << "\n If you're reading this sugar, sorry about poisoning your drink.\n";
			std::cout << "Sometimes being bad is too irresistible\n";
			std::cout << "You sigh a breathe of release as you didn't drink that martini after all.\n";
		}
	}
}

void Game::ratBattle()
{
	Die* dPtr= nullptr;
	Die* rPtr = new Die;
	int combat;
	int ratAttack;
	int ratHealth = 20;

	//determine player combat skill
	if(searchBackPack("bat"))
	{
		dPtr = new Die(10);

	}
	else
	{
		dPtr = new Die;
	}

	//fight until someone has zero health;
	do
	{
		combat = dPtr->roll();
		if(searchBackPack("bat"))
		{
			std::cout << "You swing your bat at the rat.. " << std::endl;
		}
		else
		{
			std::cout << "You try to stomp on the rat with your boot.\n";
		}

		if(combat<=2)		//rolls 1 or 2
		{
			std::cout << "You barely gaze the rat.\n\n";
			ratHealth -= combat;
			std::cout << "Rat now has " << ratHealth << " points of health.\n";
		}
		else if (combat<=4)	//rolls 3 or 4
		{
			std::cout << "You land a moderate blow on the rat.\n\n";
			ratHealth -= combat;
			std::cout << "Rat now has " << ratHealth << " points of health.\n";
		}
		else if(combat <=6) //rolls 5 or 6
		{
			std::cout << "Good strike! you did are busting that rat up.\n\n";
			ratHealth -= combat;
			std::cout << "Rat now has " << ratHealth << " points of health.\n";
		}
		else if(combat <=8)//rolls 7 or 8
		{
			std::cout << "Wow, what a strike, that rat should be nearly dead.\n\n";
			ratHealth -= combat;
			std::cout << "Rat now has " << ratHealth << " points of health.\n";
		}
		else
		{
			std::cout << "Wow, take it easy on the rat please...\n\n";
			ratHealth -= combat;
			std::cout << "Rat now has " << ratHealth << " points of health.\n";
		}

	
		ratAttack = rPtr->roll();
		if(ratAttack<=2)		//roll 2 or 1
		{
			std::cout << "Just a nibble, you should be fine.\n\n";
			this->adjustHealth(ratAttack);

		}
		else if (ratAttack<=4)			//roll 3 or 4
		{
			std::cout << "Ouch! He bit hard!\n\n";
			this->adjustHealth(ratAttack);
		}
		else if (ratAttack<=6)
		{
			std::cout << "VICIOUS CHOMP by the RAT! That is how you get the black plague....\n\n";
			this->adjustHealth(ratAttack);
		}
	} while (ratHealth > 0 && this->getHealth() > 0);

	if(ratHealth<=0)
	{
		std::cout << "You have defeated the foul rat.\n\n";
		playerLoc->setRatDead(true);
		std::cout << "You ate the rat to consume its strength.\n";
		std::cout << "The patrons in the lounge stare at you in absolute horror.\n";
		std::cout << "You don't care however because rat is your favorite meat.\n";
		std::cout << "The bones go crunch crunch crunch...\n";
		int healthGain = dPtr->roll();
		std::cout << "You have gain " << healthGain << " of health by consuming the rodent.\n";
		this->setHealth(this->getHealth() + healthGain);
		std::cout << "You now have " << this->getHealth() <<" health left."<< std::endl;
	}
	else if(this->getHealth()<=0)
	{
		std::cout << "You have no more health.\n";
		std::cout << "You lose.\n";
	}
	delete dPtr;
	delete  rPtr;
}

bool Game::gambling()
{
	bool win;
	Die * dPtr=new Die;
	int guess;
	int answer = dPtr->roll();
	std::cout << "You are gambling at the table.\n";
	std::cout << "You have to guess the number of the die roll (1-6).\n";
	//needs input validation
	std::cin >> guess;
	while (!std::cin)
	{
		std::cout << "You didn't enter an integer.\n";
		std::cin.clear();
		std::cin.ignore();
		std::cin >> guess;
	}
	while(guess<0 || guess >6)
	{
		std::cout << "Invalid guess. Choose again\n";
		std::cin >> guess;
	}
	if(guess==answer)
	{
		std::cout << "You guessed correctly.\n";
		win = true;
		delete dPtr;
		return win;
	}
	else if(guess<answer)
	{
		std::cout << "Your guess was too low.\n";
		std::cout << "Die was " << answer << std::endl;
		win = false;
		delete dPtr;
		return win;
	}
	else if(guess>answer)
	{
		std::cout << "Your guess was too high.\n";
		std::cout << "Die was " << answer << std::endl;
		win = false;
		delete dPtr;
		return win;
	}
	delete dPtr;
	return false;
	
}

bool Game::wakeFriend()
{
	Die * slap = new Die(10);
	Die * shake = new Die;
	int userInput;
	int wakeMeter=0;
	const int woke = 30;
	int friendHealth =10;
	std::cout << "You need to wake your friend up.\n";
	do
	{
		std::cout << "(1) Shake your friend.\n";
		std::cout << "(2) Slap your friend.\n";
		std::cin >> userInput;

		while (!std::cin)
		{
			std::cout << "You didn't enter an integer.\n";
			std::cin.clear();
			std::cin.ignore();
			std::cin >> userInput;
		}

		while (userInput<0 || userInput>2)
		{
			std::cout << "Please make a valid choice.\n";
			std::cin >> userInput;
		}
		switch(userInput)
		{
		case 1:
			{
			std::cout << "You chose to shake your friend.\n";
			int shakeResult;
			shakeResult = shake->roll();
				if(shakeResult <3)
				{
					std::cout << "He's not waking up after you shook him. Keep trying!\n";
					friendHealth--;
					break;
				}
				else
				{
					wakeMeter += shakeResult;
					std::cout << "He seems to be stirring in his slumber, keep trying to wake him up.\n";
					break;
				}
			}
		case 2:
			{
			std::cout << "You chose to slap your friend.\n";
			int slapResult;
			slapResult = slap->roll();
				if(slapResult<4)
				{
					std::cout << "***SLAP***\n";
					std::cout << "He's not waking up after you slapped him. You left a giant red welt on his face.\n";
					break;
				}
				else if(slapResult<=8)
				{
					std::cout << "***SLAP***\n";
					std::cout << "It's working! He is stirring in his slumber.\n";
					wakeMeter += slapResult;
					break;

				}
				if(slapResult>=9)
				{
					std::cout << "***SLAP***\n";
					std::cout << "That slap might have been to hard.. take it easy!\n";
					friendHealth -= 1;
					std::cout << "Your friend's remaining health: " << friendHealth << std::endl;
					break;
				}
			}
		}
	} while (wakeMeter < woke &&friendHealth>0);
	if(wakeMeter>=woke && friendHealth>0)
	{
		std::cout << "After much effort, your friend wakes up.\n";
		std::cout << "Oh my... where am I... **GROAN**\n";
		std::cout << "You came for me? You really are my best friend...\n";
		std::cout << "**Your friend slowly stands up**\n";
		std::cout << "Okay, I think I am ready, lets get going.\n";
		delete slap;
		delete shake;
		return true;
	}
	else
	{
		std::cout << "You freak out, your friend isn't waking up.\n";
		std::cout << "You feel for a pulse but you reel back horrified!\n";
		std::cout << "There is no pulse...\n";
		delete slap;
		delete shake;
		return false;
	}


		
}

bool Game::searchBackPack(std::string val)											
{
	for(int i = 0; i< backPack.size();i++)
	{
		if(backPack[i].getName()==val)
		{
			
			return true;
		}
	}
	return false;
}

int Game::gainHealth()
{
	Die * dPtr = new Die;
	int healthGain = dPtr->roll();
	std::cout << "You have gain " << healthGain << " of health by consuming the peanuts.\n";
	this->setHealth(this->getHealth() + healthGain);
	std::cout << "You now have " << this->getHealth() << std::endl;

	delete dPtr;
	return healthGain;
}

void Game::clearScreen()
{
	int i;

	for (i = 0; i < 25; i++)
		putchar('\n');
}

void Game::hardPeterBattle()
{
	int peterHealth = 25;
	int peterResult;
	int userResult;
	Die * peterDie = new Die;
	Die * userDie = new Die;

	std::cout << "While searching through the bottles.\n";
	std::cout << "You feel someone staring behind you.\n";
	std::cout << "So you take my money with the jackpot winning, your friend causes trouble, you have been a thorn in my back.\n";

	std::cout << "\n\nYou see that the man is the one you seen earlier with spectacles.\n";
	std::cout << "You don't know me, but people have been telling me that you were speaking to my wife in the bar.\n";
	std::cout << "\nSeeing the angry look behind the spectacles, you try to reassure the man in glasses that nothing happened.\n";
	std::cout << "That is a load of crap and I don't believe you or my hussy for a wife.\n";

	std::cout << "\nYou must defeat Peter.\n";

	do
	{
		userResult = userDie->roll();
		peterResult = peterDie->roll();
		if(userResult<3)
		{
			std::cout << "You throw a punch at peter and barely gaze him.\n";
			peterHealth -= userResult;
			std::cout << "Peter has " << peterHealth << " points of health left.\n";
		}
		else if(userResult<5)
		{
		std::cout << "\nYou land a good strke on Peter.\n";
		peterHealth -= userResult;
		std::cout << "Peter has " << peterHealth << " points of health left.\n";
		}
		else
		{
			std::cout << "\nYou crack Peter with a thunderous right.\n";
			peterHealth -= userResult;
			std::cout << "Peter has " << peterHealth << " points of health left.\n";
		}
		if(peterResult<3)
		{
			std::cout << "\nPeter barely gaze you.\n";
			this->setHealth(this->getHealth() - peterResult);
		}
		else if(peterResult<5)
		{
			std::cout << "\nPeter lands on the side of of your head, dazing you.\n";
			this->setHealth(this->getHealth() - peterResult);
		}
		else
		{
			std::cout << "\nPeter throws a bomb of a left hand at you, your legs become shakey.\n";
			this->setHealth(this->getHealth() - peterResult);
		}
		
	} while (peterHealth > 0 && this->getHealth() > 0);

	delete peterDie;
	delete userDie;
}

void Game::harderBossBattle()
{
	int bossHealth = 25;
	int bossResult;
	int userResult;

	Die * bossDie = new Die;
	Die * userDie = new Die;

	std::cout << "\nYou see a mafia looking boss behind you, he is the owner of this shady speakeasy.\n";
	std::cout << "I am not letting you walk out with the jackpot winnings after your friend trashes this place.\n";
	std::cout << "I hope you are ready for a fight.\n";

	std::cout << "\n\nYou must defeat the Speakeasy Boss.\n\n";

	do
	{
		userResult = userDie->roll();
		bossResult = bossDie->roll();
		if (userResult<3)
		{
			std::cout << "\nYou throw a punch at the boss and barely gaze him.\n";
			bossHealth -= userResult;
			std::cout << "\nBoss has " << bossHealth<< " points of health left.\n";
		}
		else if (userResult<5)
		{
			std::cout << "\nYou land a good strke on the Boss.\n";
			bossHealth -= userResult;
			std::cout << "\nBoss has " << bossHealth << " points of health left.\n";
		}
		else
		{
			std::cout << "\nYou crack Boss with a thunderous right.\n";
			bossHealth -= userResult;
			std::cout << "\nBoss has " << bossHealth << " points of health left.\n";
		}
		if (bossResult<3)
		{
			std::cout << "\nBoss barely gaze you.\n";
			this->setHealth(this->getHealth() - bossResult);
		}
		else if (bossResult<5)
		{
			std::cout << "\nBoss lands on the side of of your head, dazing you.\n";
			this->setHealth(this->getHealth() - bossResult);
		}
		else
		{
			std::cout << "\nBoss throws a bomb of a left hand at you, your legs become shakey.\n";
			this->setHealth(this->getHealth() -bossResult);
		}

	} while (bossHealth > 0 && this->getHealth() > 0);

	delete bossDie;
	delete userDie;
}

void Game::easierBossBattle()
{
	int bossHealth = 25;
	int bossResult;
	int userResult;

	Die * bossDie = new Die;
	Die * userDie = new Die(8);

	std::cout << "\nYou see a mafia looking boss behind you, he is the owner of this shady speakeasy.\n";
	std::cout << "I am not letting you walk out with the jackpot winnings after your friend trashes this place.\n";
	std::cout << "I hope you are ready for a fight.\n";

	std::cout << "\nYou must defeat the Speakeasy Boss.\n";

	do
	{
		userResult = userDie->roll();
		bossResult = bossDie->roll();
		if (userResult<3)
		{
			std::cout << "\nYou throw a punch at the boss and barely gaze him.\n";
			bossHealth -= userResult;
			std::cout << "\nBoss has " << bossHealth << " points of health left.\n";
		}
		else if (userResult<5)
		{
			std::cout << "\nYou land a good strke on the Boss.\n";
			bossHealth -= userResult;
			std::cout << "\nBoss has " << bossHealth << " points of health left.\n";
		}
		else
		{
			std::cout << "\nYou crack Boss with a thunderous right.\n";
			bossHealth -= userResult;
			std::cout << "\nBoss has " << bossHealth << " points of health left.\n";
		}
		if (bossResult<3)
		{
			std::cout << "\nBoss barely gaze you.\n";
			this->setHealth(this->getHealth() - bossResult);
		}
		else if (bossResult<5)
		{
			std::cout << "\nBoss lands on the side of of your head, dazing you.\n";
			this->setHealth(this->getHealth() - bossResult);
		}
		else
		{
			std::cout << "\nBoss throws a bomb of a left hand at you, your legs become shakey.\n";
			this->setHealth(this->getHealth() - bossResult);
		}

	} while (bossHealth > 0 && this->getHealth() > 0);

	delete bossDie;
	delete userDie;
}
void Game::easierPeterBattle()
{
	int peterHealth = 25;
	int peterResult;
	int userResult;
	Die * peterDie = new Die;
	Die * userDie = new Die(8);

	std::cout << "While searching through the bottles.\n";
	std::cout << "You feel someone staring behind you.\n";
	std::cout << "So you take my money with the jackpot winning, your friend causes trouble, you have been a thorn in my back.\n";

	std::cout << "\n\nYou see that the man is the one you seen earlier with spectacles.\n";
	std::cout << "You don't know me, but people have been telling me that you were speaking to my wife in the bar.\n";
	std::cout << "\nSeeing the angry look behind the spectacles, you try to reassure the man in glasses that nothing happened.\n";
	std::cout << "That is a load of crap and I don't believe you or my hussy for a wife.\n";

	std::cout << "\nYou must defeat Peter.\n";

	do
	{
		userResult = userDie->roll();
		peterResult = peterDie->roll();
		if (userResult<3)
		{
			std::cout << "You throw a punch at peter and barely gaze him.\n";
			peterHealth -= userResult;
			std::cout << "Peter has " << peterHealth << " points of health left.\n";
		}
		else if (userResult<5)
		{
			std::cout << "\nYou land a good strke on Peter.\n";
			peterHealth -= userResult;
			std::cout << "Peter has " << peterHealth << " points of health left.\n";
		}
		else
		{
			std::cout << "\nYou crack Peter with a thunderous right.\n";
			peterHealth -= userResult;
			std::cout << "Peter has " << peterHealth << " points of health left.\n";
		}
		if (peterResult<3)
		{
			std::cout << "\nPeter barely gaze you.\n";
			this->setHealth(this->getHealth() - peterResult);
		}
		else if (peterResult<5)
		{
			std::cout << "\nPeter lands on the side of of your head, dazing you.\n";
			this->setHealth(this->getHealth() - peterResult);
		}
		else
		{
			std::cout << "\nPeter throws a bomb of a left hand at you, your legs become shakey.\n";
			this->setHealth(this->getHealth() - peterResult);
		}

	} while (peterHealth > 0 && this->getHealth() > 0);

	delete peterDie;
	delete userDie;
}