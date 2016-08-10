#pragma once;
#include "stdafx.h"
#include <string>
#include <fstream>

using namespace std;

class Player{
public:
	int money;
	int highestWin;
	int betCount;
	int wonCount;

	Player();
	Player(string);
	Player(int, int, int, int);

	void save(string);
};