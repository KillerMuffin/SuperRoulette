#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Bet.h"
#include "Utils.cpp"
#include "Coord.h"
#include "Render.h"
#include "Highscores.h"

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Roulette{
private:
	//Current bet winnings
	int winnings;
	//Money left
	int money;
	//Winning number
	int winNum;

	//Winning bets
	vector<Bet> winBets;

	//Inside board
	Render render;

	//List of red numbers
	vector<int> red;
public:
	Player p;
	Highscores h;

	//Constructors
	Roulette();
	Roulette(Player, Highscores);

	void play();
	void newBet();

	int getBetAmount();

	int numAtCoord(Coord);
	Coord numToCoord(int);
	Coord coordToScreenCoord(Coord);

	bool onRed(int);

	void makeBet();
	void makeInsideBet();
	void makeOutsideBet();

	void mainMenu();
	void printWinnings();
	void printHighscore();
	void printInside();
	void printTitle();

private:
	void construct();
};