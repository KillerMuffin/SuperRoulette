#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Bet.h"
#include "Utils.cpp"
#include "Coord.h"

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Roulette{
private:
	int moneyLeft;
	int winNum;

	vector<Bet> winBets;
public:
	Player p;

	Roulette();
	Roulette(Player);

	void play();
	void newBet();

	int getBetAmount();

	int numAtCoord(Coord);
	bool onRed(int);

	void makeBet();
	void makeInsideBet();
	void makeOutsideBet();

	void mainMenu();
	void printWinnings();
	void printHighscore();
	void printInside();
	void printTitle();
};