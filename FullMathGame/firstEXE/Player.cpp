#include "Player.h"
//this function prints the symbols of lives that a player left
void Player::printlives(int x, int y)
{
	char heart = 3; //heart ascii number
	gotoxy(x, y);
	for (int i = 0; i < lives; i++)
	{
		cout << heart << " ";
	}
	for (int i = 0; i < 3 - lives; i++)
		cout << "  ";
}
//this function gets a location and erases the cody of the player in said location
void Player::erasePlayer(int x, int y)
{
	gotoxy(x, y);
	cout << " ";
}
//this function gets a location and prints the body of the player in said location
void Player::showPlayer(int x, int y)
{
	gotoxy(x, y);
	setXY(x, y);
	cout << this->body;
}
//this function gets a valid direction of the player and changes the movement of it
void Player::changeDirection(char direction)
{


	if (direction == PLAYER_1_UP || direction == PLAYER_2_UP)
	{
		dirx = STAY;
		diry = MOVE_UP;
	}
	else if (direction == PLAYER_1_DOWN || direction == PLAYER_2_DOWN)
	{
		dirx = STAY;
		diry = MOVE_DOWN;
	}
	else if (direction == PLAYER_1_LEFT || direction == PLAYER_2_LEFT)
	{
		dirx = MOVE_LEFT;
		diry = STAY;
	}
	else
	{
		dirx = MOVE_RIGHT;
		diry = STAY;
	}
}
//this functions makes the movement of the player
void Player::move()
{
	erasePlayer(x, y);
	x += dirx;
	y += diry;

	if (x > X_MAX)
		x = X_MIN;
	else if (x < X_MIN)
		x = X_MAX;

	if (y > Y_MAX)
		y = Y_MIN;
	else if (y < Y_MIN)
		y = Y_MAX;
	if (this->getLives() > 0)
		showPlayer(x, y);
}