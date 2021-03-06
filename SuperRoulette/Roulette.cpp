#include "stdafx.h"
#include "Roulette.h"

//New roulette game
Roulette::Roulette(){
	construct();
}
//New roulette game with loaded player and highscores
Roulette::Roulette(Player p, Highscores h){
	construct();
	this->p = p;
	this->h = h;
}

//Constructor
void Roulette::construct(){
	//Seed random
	Utils::seed_random();
	//Load the inside board into the render
	render = Render("inside.txt");

	//List of all red chips
	red.push_back(1);
	red.push_back(3);
	red.push_back(7);
	red.push_back(9);
	red.push_back(12);
	red.push_back(14);
	red.push_back(16);
	red.push_back(18);
	red.push_back(19);
	red.push_back(21);
	red.push_back(23);
	red.push_back(25);
	red.push_back(27);
	red.push_back(30);
	red.push_back(32);
	red.push_back(34);
	red.push_back(36);

	for(int i = 0; i < red.size(); i++){
		//Calculate the y position within the board
		Coord c = numToCoord(red[i]);

		//Calculate the pixel position
		c.y = (c.y*2)+2;
		c.x = (c.x*6)+5;

		//Set those pixel to be red
		for(int j = c.x-2; j < c.x+2; j++){
			Pixel * p = render.get(j,c.y);
			p->color = 12;
		}
	}

	//Save the current state
	render.saveState();
	Utils::cls();
}

void Roulette::play(){
	//Print the intro screen
	printTitle();
	Utils::paul();

	bool playing = true;

startLoop:
	//Main game loop
	while(playing){
		//Create a new bet
		newBet();
		//Show main menu
		mainMenu();

		bool betting = true;
		//While betting
		while(betting){
			//Bet menu
			Utils::cls();
			cout << "Current balance: $" << money << endl << endl;
			int selection = Utils::menu("continue_bet.menu", false);
			Utils::cls();
			

			//Process selection
			switch(selection){
			case 1:
				//Place bet
				makeBet();
				break;
			case 2:
				//View board
				Utils::cls();
				printInside();
				Utils::paul();
				break;
			case 3:
				//Finish bet
				betting = false;
				break;
			case 4:
				//Cancel bet
				goto startLoop;
			}
		}

		//Show bet results
		printWinnings();

		//Reset screen
		Utils::paul();
	}

}

//Make new bet
void Roulette::newBet(){
	//Clear the bets
	winBets.clear();
	//Reset winnings
	winnings = 0;
	//Set the money to the players money
	money = p.money;
	//Reset the board frame
	render.loadState(0);
	//Set the winning number
	winNum = Utils::random(1,36);
}

//Make a new bet
void Roulette::makeBet(){
	int selection = Utils::menu("bet_selection.menu");
	p.betCount++;

	switch(selection){
	case 1:
		makeInsideBet();
		break;
	case 2:
		makeOutsideBet();
		break;
	}
}

//Process outside bet
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

//Process inside bet
void Roulette::makeInsideBet(){
	Utils::cls();
	//Print the board
	printInside();
	
	//Get the position entered
	cout << "Chip position:" << endl;
	string pos;
	cin >> pos;

	//Convert to a coordinate
	Coord c = Utils::strToCoord(pos);

	//Place a chip in the frame at the coordinates
	Pixel * p = render.get(coordToScreenCoord(c));
	p->content = 'o';
	p->color = 10;
	
	//Handle bet
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

		if(numAtCoord(Coord(c.x-1, c.y)) == winNum || numAtCoord(Coord(c.x+1, c.y)) == winNum){
			Bet b = Bet(betAmount, splitOdds, "Split Bet");
			winBets.push_back(b);

			winnings += betAmount*splitOdds;
		}

		return;
	}

	//Check for vertical split bet
	if(((c.x+1) % 2) == 0 && (c.y % 2) == 0){
		int betAmount = getBetAmount();

		if(numAtCoord(Coord(c.x, c.y-1)) == winNum || numAtCoord(Coord(c.x, c.y+1)) == winNum){
			Bet b = Bet(betAmount, splitOdds, "Split Bet");
			winBets.push_back(b);

			winnings += betAmount*splitOdds;
		}

		return;
	}
}

//Do the main menu
void Roulette::mainMenu(){
	bool running = true;

	while(running){
		Utils::cls();
		cout << "Current balance: $" << p.money << endl << endl;
		int selection = Utils::menu("main_selection.menu", false);
		Utils::cls();

		switch(selection){
		case 1:
			//Make a bet
			return;
		case 2:
			//Print the highscore
			printHighscore();
			break;
		case 3:
			//Exit
			exit(0);
		case 4:
			//Restart
			p = Player();
			h = Highscores();
			break;
		case 5:
			//Save
			p.save("profile");
			h.save("highscores.hs");
			break;
		}

	}
}

//Print the results of the bets
void Roulette::printWinnings(){
	//Show winning pos
	//Calculate the y position within the board
	Coord c = numToCoord(winNum);

	//Calculate the pixel position
	c.y = (c.y*2)+2;
	c.x = (c.x*6)+5;

	//Set pixel and render
	render.set(c,Pixel('x',11));
	render.render();

	cout << endl << "Winning number: " << winNum << endl;

	//Print wins/losses
	if((money + winnings) > p.money){
		cout << "You won $" << (winnings) << "!" << endl;
	}else{
		cout << "You lost $" << (p.money - (money + winnings)) << "!" << endl;
	}

	//If player won something
	if(winBets.size() > 0){
		p.wonCount+=winBets.size();

		//Print the winning bets
		cout << "Winning Bets: " << endl;
		for(int i = 0; i < winBets.size(); i++){
			Bet b = winBets[i];
			cout << " - " << b.name << " for $" << b.amount << " with " << b.odds << ":1 odds" << endl;

			//Add to highscore
			h.add(Highscore(b.name, b.amount * b.odds));

			//Set highest win, etc
			if(b.amount > p.highestWin){
				p.highestWin = b.amount * b.odds;
			}
		}
	}

	//Set player money
	p.money = money + winnings;
}

//Print the title
void Roulette::printTitle(){
	string input;
	
	ifstream file("title.txt");

	while(getline(file, input)){
		cout << input << endl;
	}

	file.close();
}

//Render the board
void Roulette::printInside(){
	render.render();
}

//Print the highscores
void Roulette::printHighscore(){
	Utils::cls();

	cout << "Total Bets: " << p.betCount << endl;
	cout << "Total Won: " << p.wonCount << endl;
	cout << "Highest Win: $" << p.highestWin << endl << endl;

	cout << "Top 5 bets: " << endl;
	
	vector<Highscore *> top = h.get(5);
	for(int i = 0; i < top.size(); i++){
		cout << " - " << top[i]->bet << ": $" << top[i]->won << endl;
	}

	Utils::paul();
}

//Get the bet amount
int Roulette::getBetAmount(){
	cout << "Enter a bet amount ($" << money << " left): " << endl;
	cout << "$";

	int amount;
	cin >> amount;

	//If amount is more than the players balance, use rest of players balance
	if(amount > money){
		amount = money;
	}
	money-=amount;

	return amount;
}

//Coord to num
int Roulette::numAtCoord(Coord c){
	if((c.y % 2) == 0 || (c.x % 2) == 0 || c.x < 0 || c.x > 25 || c.y < 0 || c.y > 7){
		return -1;
	}

	c.x = (c.x+1)/2;
	c.y = (c.y-1)/2;

	return (3 * c.x) - c.y;
}
//Num to coord
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
//Inside coord to screen coord
Coord Roulette::coordToScreenCoord(Coord c){
	return Coord((c.x * 3) + 2, c.y+1);
}

//Check if number is red
bool Roulette::onRed(int num){
	return (find(red.begin(), red.end(), num) != red.end());
}