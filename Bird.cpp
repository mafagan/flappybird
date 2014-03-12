#include "Bird.h"
#define  LINES	20
#define  COLS	40

Bird::Bird()
{
	height = 11;
	speed = -1;
}

void Bird::upAccept()
{
	this->speed += 5;
	if(this->speed >= 3)
		this->speed = 3;
	return;
}

void Bird::speedChange()
{
	this->speed -= 1;
	if(this->speed < -4)
		this->speed = -4;
	return;
}

bool Bird::heightChange()
{
	this->height -= this->speed;
	if (this->height < 0)
	{
		this->height = 0;
	}
	return this->height >= 0 && this->height < LINES;
}

int Bird::getHeight()
{
	return this->height;
}
Bird::~Bird()
{
}
