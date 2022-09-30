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
int MaxResult = 0;

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
	MoveBall(2, 2);
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

void InitField()
{
	for (int i = 0; i < width; i++)
		mas[0][i] = '#';
	mas[0][width] = '\0';

	strncpy(mas[1], mas[0], width + 1);
	for (int i = 1; i < width - 1; i++)
		mas[1][i] = ' ';

	for (int i = 2; i < height; i++)
		strncpy(mas[i], mas[1], width + 1);
}

void Show()
{
	for (int i = 0; i < height; i++)
	{
		printf("%s", mas[i]);
		if (i == 4)
			printf("     Counter: %d", Counter);
		if (i == 6)
			printf("     Max Result: %d", MaxResult);
		if (i == 9)
			printf("     Press SPACE to start");
		if (i == 11)
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
		if (mas[ball.iy][ball.ix] == '=') Counter++;

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
		AutoMoveBall;
	}
}

void SetCur(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main()
{
	char press;
	BOOL run = FALSE;
	InitRacket();
	InitBall();

	do
	{
		SetCur(0, 0);

		if (run)
			AutoMoveBall();
		if (ball.iy > height)
		{
			run = FALSE;
			if (Counter > MaxResult) MaxResult = Counter;
			Counter = 0;
		}

		InitField();
		PutRacket();
		PutBall();
		Show();
		

		if (GetKeyState('A') < 0) MoveRacket(--racket.x);
		if (GetKeyState('D') < 0) MoveRacket(++racket.x);
		if (GetKeyState(' ') < 0) run = TRUE;
		if (!run)
			MoveBall(racket.x + racket.w / 2, racket.y - 1);
		Sleep(10);

	} while (GetKeyState(VK_ESCAPE) >= 0);
	return 0;
}