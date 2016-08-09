#pragma once
#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>

#include <iostream>
#include <fstream>

#include <sstream>
#include <algorithm>
#include <iterator>
#include <random>

#include "Coord.h"

using namespace std;

class Utils{
public:
	//Seed random
	static void seed_random(){
		srand(time(NULL));
	}
	
	//Random function with min and max
	static int random(int min, int max){
		//Get the random device for a more statistically random number
		random_device rd;
		//Use the mersenne twister algorithm
		mt19937 rng(rd());
		//Uniform int distribition
		uniform_int_distribution<int> uni(min,max);
		//Get a random number
		return uni(rng);
	}

	//Pause output
	static void pau(){
		system("pause");
	}
	
	//Clear console
	static void cls(){
		system("cls");
	}

	//Pause, then clear console
	static void paul(){
		pau();
		cls();
	}

	//Convert string to coordinates
	static Coord strToCoord(string coord){
		Coord c = Coord();

		//Position of number and alphabetic character
		int aPos = 0;
		int nPos = 1;
		//Find which position
		if(coord.at(0) >= 48 && coord.at(0) <= 57){
			aPos = 1;
			nPos = 0;
		}

		//Set coordinates
		c.y = coord.at(nPos)-49;

		if(coord.at(aPos) >= 97){
			c.x = coord.at(aPos) - 97;
		}else{
			c.x = coord.at(aPos) - 65;
		}

		//Return coordinates
		return c;
	}

	//Load and display a menu
	static int menu(string menu){
		cls();

		//Load the menu
		string input;
	
		ifstream file(menu);

		int count = 1;
		while(getline(file, input)){
			cout << "[" << count << "] " << input << endl;
			count++;
		}

		file.close();

		//Get the user input
		int index = 0;
		cin >> index;

		cls();
		return index;
	}

	//Split a string
	static void split(const string &s, char delim, vector<string> &elems) {
		stringstream ss(s);
		string item;
		while (getline(ss, item, delim)) {
			elems.push_back(item);
		}
	}

	static vector<string> split(const string &s, char delim) {
		vector<string> elems;
		split(s, delim, elems);
		return elems;
	}
};
