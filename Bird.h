#pragma once
class Bird
{
public:
	Bird();
	void upAccept();
	void speedChange();
	bool heightChange();
	int getHeight();
	~Bird();

private:
	int height;
	int speed;
};

