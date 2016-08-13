#include "stdafx.h"
#include "Highscores.h"

Highscores::Highscores(){}

Highscores::Highscores(string file){
	ifstream in(file);

	string input;
	while(getline(in, input)){
		vector<string> h = Utils::split(input, ',');
		highscores.push_back(Highscore(h[0], stoi(h[1])));
	}

	in.close();
}

vector<Highscore *> Highscores::get(int number){
	vector<Highscore *> h;

	int count = 0;
	for(list<Highscore>::iterator it = highscores.begin(); count < number && it != highscores.end(); it++){
		h.push_back(&(*it));

		count++;
	}

	return h;
}

void Highscores::add(Highscore h){
	for(list<Highscore>::iterator it = highscores.begin(); it != highscores.end(); it++){
		if((*it).won < h.won){
			highscores.insert(it, h);
			return;
		}
	}

	highscores.push_back(h);
}

void Highscores::save(){
	ofstream out(file);

	for(list<Highscore>::iterator it = highscores.begin(); it != highscores.end(); it++){
		out << (*it).bet << "," << (*it).won << endl;
	}

	out.close();
}