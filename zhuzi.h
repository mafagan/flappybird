#pragma once
class zhuzi
{
public:
	zhuzi(int upLength);
	void moveLeft();

	int getUpLength();
	int getPos();
	~zhuzi(void);
private:
	int length;
	int pos;
};

