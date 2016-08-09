#include "stdafx.h"
#include "Roulette.h"

Roulette::Roulette(){
	Utils::seed_random();
}
Roulette::Roulette(Player p){
	Utils::seed_random();
	this->p = p;
}

void Roulette::play(){
	printTitle();
	Utils::paul();

	bool playing = true;

	startLoop:
	while(playing){
		newBet();
		cout << "Win num: " << winNum << endl;
		Utils::pau();
		mainMenu();

		bool betting = true;
		while(betting){
			int selection = Utils::menu("continue_bet.menu");
			switch(selection){
			case 1:
				makeBet();
				break;
			case 2:
				betting = false;
				break;
			case 3:
				goto startLoop;
			}
		}

		printWinnings();

		Utils::paul();
	}

}

void Roulette::newBet(){
	winBets.clear();
	moneyLeft = p.money;
	winNum = Utils::random(1,36);
}

void Roulette::makeBet(){
	int selection = Utils::menu("bet_selection.menu");

	switch(selection){
	case 1:
		makeInsideBet();
		break;
	case 2:
		makeOutsideBet();
		break;
	}
}

void Roulette::makeOutsideBet(){
	int selection = Utils::menu("outside_bet.menu");

	const int twelveOdds = 2;
	//1st 12
	if(selection == 1){
		int betAmount = getBetAmount();

		if(winNum <= 12){
			Bet b = Bet(betAmount, twelveOdds, "1st 12");
			winBets.push_back(b);

			moneyLeft += betAmount*twelveOdds;
		}

		return;
	}

	//2nd 12
	if(selection == 2){
		int betAmount = getBetAmount();

		if(winNum > 12 && winNum <= 24){
			Bet b = Bet(betAmount, twelveOdds, "2nd 12");
			winBets.push_back(b);

			moneyLeft += betAmount*twelveOdds;
		}

		return;
	}

	//3rd 12
	if(selection == 3){
		int betAmount = getBetAmount();

		if(winNum > 24){
			Bet b = Bet(betAmount, twelveOdds, "3rd 12");
			winBets.push_back(b);

			moneyLeft += betAmount*twelveOdds;
		}

		return;
	}

	const int halfOdds = 1;
	//1 to 18
	if(selection == 4){
		int betAmount = getBetAmount();

		if(winNum <= 18){
			Bet b = Bet(betAmount, halfOdds, "1 to 18");
			winBets.push_back(b);

			moneyLeft += betAmount*halfOdds;
		}

		return;
	}

	//19 to 36
	if(selection == 4){
		int betAmount = getBetAmount();

		if(winNum > 18){
			Bet b = Bet(betAmount, halfOdds, "19 to 36");
			winBets.push_back(b);

			moneyLeft += betAmount*halfOdds;
		}

		return;
	}

	const int evenOdds = 1;
	//Even
	if(selection == 5){
		int betAmount = getBetAmount();

		if((winNum % 2) == 0){
			Bet b = Bet(betAmount, halfOdds, "Even");
			winBets.push_back(b);

			moneyLeft += betAmount*halfOdds;
		}

		return;
	}

	//Odd
	if(selection == 6){
		int betAmount = getBetAmount();

		if(((winNum+1) % 2) == 0){
			Bet b = Bet(betAmount, halfOdds, "Odd");
			winBets.push_back(b);

			moneyLeft += betAmount*halfOdds;
		}

		return;
	}

	const int colorOdd = 1;
	//Red
	if(selection == 6){
		int betAmount = getBetAmount();

		if(onRed(winNum)){
			Bet b = Bet(betAmount, halfOdds, "Red");
			winBets.push_back(b);

			moneyLeft += betAmount*halfOdds;
		}

		return;
	}

	//Black
	if(selection == 6){
		int betAmount = getBetAmount();

		if(onRed(winNum)){
			Bet b = Bet(betAmount, halfOdds, "Black");
			winBets.push_back(b);

			moneyLeft += betAmount*halfOdds;
		}

		return;
	}
}

void Roulette::makeInsideBet(){
	Utils::cls();
	printInside();
	
	cout << "Chip position:" << endl;
	string pos;
	cin >> pos;

	Coord c = Utils::strToCoord(pos);
	
	//Check to see if single num
	if(((c.x-1) % 2) == 0 && ((c.y-1) % 2) == 0){
		const int singleOdds = 35;

		int betAmount = getBetAmount();

		if(numAtCoord(c) == winNum){
			Bet b = Bet(betAmount, singleOdds, "Single Bet");
			winBets.push_back(b);

			moneyLeft += betAmount*singleOdds;
		}

		return;
	}
	
	//Check to see if column bet
	if(c.x == 25){
		//If valid position
		if(((c.y+1) % 2) == 0){
			const int columnOdds = 2;

			int betAmount = getBetAmount();

			int offset = ((c.y+1)/2)-1;

			//If number won
			if(((winNum+offset) % 3) == 0){
				Bet b = Bet(betAmount, columnOdds, "Column Bet");
				winBets.push_back(b);

				moneyLeft += betAmount*columnOdds;
			}
		}
		return;
	}

	//Check to see if corner bet
	if((c.x % 2) == 0 && (c.y % 2) == 0){
		const int cornerOdds = 8;

		int betAmount = getBetAmount();

		//If number won
		if(
			numAtCoord(Coord(c.x-1, c.y-1)) == winNum ||
			numAtCoord(Coord(c.x-1, c.y+1)) == winNum ||
			numAtCoord(Coord(c.x+1, c.y-1)) == winNum ||
			numAtCoord(Coord(c.x+1, c.y+1)) == winNum){
			
			Bet b = Bet(betAmount, cornerOdds, "Corner Bet");
			winBets.push_back(b);

			moneyLeft += betAmount*cornerOdds;
		}

		return;
	}

	//Check to see if street bet
	if(((c.x+1) % 2) == 0 && (c.y == 0 || c.y == 6)){
		const int streetOdds = 11;

		int betAmount = getBetAmount();

		//If number won
		int top = numAtCoord(Coord(c.x, 1));
		if(top == winNum || (top - 1) == winNum || (top - 2) == winNum){
			Bet b = Bet(betAmount, streetOdds, "Street Bet");
			winBets.push_back(b);

			moneyLeft += betAmount*streetOdds;
		}

		return;
	}

	//Check to see if line bet
	if((c.x % 2) == 0 && (c.y == 0 || c.y == 6)){
		const int lineOdds = 5;

		int betAmount = getBetAmount();
		//If number won
		int topL = numAtCoord(Coord(c.x-1, 1));
		int topR = numAtCoord(Coord(c.x-1, 1));
		if(
			topL == winNum || (topL - 1) == winNum || (topL - 2) == winNum ||
			topR == winNum || (topR - 1) == winNum || (topR - 2) == winNum
			){
			Bet b = Bet(betAmount, lineOdds, "Line Bet");
			winBets.push_back(b);

			moneyLeft += betAmount*lineOdds;
		}

		return;
	}

	const int splitOdds = 17;
	//Check for horizontal split bet
	if((c.x % 2) == 0 && ((c.y+1) % 2) == 0){
		int betAmount = getBetAmount();

		if(numAtCoord(Coord(c.x-1, c.y)) == winNum || numAtCoord(Coord(c.x+1, c.y))){
			Bet b = Bet(betAmount, splitOdds, "Split Bet");
			winBets.push_back(b);

			moneyLeft += betAmount*splitOdds;
		}

		return;
	}

	//Check for vertical split bet
	if(((c.x+1) % 2) == 0 && (c.y % 2) == 0){
		int betAmount = getBetAmount();

		if(numAtCoord(Coord(c.x, c.y-1)) == winNum || numAtCoord(Coord(c.x, c.y+1))){
			Bet b = Bet(betAmount, splitOdds, "Split Bet");
			winBets.push_back(b);

			moneyLeft += betAmount*splitOdds;
		}

		return;
	}
}

void Roulette::mainMenu(){
	bool running = true;

	while(running){
		int selection = Utils::menu("main_selection.menu");

		switch(selection){
		case 1:
			return;
		case 2:
			printHighscore();
			break;
		case 3:
			exit(0);
		case 4:
			//TODO
			return;
		}
	}
}

void Roulette::printWinnings(){
	if(moneyLeft > p.money){
		cout << "You won $" << (moneyLeft - p.money) << "!" << endl;
	}else{
		cout << "You lost $" << (p.money - moneyLeft) << "!" << endl;
	}

	cout << "Winning Bets: " << endl;
	for(int i = 0; i < winBets.size(); i++){
		Bet b = winBets[i];
		cout << " - " << b.name << " for $" << b.amount << " with " << b.odds << ":1 odds" << endl;
	}

	p.money = moneyLeft;
}

void Roulette::printTitle(){
	string input;
	
	ifstream file("title.txt");

	while(getline(file, input)){
		cout << input << endl;
	}

	file.close();
}

void Roulette::printInside(){
	string input;
	
	ifstream file("inside.txt");

	while(getline(file, input)){
		cout << input << endl;
	}

	file.close();
}

void Roulette::printHighscore(){

}

int Roulette::getBetAmount(){
	cout << "Enter a bet amount: " << endl;
	cout << "$";

	int amount;
	cin >> amount;

	return amount;
}

int Roulette::numAtCoord(Coord c){
	if((c.y % 2) == 0 || (c.x % 2) == 0 || c.x < 0 || c.x > 25 || c.y < 0 || c.y > 7){
		return -1;
	}

	c.x = (c.x+1)/2;
	c.y = (c.y-1)/2;

	return (3 * c.x) - c.y;
}

bool Roulette::onRed(int num){
	return (
		num == 1 ||
		num == 3 ||
		num == 5 ||
		num == 7 ||
		num == 9 ||
		num == 12 ||
		num == 14 ||
		num == 16 ||
		num == 18 ||
		num == 19 ||
		num == 21 ||
		num == 23 ||
		num == 25 ||
		num == 27 ||
		num == 30 ||
		num == 32 ||
		num == 34 ||
		num == 36);
}