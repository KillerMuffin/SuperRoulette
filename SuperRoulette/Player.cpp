#include "stdafx.h"
#include "Player.h"

Player::Player(){
	//Set the default values
	highestWin = betCount = wonCount = 0;
	money = 500;
}

//Load values
Player::Player(int money, int highestWin, int betCount, int wonCount){
	this->money = money;
	this->highestWin = highestWin;
	this->betCount = betCount;
	this->wonCount = wonCount;
}