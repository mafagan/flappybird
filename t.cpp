#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <vector>
#include <time.h>
#include "zhuzi.h"
#include "Bird.h"
#define  LINES	20
#define  COLS	40
#define  UP		true
#define  DOWN	false
using namespace std;

char map[LINES][COLS];
bool upPush;
void mapInit();
bool moveZhuzi(vector<zhuzi> &t);
int getRand(int limit);
bool birdMove(Bird &bd);
void birdShow(Bird &bd);
DWORD WINAPI getKeyData(LPVOID lpParamter);
int score;
bool replay;
int main()
{
	replay = false;
	while (true)
	{
		score = 0;
		upPush = false;

		vector<zhuzi> obs;
		Bird bd;
		int nChoice = 0;
		upPush = false;
		system("mode con cols=40 lines=22");
		if (!replay)
		{
			
			for (int i = 0; i < 10; i++)
			{
				printf("\n");
			}

			printf("\tPress any key to go");
			int tdata = _getch();
		}
		
		
		HANDLE keyThread = CreateThread(NULL, 0, getKeyData, NULL, 0, NULL);

		/*nChoice = _getch();
		cout<<nChoice<<endl;
		cout<<"haha"<<endl;*/
		int count = 0;
		score = 0;
		while (true)
		{
			count++;
			if(count > 10000)
				count = 0;

			system("cls");

			if (upPush)
			{
				bd.upAccept();
				upPush = false;
			}
			mapInit();


			if ((count & 0x01) == 0)
			{
				if(!birdMove(bd))
					break;
			}
			birdShow(bd);

			if(!moveZhuzi(obs))
				break;

			sprintf_s(map[21], 40, "Score: %d",score);
			for(int j=0;j<LINES + 1;j++)
			{
				for(int k=0;k<COLS;k++)
				{

					printf("%c",map[j][k]);
				}
			}
			printf("Your score is %d", score);
			Sleep(50);

		}
		system("cls");
		for (int i = 0; i < 10; i++)
		{
			printf("\n");
		}

		printf("\tYour score is %d\t\t\t\n", score);
		printf("\treplay in 3 s", score);
		replay = true;
		Sleep(3000);
		//CloseHandle(keyThread);
		/*TerminateThread(keyThread,0);
		int temp = _getch();
		if(temp != '1')
			break;*/
	}
	return 0;
}




void mapInit()
{
	for(int i = 0; i < LINES; ++i)
	{
		for(int j = 0; j < COLS; ++j)
		{
			map[i][j] = ' ';
		}
	}
}

bool moveZhuzi(vector<zhuzi> &t)
{


	if(t.empty())
	{
		//printf("empty now");
		zhuzi temp(getRand(20-5));
		t.push_back(temp);

	}
	//printf("%d\n",t[0].getPos());
	if(t[0].getPos() < -5)
	{
		t.erase(t.begin());
		score++;
	}

	if(t[t.size()-1].getPos() < COLS - 15)
	{
		int dis = getRand(10);
		if(getRand(2) == 0)
		{
			if(t[t.size()-1].getUpLength() < dis)
			{
				zhuzi temp(t[t.size()-1].getUpLength() + dis);
				t.push_back(temp);
			}else
			{
				zhuzi temp(t[t.size()-1].getUpLength() - dis);
				t.push_back(temp);
			}
		}else
		{
			if(t[t.size()-1].getUpLength() + dis > LINES - 5)
			{
				zhuzi temp(t[t.size()-1].getUpLength() - dis);
				t.push_back(temp);
			}else
			{
				zhuzi temp(t[t.size()-1].getUpLength() + dis);
				t.push_back(temp);
			}
		}

	}

	for(int it = 0; it < t.size(); it++)
	{

		for (int i = 0; i < t[it].getUpLength(); ++i)
		{
			for (int j = t[it].getPos(); (j < t[it].getPos() + 5) && j < COLS; j++)
			{
				if(j < 0)
					continue;
				if(map[i][j] == 'X' || map[i][j] == 'O')
					return false;
				map[i][j] = '#';
			}
		}

		for (int i = LINES - 1; i >= t[it].getUpLength() + 5; --i)
		{
			for (int j = t[it].getPos(); (j < t[it].getPos() + 5) && j < COLS; j++)
			{
				if (j < 0)
				{
					continue;
				}

				if(map[i][j] == 'X' || map[i][j] == 'O')
					return false;
				map[i][j] = '#';
			}
		}
		t[it].moveLeft();
		//printf("%d\n",t[0].getPos());
	}
	return true;
}

bool birdMove(Bird &bd)
{
	if(!bd.heightChange())
		return false;

	bd.speedChange();
	return true;
}

int getRand(int limit)
{
	srand(time(0));
	return rand()%limit;
}
void birdShow(Bird &bd)
{
	map[bd.getHeight()][7] = 'X';
	map[bd.getHeight()][8] = 'O';
}

DWORD WINAPI getKeyData(LPVOID lpParamter)
{
	while (true)
	{
		int data = _getch();
		if (data == 224)
		{
			upPush = true;
		}
	}

}