#include "stdafx.h"
#include "Roulette.h"

Roulette::Roulette(){
	construct();
}
Roulette::Roulette(Player p){
	construct();
	this->p = p;
}

void Roulette::construct(){
	Utils::seed_random();
	render = Render("inside.txt");

	int redPos [] = {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};

	for(int i = 0; i < 18; i++){
		//Calculate the y position within the board
		int rawY = 2;
		if((redPos[i] % 3) == 0){
			rawY = 0;
		}else if(((redPos[i] + 1) % 3) == 0){
			rawY = 1;
		}
		int rawX = ((redPos[i] + rawY) / 3)-1;

		//Calculate the pixel position
		int y = (rawY*2)+2;
		int x = (rawX*6)+5;

		//Set those pixel to be red
		for(int j = x-2; j < x+2; j++){
			Pixel * p = render.get(j,y);
			p->color = 12;
		}
	}

	render.saveState();
	Utils::cls();
}

void Roulette::play(){
	printTitle();
	Utils::paul();

	bool playing = true;

	startLoop:
	while(playing){
		newBet();
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
	winnings = 0;
	money = p.money;
	render.loadState(0);
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

			winnings += betAmount*twelveOdds;
		}

		return;
	}

	//2nd 12
	if(selection == 2){
		int betAmount = getBetAmount();

		if(winNum > 12 && winNum <= 24){
			Bet b = Bet(betAmount, twelveOdds, "2nd 12");
			winBets.push_back(b);

			winnings += betAmount*twelveOdds;
		}

		return;
	}

	//3rd 12
	if(selection == 3){
		int betAmount = getBetAmount();

		if(winNum > 24){
			Bet b = Bet(betAmount, twelveOdds, "3rd 12");
			winBets.push_back(b);

			winnings += betAmount*twelveOdds;
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

			winnings += betAmount*halfOdds;
		}

		return;
	}

	//19 to 36
	if(selection == 4){
		int betAmount = getBetAmount();

		if(winNum > 18){
			Bet b = Bet(betAmount, halfOdds, "19 to 36");
			winBets.push_back(b);

			winnings += betAmount*halfOdds;
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

			winnings += betAmount*halfOdds;
		}

		return;
	}

	//Odd
	if(selection == 6){
		int betAmount = getBetAmount();

		if(((winNum+1) % 2) == 0){
			Bet b = Bet(betAmount, halfOdds, "Odd");
			winBets.push_back(b);

			winnings += betAmount*halfOdds;
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

			winnings += betAmount*halfOdds;
		}

		return;
	}

	//Black
	if(selection == 6){
		int betAmount = getBetAmount();

		if(onRed(winNum)){
			Bet b = Bet(betAmount, halfOdds, "Black");
			winBets.push_back(b);

			winnings += betAmount*halfOdds;
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

	Pixel * p = render.get(coordToScreenCoord(c));
	p->content = 'o';
	p->color = 10;
	
	//Check to see if single num
	if(((c.x-1) % 2) == 0 && ((c.y-1) % 2) == 0){
		const int singleOdds = 35;

		int betAmount = getBetAmount();

		if(numAtCoord(c) == winNum){
			Bet b = Bet(betAmount, singleOdds, "Single Bet");
			winBets.push_back(b);

			winnings += betAmount*singleOdds;
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

				winnings += betAmount*columnOdds;
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

			winnings += betAmount*cornerOdds;
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

			winnings += betAmount*streetOdds;
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

			winnings += betAmount*lineOdds;
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

			winnings += betAmount*splitOdds;
		}

		return;
	}

	//Check for vertical split bet
	if(((c.x+1) % 2) == 0 && (c.y % 2) == 0){
		int betAmount = getBetAmount();

		if(numAtCoord(Coord(c.x, c.y-1)) == winNum || numAtCoord(Coord(c.x, c.y+1))){
			Bet b = Bet(betAmount, splitOdds, "Split Bet");
			winBets.push_back(b);

			winnings += betAmount*splitOdds;
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
	cout << "Winning number: " << winNum << endl;

	if(money > p.money){
		cout << "You won $" << (winnings) << "!" << endl;
	}else{
		cout << "You lost $" << (p.money - (money + winnings)) << "!" << endl;
	}
	cout << "Winning Bets: " << endl;
	for(int i = 0; i < winBets.size(); i++){
		Bet b = winBets[i];
		cout << " - " << b.name << " for $" << b.amount << " with " << b.odds << ":1 odds" << endl;
	}

	p.money = money + winnings;
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
	render.render();
}

void Roulette::printHighscore(){

}

int Roulette::getBetAmount(){
	cout << "Enter a bet amount ($" << money << " left): " << endl;
	cout << "$";

	int amount;
	cin >> amount;

	if(amount > money){
		amount = money;
	}
	money-=amount;

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
Coord Roulette::numToCoord(int num){
	//Calculate the y position within the board
	int rawY = 2;
	if((num % 3) == 0){
		rawY = 0;
	}else if(((num + 1) % 3) == 0){
		rawY = 1;
	}
	int rawX = ((num + rawY) / 3)-1;

	return Coord(rawX, rawY);
}
Coord Roulette::coordToScreenCoord(Coord c){
	return Coord((c.x * 3) + 2, c.y+1);
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