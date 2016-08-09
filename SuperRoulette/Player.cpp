#include "stdafx.h"
#include "Player.h"

Player::Player(){
	highestWin = betCount = wonCount = 0;
	money = 500;
}

Player::Player(int money, int highestWin, int betCount, int wonCount){
	this->money = money;
	this->highestWin = highestWin;
	this->betCount = betCount;
	this->wonCount = wonCount;
}