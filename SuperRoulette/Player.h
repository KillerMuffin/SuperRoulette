#pragma once;
#include "stdafx.h"

using namespace std;

class Player{
public:
	int money;
	int highestWin;
	int betCount;
	int wonCount;

	Player();
	Player(int, int, int, int);
};