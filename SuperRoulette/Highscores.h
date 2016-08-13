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
	//Linked list of highscores
	list<Highscore> highscores;

	Highscores();
	//Read highscores from file
	Highscores(string);

	//Get top highscores
	vector<Highscore *> get(int);
	//Add a highscore
	void add(Highscore);

	//Save highscores
	void save(string);
};