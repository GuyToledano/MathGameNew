#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Equation.h"
#include <iostream>
#include "io_utils.h"
//#include "TheMathGame.h"
using namespace std;

#define PLAYER_1_UP 'w'
#define PLAYER_1_DOWN 'x'
#define PLAYER_1_LEFT 'a'
#define PLAYER_1_RIGHT 'd'
#define PLAYER_2_UP 'i'
#define PLAYER_2_DOWN 'm'
#define PLAYER_2_LEFT 'j'
#define PLAYER_2_RIGHT 'l'

#define X_MAX 79
#define X_MIN 0
#define Y_MAX 23
#define Y_MIN 3
#define MOVE_LEFT -1
#define MOVE_RIGHT 1
#define MOVE_UP -1
#define MOVE_DOWN 1
#define STAY 0

class Player
{
	char body;
	int score;
	Equation* eq;
	int x;
	int y;
	int lives;
	int dirx, diry;
	bool winner;
	int targetNum;

	// TODO: create 'Point' class, and point data member instead of 2 ints
public:
	Player(char body = '*', int x = 0, int y = 0, int dirx = 0, int diry = 0, int score = 0, int lives = 3, bool winner = false, int targetNum = 0)
		: body(body), x(x), y(y), dirx(dirx), diry(diry), score(score), lives(lives), winner(winner), targetNum(targetNum) {}

	void setEquation(Equation *newEq) { eq = newEq; }
	Equation* getEquation() { return eq; }

	void setLives(int newLives = 3) { lives = newLives; }
	int getLives() { return lives; }

	void setXY(int newX, int newY)  { x = newX; y = newY; }
	int getX() { return x; }
	int getY() { return y; }

	void setDirx(int Dirx) { dirx = Dirx; }
	void setDiry(int Diry) { diry = Diry; }
	int getDirx() { return dirx; }
	int getDiry() { return diry; }
	void setWinner(bool winner) { winner = winner; }
	bool getWinner() { return winner; }
	void showPlayer(int x, int y);
	void erasePlayer(int x, int y);
	void changeDirection(char direction);
	void move();

	void printlives(int x, int y);
	int getScore() { return score; }
	void setScore(int score) { score = score; }
	bool isPlayerStationary() { return (dirx == STAY && diry == STAY); }
	int getTargetNum() { return targetNum; }
	void setTargetNum(int targetNum) { targetNum = targetNum; }

};


#endif