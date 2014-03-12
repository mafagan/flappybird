#include "zhuzi.h"


zhuzi::zhuzi(int upLength)
{
	this->length = upLength;
	this->pos = 40;
}

void zhuzi::moveLeft()
{
	this->pos--;
	return;
}

int zhuzi::getUpLength()
{
	return this->length;
}

int zhuzi::getPos()
{
	return this->pos;
}
zhuzi::~zhuzi(void)
{
}