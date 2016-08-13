// SuperRoulette.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Roulette.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Player p("profile");
	Highscores h("highscores.hs");

	Roulette r = Roulette(p,h);
	r.play();

	return 0;
}

