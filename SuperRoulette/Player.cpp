#include "stdafx.h"
#include "Player.h"

Player::Player(string name){
	//Set the default values
	highestWin = betCount = wonCount = 0;
	money = 500;

	ifstream in(name + ".player");
	if(in.is_open()){
		in >> money;
		in >> highestWin;
		in >> betCount;
		in >> wonCount;
	}
}

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

void Player::save(string name){
	ofstream out(name + ".player");
	
	out << money << endl;
	out << highestWin << endl;
	out << betCount << endl;
	out << wonCount << endl;

	out.close();
}