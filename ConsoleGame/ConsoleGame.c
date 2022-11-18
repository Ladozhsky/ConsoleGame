#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#pragma warning(disable : 4996)

#define width 65
#define height 25

typedef struct {
	int x, y;
	int w;
} Tracket;

typedef struct {
	float x, y;
	int ix, iy;
	float corner;
	float speed;
} TBall;

char mas[height][width + 1];
Tracket racket;
TBall ball;
int Counter = 0;
int Level = 1;
BOOL run = FALSE;

void InitRacket() {
	racket.w = 7;
	racket.x = (width - racket.w) / 2;
	racket.y = height - 1;
}

void MoveBall(float x, float y)
{
	ball.x = x;
	ball.y = y;
	ball.ix = (int)round(ball.x);
	ball.iy = (int)round(ball.y);
}

void InitBall() {
	ball.corner = -1;
	ball.speed = 0.5;
}

void PutRacket() {
	for (int i = racket.x; i < racket.x + racket.w; i++)
		mas[racket.y][i] = '=';
}

void PutBall()
{
	mas[ball.iy][ball.ix] = '@';
}

void InitField(int Level)
{
	for (int i = 0; i < width; i++)
		mas[0][i] = '#';
	mas[0][width] = '\0';

	strncpy(mas[1], mas[0], width + 1);
	for (int i = 1; i < width - 1; i++)
		mas[1][i] = ' ';

	for (int i = 2; i < height; i++)
		strncpy(mas[i], mas[1], width + 1);

	if (Level == 2)
	for (int i = 20; i < 50; i++)
		mas[10][i] = '#';

	if (Level == 3) {
		for (int i = 10; i < 30; i++)
			mas[8][i] = '#';
		for (int j = 35; j < 55; j++)
			mas[12][j] = '#';
	}
	
	if (Level == 4) {
		for (int j = 1; j < 10; j++)
			for (int i = 1; i < 65; i += 7)
				mas[j][i] = '#';
	}

	if (Level == 5)
		for (int j = 1; j < 13; j++) {
			for (int i = 1; i < width - 1; i++)
				mas[j][i] = '#';
		}
}

void Show()
{
	for (int i = 0; i < height; i++)
	{
		printf("%s", mas[i]);
		if (i == 5)
			printf("     Level: %d", Level);
		if (i == 7)
			printf("     Counter: %d", Counter);
		if (i == 12)
			printf("     Press SPACE to start");
		if (i == 14)
			printf("     Use A and D to move the racket");
		if (i < height - 1)
			printf("\n");
	}
}

void MoveRacket(int x)
{
	racket.x = x;
	if (racket.x < 1)
		racket.x = 1;
	if (racket.x + racket.w >= width)
		racket.x = width - 1 - racket.w;
}


void AutoMoveBall()
{
	if (ball.corner < 0) ball.corner += M_PI * 2;
	if (ball.corner > M_PI * 2) ball.corner -= M_PI * 2;

	TBall b1 = ball;
	MoveBall(ball.x + cos(ball.corner) * ball.speed,
		ball.y + sin(ball.corner) * ball.speed);

	if ((mas[ball.iy][ball.ix] == '#') || (mas[ball.iy][ball.ix] == '='))
	{
		if (mas[ball.iy][ball.ix] == '=')
		{
			Counter++;
			Beep(1000, 1000 / 8);
		}

		if ((ball.ix != b1.ix) && (ball.iy != b1.iy))
		{
			if (mas[b1.iy][ball.ix] == mas[ball.iy][b1.ix])
				b1.corner = b1.corner + M_PI;
			else
			{
				if (mas[b1.iy][ball.ix] == '#')
					b1.corner = (2 * M_PI - b1.corner) + M_PI;
				else
					b1.corner = (2 * M_PI - b1.corner);
			}
		}
		else if (ball.iy == b1.iy)
			b1.corner = (2 * M_PI - b1.corner) + M_PI;
		else
			b1.corner = (2 * M_PI - b1.corner);

		ball = b1;
	}
}

void SetCur(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ShowLevel()
{
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n \t\t\t\t\t\t       Level %d", Level);
	Sleep(1500);
	system("cls");
}

void ShowEnd()
{
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n \t\t\t\t\t\t       You Win!");
	Sleep(100000);
	system("cls");
}

void setColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;


	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
}

void ManageRacket()
{
	if (GetKeyState('A') < 0) MoveRacket(--racket.x);
	if (GetKeyState('D') < 0) MoveRacket(++racket.x);
	if (GetKeyState(' ') < 0) run = TRUE;

	if (!run)
		MoveBall(racket.x + racket.w / 2, racket.y - 1);
	Sleep(10);
}

void Fail()
{
	if (ball.iy >= height - 1)
	{
		run = FALSE;
		Counter = 0;
	}
}

Win()
{
	if (Counter > 4)
	{
		if (Level < 5) {
			Level++;
			ball.speed += 0.05;
			run = FALSE;
			Counter = 0;
			ShowLevel();
		}
		else {
			ShowEnd();
		}
	}
}

int main()
{
	setColor(6);
	InitRacket();
	InitBall();

	ShowLevel();

	do
	{
		SetCur(0, 0);

		if (run)
			AutoMoveBall();
		Fail();
		Win();

		InitField(Level);
		PutRacket();
		PutBall();
		Show();
		ManageRacket();

	} while (GetKeyState(VK_ESCAPE) >= 0);
	
	return 0;
}

