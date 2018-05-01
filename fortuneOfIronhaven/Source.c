/*
Author: Anthony Robustelli
Game Title: Fortune of Ironhaven
Final Project for Programming in C
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct monster//struct for monsters
{
	char *monsterName;
	int strCheck;
	int intCheck;
	int dexCheck;
	int dmgMod;
	int monsterHP;
};

struct character//struct for player character
{
	char firstName[31];
	char lastName[31];
	char *Race;
	char *Class;
	int strPoints;
	int strMod;
	int intPoints;
	int intMod;
	int dexPoints;
	int dexMod;
	int playerHP;
};

struct character playerChar;//define the player character
int goldPieces = 0;//global variable used to keep score
int turnCount = 0;//tracks turns in the caves
int chestCount = 0;//tracks which riddle chest we are on
int highScore[10] = { 0 };//array for storing high scores
int eCaverncount = 0;//keeps track of how many empty caverns were found

int main(void)
{
	int playerRaceChoice;
	int playerClassChoice;
	int remPoints = 20;

	printf("+++++++++++++++++++++++++++++++++\n");
	printf("Welcome to Fortune of Ironhaven\nAuthor: Anthony Robustelli\n");
	printf("+++++++++++++++++++++++++++++++++\n\n\n");
	system("pause");
	printf("\nOur story begins...\n\n");
	system("pause");
	printf("\n*******\nYou are shuffling through a long line in front of the mouth\nof a large cave, the line moves towards a gated archway\nwhere you can see an older looking man dressed in a very \nofficial looking uniform.\n*******\n\n");
	system("pause");
	printf("\n(Official Looking Man): next, next, NEXT\n\n");
	system("pause");
	printf("\n(Official Looking Man): Hello traveler, I am the Immigration Officer, \nbefore I can approve your request of relocation, we have \nto go through a few questions for the town census.\n\n");
	system("pause");
	printf("\nImmigration Officer: what is your race?\n\t1 - Human\n\t2 - Elf\n\t3 - Orc\n\n");
	printf("Make your RACE choice: ");//player if prompted and chooses what Race they are (asthetics)
	scanf_s("%d", &playerRaceChoice);
	switch (playerRaceChoice)//each race leads to different dialogue
	{
	case 1: 
		playerChar.Race = "Human";
		printf("Immigration Officer: Ah yes, of course you are HUMAN, I just didn't want \nto make any assumptions, all sorts have come \nthrough here, you would not believe what I have seen!\n\n");
		break;
	case 2:
		playerChar.Race = "Elf";
		printf("Immigration Officer: Right, the pointy ears should have given it away,\nthen again, so many people have come through here\npointy ears are not really that rare anymore.\n\n");
		break;
	case 3:
		playerChar.Race = "Orc";
		printf("Immigration Officer: It must be this sunlight, I could not even see \nyour green skin...or those big mouth tusks, then again, \nI have seen so many people, it is hardly a surprise.\n\n");
		break;
	}
	system("pause");
	printf("\nImmigration Officer: OK, moving along, I see you are registered with \nthe Adventurers Guild, what class of adventurer have you \nregistered as?\n");//prompted for player class
	printf("\t1 - Wizard (+2 spell damage)\n\t2 - Ranger (+2 bow damage)\n\t3 - Warrior (+2 melee damage)\n");//classes do bonus damage on different attacks
	printf("Make your CLASS choice: ");
	scanf_s("%d", &playerClassChoice);
	switch (playerClassChoice)//class also leads to different dialogue outcomes
	{
	case 1:
		playerChar.Class = "Wizard";
		printf("\nImmigration Officer: So you are a Wizard, I was never much for spells and such\nI like a more direct approach, with none of that \nhand waving and such.\n\n");
		break;
	case 2:
		playerChar.Class = "Ranger";
		printf("\nImmigration Officer: Ah, a ranger, I thought your kind liked to keep to the\nforests or somewhere where firing arrows is easier, \nbut I suppose if you are good, the caverns will not be a challenge\nI prefer a nice sharp sword myself.\n\n");
		break;
	case 3:
		playerChar.Class = "Warrior";
		printf("\nImmigration Officer: Well now, a mighty Warrior, I remember my days scouring \nthe lands looking for work, all I needed was a sharp \nsword and a dry place to sleep, you will do fine here.\n\n");
		break;
	}
	system("pause");
	printf("\nImmigration Officer: And finally, I need your name.\n");
	printf("What is your first name: ");
	scanf_s("%s", playerChar.firstName, 30);//player enters their first and last name
	printf("What is your last name: ");
	scanf_s("%s", playerChar.lastName, 30);
	printf("Great! Everything seems to be in order, here is your immigration card\n");
	printf("======================================\n");//displays the players choices made so far
	printf("| DEPARTMENT OF IMMIGRATION\n");
	printf("| Name: %s %s\n", playerChar.firstName, playerChar.lastName);
	printf("| Race: %s\n", playerChar.Race);
	printf("| Class: %s\n", playerChar.Class);
	printf("| TOWN OF IRONHAVEN\n");
	printf("======================================\n");
	system("pause");
	printf("\nYou recieved your Immigration card!\n\n");
	goldPieces += 10;//immigration card is worth 10 GP so score is iterated
	printf("Immigration Officer: Enjoy your time in Ironhaven\n\n");
	printf("You press forward eager to explore the caverns.\n");
	system("pause");
	printf("\n\nBefore we can begin you must first set up your player stats.\n");
	printf("Here are your current stats:\n");
	printf("======================================\n");//player is prompted to choose their stat build
	printf("| STATS\n");
	printf("| Name: %s %s\n", playerChar.firstName, playerChar.lastName);
	printf("| Strength: 0    ROLL MOD: -5 \n");//each stat gives roll or damage modifiers depending on their value
	printf("| Intellect: 0    ROLL MOD: -5 \n");
	printf("| Dexterity: 0    ROLL MOD: -5 \n");
	printf("| Health Ponts: (3 + (Strength * 3))\n");
	printf("======================================\n");
	printf("You can allocate %d points between your three stats\n", remPoints);//player allocates the designated points
	printf("How many points will you put into strength: ");
	scanf_s("%d", &playerChar.strPoints);//modifiers are assigned in accordance to the point values on each stat
	if (playerChar.strPoints <= 2)
	{
		playerChar.strMod = -5;//lower point value can actually make things harder, but deciding which skill seems more necessary is important
	}
	else if (playerChar.strPoints == 3 || playerChar.strPoints == 4)
	{
		playerChar.strMod = -3;
	}
	else if (playerChar.strPoints == 5 || playerChar.strPoints == 6)
	{
		playerChar.strMod = 0;
	}
	else if (playerChar.strPoints == 7 || playerChar.strPoints == 8 || playerChar.strPoints == 9)
	{
		playerChar.strMod = 3;
	}
	else if (playerChar.strPoints == 10)
	{
		playerChar.strMod = 5;
	}
	else if (playerChar.strPoints > remPoints)//make sure the player doesn't try to allocate more points than available
	{
		printf("\nYou cannot allocate more points than there are available, try again\n");
		printf("How many points will you put into strength: ");
		scanf_s("%d", &playerChar.strPoints);
	}
	playerChar.playerHP = (3 + (playerChar.strPoints * 3));//HP value is created from strength with a minimum of 3 if a player is daring (or stupid) enough
	remPoints -= playerChar.strPoints;//the remaining points are always decremented
	printf("Remaining Points: %d\n", remPoints);
	printf("How many points will you put into intellect: ");
	scanf_s("%d", &playerChar.intPoints);
	if (playerChar.intPoints <= 2)
	{
		playerChar.intMod = -5;
	}
	else if (playerChar.intPoints == 3 || playerChar.intPoints == 4)
	{
		playerChar.intMod = -3;
	}
	else if (playerChar.intPoints == 5 || playerChar.intPoints == 6)
	{
		playerChar.intMod = 0;
	}
	else if (playerChar.intPoints == 7 || playerChar.intPoints == 8 || playerChar.intPoints == 9)
	{
		playerChar.intMod = 3;
	}
	else if (playerChar.intPoints == 10)
	{
		playerChar.intMod = 5;
	}
	else if (playerChar.intPoints > remPoints)
	{
		printf("\nYou cannot allocate more points than there are available, try again\n");
		printf("How many points will you put into intellect: ");
		scanf_s("%d", &playerChar.intPoints);
	}
	remPoints -= playerChar.intPoints;
	printf("Remaining Points: %d\n", remPoints);
	printf("How many points will you put into dexterity: ");
	scanf_s("%d", &playerChar.dexPoints);
	if (playerChar.dexPoints <= 2)
	{
		playerChar.dexMod = -5;
	}
	else if (playerChar.dexPoints == 3 || playerChar.dexPoints == 4)
	{
		playerChar.dexMod = -3;
	}
	else if (playerChar.dexPoints == 5 || playerChar.dexPoints == 6)
	{
		playerChar.dexMod = 0;
	}
	else if (playerChar.dexPoints == 7 || playerChar.dexPoints == 8 || playerChar.dexPoints == 9)
	{
		playerChar.dexMod = 3;
	}
	else if (playerChar.dexPoints == 10)
	{
		playerChar.dexMod = 5;
	}
	else if (playerChar.dexPoints > remPoints)
	{
		printf("\nYou cannot allocate more points than there are available, try again\n");
		printf("How many points will you put into dexterity: ");
		scanf_s("%d", &playerChar.dexPoints);
	}
	remPoints -= playerChar.dexPoints;
	printf("\nGood now your stats are all set.\n");
	printf("Here they are:\n");
	printf("======================================\n");
	printf("| STATS\n");
	printf("| Name: %s %s\n", playerChar.firstName, playerChar.lastName);
	printf("| Strenght: %d    ROLL MOD: %d \n", playerChar.strPoints, playerChar.strMod);
	printf("| Intellect: %d    ROLL MOD: %d \n", playerChar.intPoints, playerChar.intMod);
	printf("| Dexterity: %d    ROLL MOD: %d \n", playerChar.dexPoints, playerChar.dexMod);
	printf("| Health Ponts: %d\n", playerChar.playerHP);
	printf("======================================\n");
	system("pause");
	printf("\n\nNow we can go exploring into the caverns!\n");
	printf("You only have limited time in the caverns (20 turns)\n");
	printf("Make them count!\n\n");
	system("pause");
	printf("\n\nYou push forwards into the cave...\n\n");
	system("pause");
	randRoom();
	system("pause");

	return 0;
}

int actionRoll (void)//actions are compared against a 20 point range (closer to 20 = more success)
{
	srand(time(NULL));
	int roll = 1 + rand() % 20;
	return roll;
}

int modRoll(void)//modifiers are rolled against a 6 point range (the higher the number, the more modifier you get)
{
	srand(time(NULL));
	int mod = 1 + rand() % 6;
	return mod;
}

int randRoom(void)//randomly creates dungeon rooms to explore
{
	if (turnCount < 20)//runs as long as turn count is below or at 20
	{
		srand(time(NULL));
		int room = rand() % 10;

		printf("\n\nYou press onwards\n\n");
		turnCount++;
		printf("Turn Number: %d\n\n", turnCount);
		if (room <= 2)//common
		{
			emptyCavern();//function spawns a room that's empty, how uninteresting
		}
		else if (room == 3 || room == 4 || room == 5 || room == 6 || room == 7)//common
		{
			monsterCavern();//function to spawn room with a monster
		}
		else if (room == 8 || room == 9)//rare
		{
			trapChest();//function spawns a room with a trap treasure chest
		}
	}
	else//20 turns are up = end of game
	{
		gameOver();
	}
}

int emptyCavern(void)//empty caverns are just poor luck of the draw
{
	if (eCaverncount <= 3)//until you've visited 3 empty caverns
	{
		printf("\nYou come upon an empty cavern.\n");
		printf("It is pretty uninteresting.\n");
		printf("Honestly seems kind of lazy on some greater powers part.\n\n");
		eCaverncount++;//iterate the cavern count
		system("pause");
		printf("\n");
		randRoom();
	}
	else
	{
		printf("\nYou come upon an empty cavern.\n");//on your 4th empty cavern you get a gift
		printf("It is pretty uninteresting.\n");
		system("pause");
		printf("\nWait...you notice something on the ground.\n");
		printf("After a little digging, you found a dusty looking sack.\n");
		printf("You found gold coins in the sack, lucky day.\n");//maybe finding empty caverns isn't so bad
		printf("Found: 200 GP\n");
		goldPieces += 200;
		eCaverncount = 0;//cavern count is reset
		system("pause");
		printf("\n");
		randRoom();
	}
}

int monsterCavern(void)//creates the monster cavern room
{
	srand(time(NULL));
	printf("\n\nYou hear some low growling or maybe some scraping, you are unsure.\n");
	system("pause");
	printf("\n");//I like line spacing
	int fightChoice;
	int monsterType = rand() % 4;//a rand function randomly generates a monster with set stats
	if (monsterType == 0)
	{
		struct monster monster0;//the rand calls different monster structs
		monster0.monsterName = "Cave Spider";
		monster0.strCheck = 12;
		monster0.intCheck = 6;
		monster0.dexCheck = 10;
		monster0.dmgMod = 0;
		monster0.monsterHP = 7;
		printf("\nYou round the corner and spot a %s\n", monster0.monsterName);
		printf("Would you like to slay this creature and possibly gain some loot?\n");//a tempting offer is made, what will the player choose
		printf("YES = 1 || NO = 2\n");
		printf("Make your choice: ");
		scanf_s("%d", &fightChoice);
		if (fightChoice == 1)//player can choose to fight
		{
			itsAFight(monster0);
		}
		else if (fightChoice == 2)//or run
		{
			printf("\nThere is no shame in running, run to fight another day I suppose\n");
			printf("You sneak away and the %s did not notice\n\n", monster0.monsterName);
			system("pause");
			printf("\n");
			randRoom();
		}
		else if (fightChoice > 2)
		{
			printf("\nUhhhh... that is not a choice, how about you try again\n");//if player doesn't make a correct choice, it will ask again
			system("pause");
			printf("\n\nWould you like to slay this creature and possibly gain some loot?\n");
			printf("YES = 1 || NO = 2\n");
			printf("Make your choice: ");
			scanf_s("%d", &fightChoice);
		}
	}
	else if (monsterType == 1)
	{
		struct monster monster1;
		monster1.monsterName = "Cave Goblin";
		monster1.strCheck = 14;
		monster1.intCheck = 5;
		monster1.dexCheck = 6;
		monster1.dmgMod = 2;
		monster1.monsterHP = 10;
		printf("\nYou round the corner and spot a %s\n", monster1.monsterName);
		printf("Would you like to slay this creature and possibly gain some loot?\n");
		printf("YES = 1 || NO = 2\n");
		printf("Make your choice: ");
		scanf_s("%d", &fightChoice);
		if (fightChoice == 1)
		{
			itsAFight(monster1);
		}
		else if (fightChoice == 2)
		{
			printf("\nThere is no shame in running, run to fight another day I suppose\n");
			printf("You sneak away and the %s did not notice\n\n", monster1.monsterName);
			system("pause");
			printf("\n");
			randRoom();
		}
		else if (fightChoice > 2)
		{
			printf("\nUhhhh... that is not a choice, how about you try again\n");
			system("pause");
			printf("\n\nWould you like to slay this creature and possibly gain some loot?\n");
			printf("YES = 1 || NO = 2\n");
			printf("Make your choice: ");
			scanf_s("%d", &fightChoice);
		}
	}
	else if (monsterType == 2)
	{
		struct monster monster2;
		monster2.monsterName = "Undead Adventurer";
		monster2.strCheck = 11;
		monster2.intCheck = 14;
		monster2.dexCheck = 6;
		monster2.dmgMod = 1;
		monster2.monsterHP = 12;
		printf("\nYou round the corner and spot a %s\n", monster2.monsterName);
		printf("Would you like to slay this creature and possibly gain some loot?\n");
		printf("YES = 1 || NO = 2\n");
		printf("Make your choice: ");
		scanf_s("%d", &fightChoice);
		if (fightChoice == 1)
		{
			itsAFight(monster2);
		}
		else if (fightChoice == 2)
		{
			printf("\nThere is no shame in running, run to fight another day I suppose\n");
			printf("You sneak away and the %s did not notice\n\n", monster2.monsterName);
			system("pause");
			printf("\n");
			randRoom();
		}
		else if (fightChoice > 2)
		{
			printf("\nUhhhh... that is not a choice, how about you try again\n");
			system("pause");
			printf("\nWould you like to slay this creature and possibly gain some loot?\n");
			printf("YES = 1 || NO = 2\n");
			printf("Make your choice: ");
			scanf_s("%d", &fightChoice);
		}
	}
	else if (monsterType == 3)
	{
		struct monster monster3;
		monster3.monsterName = "Cave Lizard";
		monster3.strCheck = 10;
		monster3.intCheck = 10;
		monster3.dexCheck = 15;
		monster3.dmgMod = 0;
		monster3.monsterHP = 8;
		printf("\nYou round the corner and spot a %s\n", monster3.monsterName);
		printf("Would you like to slay this creature and possibly gain some loot?\n");
		printf("YES = 1 || NO = 2\n");
		printf("Make your choice: ");
		scanf_s("%d", &fightChoice);
		if (fightChoice == 1)
		{
			itsAFight(monster3);
		}
		else if (fightChoice == 2)
		{
			printf("\nThere is no shame in running, run to fight another day I suppose\n");
			printf("You sneak away and the %s did not notice\n\n", monster3.monsterName);
			system("pause");
			printf("\n");
			randRoom();
		}
		else if (fightChoice > 2)
		{
			printf("\nUhhhh... that is not a choice, how about you try again\n");
			system("pause");
			printf("\nWould you like to slay this creature and possibly gain some loot?\n");
			printf("YES = 1 || NO = 2\n");
			printf("Make your choice: ");
			scanf_s("%d", &fightChoice);
		}
	}
}

int itsAFight(struct monster x)//function used to create fight scenarios parsing the monster struct as an argument
{
	int monsterHP = x.monsterHP;
	int attack;

	printf("\n\nYou have chosen to attack the monster!\n");
	while (monsterHP > 0 && playerChar.playerHP > 0)
	{
		unsigned int plDmg;//placeholder for player damage value
		unsigned int msDmg;//placeholder for monster damage value
		printf("MONSTER HP: %d\tPLAYER HP: %d\n\n", monsterHP, playerChar.playerHP);
		printf("Choose to attack with 1: Melee 2: Bow and Arrow or 3: Magic\n");
		printf("your choice: ");
		scanf_s("%d", &attack);
		if (attack == 1)
		{
			printf("You swing your weapon at the beast\n");
			if ((actionRoll() + playerChar.strMod) > x.strCheck)//each attack characteristic is checked against a different monster stat vs your roll
			{
				plDmg = (modRoll() + playerChar.strMod);//damage is also calculated against appropriate stats
				printf("With a mighty hit you deal %d damage\n", plDmg);
				monsterHP -= plDmg;
				if (playerChar.Class == "Warrior")//classes give bonus damage with different attacks
				{
					printf("You dealt 2 extra damage for being a Warrior\n");
					monsterHP -= 2;//monster HP gets iterated down with each hit
				}
			}
			else
			{
				printf("You weapon makes a whooshing sound as it misses the beast\n");//or you can also miss completely
			}
		}
		else if (attack == 2)
		{
			printf("You knock an arrow and fire at the beast, aiming for something vital\n");
			if ((actionRoll() + playerChar.dexMod) > x.dexCheck)
			{
				plDmg = (modRoll() + playerChar.dexMod);
				printf("Your arrow hits the beast dealing %d damage\n", plDmg);
				monsterHP -= plDmg;
				if (playerChar.Class == "Ranger")
				{
					printf("You dealt 2 extra damage for being a Ranger\n");
					monsterHP -= 2;
				}
			}
			else
			{
				printf("Your arrow whooshes by as it misses the beast\n");
			}
		}
		else if (attack == 3)
		{
			printf("You wave your hands as you chant ancient words\n");
			if ((actionRoll() + playerChar.intMod) > x.intCheck)
			{
				plDmg = (modRoll() + playerChar.intMod);
				printf("With a burst of arcane light you deal %d damage\n", plDmg);
				monsterHP -= plDmg;
				if (playerChar.Class == "Wizard")
				{
					printf("You dealt 2 extra damage for being a Wizard\n");
					monsterHP -= 2;
				}
			}
			else
			{
				printf("The beast is struct by arcane light, but it does not seem to have affect\n");
			}
		}
		else
		{
			printf("Invalid choice\n");
			system("pause");
			printf("\nChoose to attack with 1: Melee 2: Bow and Arrow or 3: Magic\n");
			printf("your choice: ");
			scanf_s("%d", &attack);
		}
		printf("The %s lunges at you to attack\n", x.monsterName);
		system("pause");
		if ((actionRoll() + x.dmgMod) > playerChar.dexPoints)
		{
			msDmg = (modRoll() + x.dmgMod);
			printf("The monster strikes dealing %d damage to you\n", msDmg);
			playerChar.playerHP -= msDmg;
		}
		else
		{
			printf("You skillfully dodge an otherwise painful looking blow\n");
		}
		if (monsterHP <= 0)
		{
			printf("Congrats, you have beaten the monster!\n You spot a small satchel on the ground.\n");//if you win, you are rewarded with GOLD
			system("pause");
			printf("You pick it up and find 150 gold pieces inside for the taking\n");
			printf("*150 GP added to your inventory*");
			goldPieces += 150;
			randRoom();
		}
		else if (playerChar.playerHP <= 0)//if you die in battle, it's game over
		{
			gameOver();
		}
	}
}

int trapChest()//Creates three chest with different number riddles, type the wrong answer and you get damaged, the right answer gives you treasure
{
	int chest1;
	int chest2;
	int chest3;
	int chestDmg;
	if (chestCount == 0)
	{
		printf("You come across a dusty chest with an old 5 number dial\n");
		system("pause");
		printf("It reads: 1-3-5-7-blank\n");
		printf("Guess the next number to unlock this chest: ");
		scanf_s("%d", &chest1);
		if (chest1 == 9)
		{
			printf("You hear a loud CLANK and the chest swings open\n");
			system("pause");
			printf("\nYou find 500 gold pieces\n");
			goldPieces += 500;//yay gold
			chestCount = 1;
			randRoom();
		}
		else
		{
			chestDmg = modRoll();//chests use the modRoll function to calculate damage
			printf("You set your number, and a flash of light blinds you as you feel a seering pain\n");
			printf("You received %d damage\n", chestDmg);
			playerChar.playerHP -= chestDmg;//oh no it hurts
			system("pause");
			printf("You feel like you will probably see that chest again.\n");
			randRoom();
		}
	}
	if (chestCount == 1)
	{
		printf("You come across a dusty chest with an old 5 number dial\n");
		system("pause");
		printf("It reads: 1-4-blank-10-13\n");
		printf("Guess the next number to unlock this chest: ");
		scanf_s("%d", &chest2);
		if (chest2 == 7)
		{
			printf("You hear a loud CLANK and the chest swings open\n");
			printf("You find 1000 gold pieces\n");
			goldPieces += 1000;
			chestCount = 2;
			randRoom();
		}
		else
		{
			chestDmg = modRoll();
			printf("You set your number, and a flash of light blinds you as you feel a seering pain\n");
			printf("You received %d damage\n", chestDmg);
			playerChar.playerHP -= chestDmg;
			system("pause");
			printf("You feel like you will probably see that chest again.\n");
			randRoom();
		}
	}
	if (chestCount == 2)
	{
		printf("You come across a dusty chest with an old 5 number dial\n");
		system("pause");
		printf("It reads: 1-2-4-7-blank\n");
		printf("Guess the next number to unlock this chest: ");
		scanf_s("%d", &chest3);
		if (chest3 == 11)
		{
			printf("You hear a loud CLANK and the chest swings open\n");
			printf("You find 2000 gold pieces\n");
			goldPieces += 2000;//rewards increase with each chest opened
			chestCount = 3;
			randRoom();
		}
		else
		{
			chestDmg = modRoll();
			printf("You set your number, and a flash of light blinds you as you feel a seering pain\n");
			printf("You received %d damage\n", chestDmg);
			playerChar.playerHP -= chestDmg;
			system("pause");
			printf("You feel like you will probably see that chest again.\n");
			randRoom();
		}
	}
	if (chestCount == 3)//There are only three trap chests, after that, it's just empty caverns
	{
		emptyCavern();
	}
}

int gameOver(void)
{
	if (playerChar.playerHP <= 0)
	{
		printf("\n\nUh Oh, you have died\n");//game also end if you die
		printf("This is where your story ends...\n");
		printf("Thanks for playing\n");
		printf("Your final score was: %d GP\n\n", goldPieces);
		printf("HIGH SCORES\n");
		printf("*********************\n");
		printf("SCORE\tPLAYER\n");
		highScore[0] = goldPieces;
		printf("%d\t%s %s\n", highScore[0], playerChar.firstName, playerChar.lastName);
		for (int i = 1; i <= 10; i++)
		{
			for (int x = i + 1; x <= 10; x++)
			{
				if (highScore[x] > highScore[i])
				{
					int temp = highScore[i];
					highScore[i] = highScore[x];
					highScore[x] = temp;
				}
			}
			printf("%d\n", highScore[i]);
		}
	}
	else
	{
		printf("\n\nCongrats on making it through 20 turns\n");//game ends after 20 turns, high score displayed
		printf("Unfortunately this is where our story ends\n");
		printf("Thank you for playing\n");
		printf("Your final score was: %d GP\n\n", goldPieces);
		printf("HIGH SCORES\n");
		printf("*********************\n");
		printf("SCORE\tPLAYER\n");
		highScore[0] = goldPieces;
		printf("%d\t%s %s\n", highScore[0], playerChar.firstName, playerChar.lastName);
		for (int i = 1; i <= 10; i++)
		{
			for (int x = i+1; x <= 10; x++)
			{
				if (highScore[x] > highScore[i])//if statement sorts highscores in descending order
				{
					int temp = highScore[i];
					highScore[i] = highScore[x];
					highScore[x] = temp;
				}
			}

			printf("%d\n", highScore[i]);
		}
	}
}