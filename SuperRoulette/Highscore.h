#pragma once
#include "stdafx.h"
#include <string>

using namespace std;

class Highscore{
public:
	string bet;
	int won;

	Highscore();
	Highscore(string, int);
};