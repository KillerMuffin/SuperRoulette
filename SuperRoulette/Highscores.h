#pragma once
#include "stdafx.h"
#include "Highscore.h"
#include <list>
#include <vector>

using namespace std;

class Highscores{
public:
	list<Highscore> highscores;

	Highscores();
	Highscores(string);

	vector<Highscore *> get(int);
	void add(Highscore);

	void save();
};