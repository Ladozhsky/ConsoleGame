#include "Dependencies.h"
#include "Dependencies.c"

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

		InitField();
		PutRacket();
		PutBall();
		Show();
		ManageRacket();

	} while (GetKeyState(VK_ESCAPE) >= 0);
	
	return 0;
}

