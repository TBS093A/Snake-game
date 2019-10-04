//Author: TBS093A

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <vector>

using namespace std;

#define up		87		//W
#define down	83		//S
#define right	68		//D
#define left	65		//A

#define up_1	119		//w
#define down_1	115		//s
#define right_1	100		//d
#define left_1	97		//a

#define random	1

struct historyPoint {
	int xh;
	int yh;
};

vector<historyPoint> snake;

//primary variables

bool gameOver;
int width, height;
int x, y, xF, yF;
int score;

//logic variables

char key;
int value = up;

//game methods

void Setup()
{
	gameOver = false;
	width = 28;
	height = 28;
	x = width / 2;
	y = height / 2;
	xF = (rand() % width - 1) + 1;
	yF = (rand() % height - 1) + 1;
	score = 1;
}
void Draw() 
{
	system("cls");

	for (int i = 0; i < width; i++)
		cout << "#";

	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)										//walls
				cout << "#";
			else if (i == y && j == x && score == 0)							//snake head
				cout << "o";
			else if (i == yF && j == xF)										//fruit
				cout << "+";
			else if (score > 0)													//empty space & snake body
				for (int k = snake.size() - score; k < snake.size(); k++)
				{
					if (i == snake.at(k).yh && j == snake.at(k).xh)
					{
						cout << "o";
						break;
					}
					else if ((i != snake.at(k).yh || j != snake.at(k).xh) && k == snake.size() - 1)		//snake size (on body iteration)
					{
						cout << " ";
					}
				}
			else
				cout << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < width; i++)
		cout << "#";
}
void Logic()
{
	if (value == up || value == up_1)								//head move
		y--;
	else if (value == down || value == down_1)
		y++;
	else if (value == right || value == right_1)
		x++;
	else if (value == left || value == left_1)
		x--;

	historyPoint HP;
	HP.xh = x;
	HP.yh = y;
	snake.push_back(HP);

	if (y == yF && x == xF)											//points of score & upgrade snake
	{
		score++;
		xF = (rand() % width - 1) + 1;
		yF = (rand() % height - 1) + 1;
	}

	if ((y == -1 || y == height) || (x == 0 || x == width-1))		//wall collisions
		gameOver = true;

	for (int k = snake.size() - score; k < snake.size() - 1; k++)	//snake body collision ( size - 1 beacause calculation without snake head)
		if (y == snake.at(k).yh && x == snake.at(k).xh)
			gameOver = true;

}
void Input()
{
	key = _getch();
	if ((key == up && value == down) || (key == up_1 && value == down_1))				//block "reverse" move
		value = down;
	else if ((key == down && value == up) || (key == down_1 && value == up_1))
		value = up;
	else if ((key == right && value == left) || (key == right_1 && value == left_1))
		value = left;
	else if ((key == left && value == right) || (key == left_1 && value == right_1))
		value = right;
	else
		value = key;
}

//General pogram

int main()
{
	Setup();
	while (!gameOver) {
		Draw();
		if (_kbhit()) {
			Input();
		}
		Logic();
		Sleep(50);
	}
	cout << "your score: " << score;
}