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

Tracket racket;

typedef struct {
	float x, y;
	int ix, iy;
	float corner;
	float speed;
} TBall;
TBall ball;

char mas[height][width + 1];


static int Counter = 0;
static int Level = 1;
static BOOL run = FALSE;

//void InitRacket();
//
//void MoveBall(float x, float y);
//
//void InitBall();
//
//void PutRacket();
//
//void PutBall();
//
//void InitField();
//
//void Show();
//
//void MoveRacket(int x);
//
//void AutoMoveBall();
//
//void SetCur(int x, int y);
//
//void ShowLevel();
//
//void ShowEnd();
//
//void setColor(int ForgC);
//
//void ManageRacket();
//
//void Fail();
//
//void Win();
//
//void GameLoop();
