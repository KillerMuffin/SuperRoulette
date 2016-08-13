#pragma once
#include "stdafx.h"
#include "Highscore.h"
#include "Utils.cpp"
#include <list>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Highscores{
public:
	list<Highscore> highscores;
	string file;

	Highscores();
	Highscores(string);

	vector<Highscore *> get(int);
	void add(Highscore);

	void save();
};