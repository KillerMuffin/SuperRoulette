#include "stdafx.h"
#include "Highscore.h"

Highscore::Highscore(){
	bet = "";
	won = 0;
}

Highscore::Highscore(string bet, int won){
	this->bet = bet;
	this->won = won;
}