#include <iostream>
#include <conio.h>
#include <Windows.h>

bool GameOver;
const int height = 20;
const int width = 20;
int x, y, fruitX, fruitY,score;
int tailX[100], tailY[100];
int Ntail;
enum directional {STOP=0,LEFT,RIGHT,UP,DOWN};
directional dir;

void setup()
{
	GameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void draw()
{
	system("CLS");
	for (int i = 0;i < height;++i)
	{
		for (int j = 0;j < width;++j)
		{
			if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
			{
				std::cout << "#";
			}
			else {
				std::cout << " ";
			}
			if (i == y && j == x)
				std::cout << "0";
			else if (i == fruitY && j == fruitX)
				std::cout << "$";
			else
			{
				bool print=false;
				for (int k = 0;k < Ntail;++k)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						std::cout << "o";
					}
				}
				if (!print)
				{
					std::cout << " ";
				}
				else
					std::cout << "";
			}	
		}
		std::cout << std::endl;
	}
	std::cout<<"score: "<< score<<std::endl;
}

void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case'a':
			dir = LEFT;
			break;
		case'd':
			dir = RIGHT;
			break;
		case'w':
			dir = UP;
			break;
		case's':
			dir = DOWN;
			break;
		case'x':
			GameOver = true;
			break;
		}
	}
}


void logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	int prev2X, prev2Y;
	for (int k = 1;k < Ntail;++k)
	{
		prev2X = tailX[k];
		prev2Y = tailY[k];
		tailX[k] = prevX;
		tailY[k] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	Sleep(100);
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	/*if (x<0 || x>width || y<0 || y>height)
		GameOver = true;*/

	if (x <= 0)
		x = width - 2;
	if (x >= width)
		x = 0;
	if (y <= 0)
		y = height - 2;
	if (y >= height)
		y = 0;

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		fruitX += fruitX ? 0 : 1;
		fruitY += fruitY ? 0 : 1;
		Ntail++;
	}
	for (int i = 0;i < Ntail;++i)
	{
			if (x == prevX && y== prevY)
				GameOver = true;
	}
}


int main()
{
	setup();
	while (!GameOver)
	{
		draw();
		input();
		logic();
	}
}

