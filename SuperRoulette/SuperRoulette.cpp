// SuperRoulette.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Roulette.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Player p("profile");

	Roulette r = Roulette(p);
	r.play();

	return 0;
}

