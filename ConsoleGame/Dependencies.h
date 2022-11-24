#pragma once
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