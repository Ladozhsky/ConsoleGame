#include "../Header files/Dependencies.h"
#include "Dependencies.c"

int main()
{
	setColor(6);

	InitRacket();

	InitBall();

	ShowLevel();

	GameLoop();
	
	return 0;
}

