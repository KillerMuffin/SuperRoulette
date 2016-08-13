#include "stdafx.h"
#include "Highscores.h"

Highscores::Highscores(){}

Highscores::Highscores(string file){

}

vector<Highscore *> Highscores::get(int number){
	vector<Highscore *> h;

	for(list<Highscore>::iterator it = highscores.begin(), int count = 0; count < number; it++, count++){
		h.push_back(&(*it));
	}

	return h;
}

void Highscores::add(Highscore h){

}