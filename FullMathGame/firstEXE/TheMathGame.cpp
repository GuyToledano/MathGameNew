#include "GameManager.h"
#include "TheMathGame.h"
#include "io_utils.h"
#include "Equation.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
using namespace std;

//TODO: create function "levelDone. it will free the equasions

//TODO: style the instructions a bit
void TheMathGame::showInstructions()const
{
	clear_screen();
	//gotoxy(40, 10);
	cout << "each player gets a math problem, ";
	//gotoxy(20, 11);
	cout << "use the following keys to move and collect the correct answer." << endl;
	gotoxy(20, 5);
	cout << "Player| #1:      |         #2:" << endl;
	gotoxy(20, 5);
	cout << "Up    |  W       |          I" << endl;
	gotoxy(20, 5);
	cout << "down  |  X       |          M" << endl;
	gotoxy(20, 5);
	cout << "Left  |  A       |          J" << endl;
	gotoxy(20, 5);
	cout << "right |  D       |          L" << endl << endl;

	cout << "press any key to go back to main menu";
	_getch();
	clear_screen();

}
// virtual fucnction with =0 is called an "abstract method"
// abstract method must be implemented by non-abstract inherited class
bool TheMathGame::isLevelDone()
{
	if (player1.getWinner() == true || player2.getWinner() == true)
		return true;

	return false;
}
bool TheMathGame::hasNextLevel(const unsigned int currentLevel)const
{
	if (currentLevel < LAST_LEVEL)
		return true;

	return false;
}
//TODO: create c'tor of TheMathGame to initiate both players
void TheMathGame::startLevel(const unsigned int currentLevel)
{
	clear_screen();

	this->player1 = Player('@', 10, 9, MOVE_RIGHT, STAY, 0, 3);
	this->player2 = Player('#', 70, 9, MOVE_LEFT, STAY, 0, 3);
	boardInit();
	setEquations(currentLevel);

	player1.setTargetNum(player1.getEquation()->getTargetNumber());
	player2.setTargetNum(player1.getEquation()->getTargetNumber());

	printframe(currentLevel);

	this->player1.showPlayer(10, 9);
	this->player2.showPlayer(70, 9);

}
void TheMathGame::setEquations(const unsigned int currentLevel)
{
	this->player1.setEquation(new Equation(currentLevel));
	this->player2.setEquation(new Equation(currentLevel));
}
void TheMathGame::printframe(const unsigned int currentLevel)
{
	Equation* eq1 = this->player1.getEquation();
	Equation* eq2 = this->player2.getEquation();
	eq1->printEquation(0, 0);
	eq2->printEquation(60, 0);
	player1.printlives(0, 1);
	player2.printlives(60, 1);
	gotoxy(8, 1);
	cout << "score: " << player1.getScore();
	gotoxy(68, 1);
	cout << "score: " << player2.getScore();
	gotoxy(36, 0);
	cout << "Level: " << currentLevel;
	gotoxy(0, 2);
	for (int i = 0; i < 80; i++)
		cout << "_";

}
// get a list with keyHits and returns a list with the keys that were used
void TheMathGame::doIteration(const list<char>& keyHits)
{
	char direction;
	int playerMove;
	bool gotDirectionForPlayer1 = false;
	bool gotDirectionForPlayer2 = false;

	for (list<char>::const_iterator itr = keyHits.cbegin();
		(itr != keyHits.cend()) && (gotDirectionForPlayer1 == false || gotDirectionForPlayer2 == false);
		++itr)
	{
		direction = *itr;
		if (isValid(direction))
		{
			playerMove = assignToPlayer(direction);

			if (playerMove == PLAYER_1 && gotDirectionForPlayer1 == false && player1.getLives() > 0)
			{
				gotDirectionForPlayer1 = true;
				this->player1.changeDirection(direction);
			}
			if (playerMove == PLAYER_2 && gotDirectionForPlayer2 == false && player2.getLives() > 0)
			{
				gotDirectionForPlayer2 = true;
				this->player2.changeDirection(direction);
			}
		}
	}
	generateNumber();
	didPlayersCollide();
	playerGetsNumber(player1);
	playerGetsNumber(player2);
	this->player1.move();
	this->player2.move();
}

//TODO: change the letters to defines
int TheMathGame::assignToPlayer(char direction)
{
	switch (direction)   //switch to check whisch button was pressed
	{
	case PLAYER_1_UP:
		return PLAYER_1;

	case PLAYER_1_RIGHT:
		return PLAYER_1;

	case PLAYER_1_LEFT:
		return PLAYER_1;

	case PLAYER_1_DOWN:
		return PLAYER_1;

	case PLAYER_2_UP:
		return PLAYER_2;

	case PLAYER_2_RIGHT:
		return PLAYER_2;

	case PLAYER_2_LEFT:
		return PLAYER_2;

	case PLAYER_2_DOWN:
		return PLAYER_2;
	}
	return 0;        //returns 0 as default if the keyboard hit didnt belong to neither one of the players
}
bool TheMathGame::isValid(char direction)
{
	return (assignToPlayer(direction) != 0);
}
void TheMathGame::doSubIteration()
{

}
/************************************************************************************************/
void TheMathGame::didPlayersCollide()
{
	if ((this->player1.getX() + this->player1.getDirx()) == (this->player2.getX() + this->player2.getDirx())
		&& (this->player1.getY() + this->player1.getDiry()) == (this->player2.getY() + this->player2.getDiry())
		&& (!(this->player1.isPlayerStationary() || this->player2.isPlayerStationary())))
	{
		this->player1.move();
		this->player1.setDirx(STAY);
		this->player2.setDirx(STAY);
		this->player1.setDiry(STAY);
		this->player2.setDiry(STAY);
	}
	else if (((this->player1.getX() + this->player1.getDirx() == this->player2.getX())
		&& (this->player2.getX() + this->player2.getDirx() == this->player1.getX())
		&& (this->player1.getY() == this->player2.getY()))
		|| ((this->player1.getY() + this->player1.getDiry() == this->player2.getY())
		&& (this->player2.getY() + this->player2.getDiry() == this->player1.getY())
		&& (this->player1.getX() == this->player2.getX())))
	{
		this->player1.setDirx(STAY);
		this->player2.setDirx(STAY);
		this->player1.setDiry(STAY);
		this->player2.setDiry(STAY);
	}

	else if (this->player1.isPlayerStationary())
	{
		if ((this->player2.getX() + this->player2.getDirx() == this->player1.getX()
			&& (this->player1.getY() == this->player2.getY()))
			|| (this->player2.getY() + this->player2.getDiry() == this->player1.getY()
			&& (this->player1.getX() == this->player2.getX())))
		{
			this->player1.setDirx(STAY);
			this->player2.setDirx(STAY);
			this->player1.setDiry(STAY);
			this->player2.setDiry(STAY);
		}

	}
	else if (this->player2.isPlayerStationary())
	{
		if ((this->player1.getX() + this->player1.getDirx() == this->player2.getX()
			&& (this->player2.getY() == this->player1.getY()))
			|| (this->player1.getY() + this->player1.getDiry() == this->player2.getY()
			&& (this->player2.getX() == this->player1.getX())))
		{
			this->player1.setDirx(STAY);
			this->player2.setDirx(STAY);
			this->player1.setDiry(STAY);
			this->player2.setDiry(STAY);
		}

	}
}

void TheMathGame::boardInit()
{
	for (int i = 0; i < BOARD_WITDH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
			numberBoard[i][j] = EMPTY_CELL;
	}
}
short int TheMathGame::getRandomNumber()
{
	short int number;

	number = rand() % (currentLevel + 10) + 1;

	return number;
}
void TheMathGame::generateNumber()
{
	short int number;
	int x, y;
	int offset;
	bool validPlace = false;
	int numOfAttempts = 0;

	number = getRandomNumber();
	offset = getNumOfDigits(number) - 1;
	do
	{
		x = rand() % (BOARD_WITDH - offset);
		y = rand() % (BOARD_HEIGHT)+3;
		numOfAttempts++;

	} while ((!isValidPlace(x, y, offset + 1)) && (numOfAttempts < 10));

	if (numOfAttempts != 10)
		updateBoard(x, y, number);

}
bool TheMathGame::isValidPlace(int x, int y, int numOfDigits)
{

	for (int i = 0; i < numOfDigits; i++)
	{
		if (numberBoard[x + i][y] != EMPTY_CELL)
			return false;

		if (numberBoard[x + i][y + 1] != EMPTY_CELL)
			return false;

		if (numberBoard[x + i][y - 1] != EMPTY_CELL)
			return false;
	}
	return !thereIsAPlayerInTheWay(x, y);
}
bool TheMathGame::thereIsAPlayerInTheWay(int x, int y)
{
	if (y == this->player1.getY() && x == this->player1.getX())
		return true;

	if (y == this->player1.getY() + 1 && x == this->player1.getX())
		return true;

	if (y == this->player1.getY() - 1 && x == this->player1.getX())
		return true;

	if (y == this->player1.getY() && x == this->player1.getX() + 1)
		return true;

	if (y == this->player1.getY() && x == this->player1.getX() - 1)
		return true;

	if (y == this->player2.getY() && x == this->player2.getX())
		return true;

	if (y == this->player2.getY() + 1 && x == this->player2.getX())
		return true;

	if (y == this->player2.getY() - 1 && x == this->player2.getX())
		return true;

	if (y == this->player2.getY() && x == this->player2.getX() + 1)
		return true;

	if (y == this->player2.getY() && x == this->player2.getX() - 1)
		return true;

	return false;
}
void TheMathGame::updateBoard(int x, int y, short int number)
{
	int numOfDigits;

	numberBoard[x][y] = number;
	numOfDigits = getNumOfDigits(number);
	for (int i = 1; i < numOfDigits; i++)
	{
		numberBoard[x + i][y] = number;
		numberBoard[x + i][y + 1] = DO_NOT_PLACE;
		numberBoard[x + i][y - 1] = DO_NOT_PLACE;
	}
	if (x != 0)
		numberBoard[x - 1][y] = DO_NOT_PLACE;

	numberBoard[x][y - 1] = DO_NOT_PLACE;
	numberBoard[x][y + 1] = DO_NOT_PLACE;
	numberBoard[x + numOfDigits][y] = DO_NOT_PLACE;

	gotoxy(x, y);
	cout << number;
}
int TheMathGame::getNumOfDigits(short int num)
{
	int count = 0;
	while (num > 0)
	{
		count++;
		num = num / 10;
	}
	return count;
}
void TheMathGame::playerGetsNumber(Player &p)
{
	if (isPlayerGetsNumber(p))
	{
		if (numberBoard[p.getX()][p.getY()] == p.getTargetNum())  // TODO: check if we can turn into a function
		{
			p.setWinner(true);
			removeNumberFromBoard(p.getX(), p.getY());
			p.setScore(p.getScore() + 1);
			printframe(currentLevel);
		}
		else
		{

			removeNumberFromBoard(p.getX(), p.getY());
			updateLives(p);
			if (p.getLives() <= 0) //if player is dead
			{
				removePlayerFromBoard(p);
			}

		}
		//TODO: if lives == 0 then player is dead. if both are dead, next level
	}


}
//TODO: disable movement 
void TheMathGame::removePlayerFromBoard(Player &p)
{
	p.setXY(OUT_OF_BOARD, OUT_OF_BOARD);
	p.erasePlayer(p.getX(), p.getY());
	p.setDirx(STAY);
	p.setDiry(STAY);

}
bool TheMathGame::isPlayerGetsNumber(Player &p) const
{
	int playerLocationX, playerLocationY;

	playerLocationX = p.getX();
	playerLocationY = p.getY();


	if (numberBoard[playerLocationX][playerLocationY] >= 0) //if lower than 0 it means that it is an empty cell or invalid cell
		return true;

	return false;
}

void TheMathGame::removeNumberFromBoard(int x, int y)
{
	int i = 0;
	while (numberBoard[x - i][y] != DO_NOT_PLACE && (x - i) != 0)
	{
		i++;
	}
	x = x - i;
	if (x == 0)
	{
		numberBoard[x][y + 1] = EMPTY_CELL;
		numberBoard[x][y - 1] = EMPTY_CELL;
		gotoxy(x, y);
		cout << " ";
	}
	numberBoard[x][y] = EMPTY_CELL;
	i = 1;
	do
	{
		gotoxy(x + i, y);
		cout << " ";
		numberBoard[x + i][y] = EMPTY_CELL;

		numberBoard[x + i][y + 1] = EMPTY_CELL;
		numberBoard[x + i][y - 1] = EMPTY_CELL;
		i++;
	} while (numberBoard[x + i][y] != DO_NOT_PLACE && (x + i) != 79);
	if ((x + i) == 79)
	{
		gotoxy(x + i, y);
		cout << " ";
		numberBoard[x + i][y + 1] = EMPTY_CELL;
		numberBoard[x + i][y - 1] = EMPTY_CELL;
	}
	numberBoard[x + i][y] = EMPTY_CELL;
}

//TODO: to see why we arent winning when collecting the right number

void TheMathGame::updateLives(Player &p)
{
	p.setLives(p.getLives() - 1);
	printframe(currentLevel);
}