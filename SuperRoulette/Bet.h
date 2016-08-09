#pragma once;
#include "stdafx.h"
#include <string>

using namespace std;

class Bet{
public:
	int amount;
	int odds;
	string name;

	Bet(int, int, string);
};