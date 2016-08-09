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
	static void seed_random(){
		srand(time(NULL));
	}
	
	static int random(int min, int max){
		random_device rd;
		mt19937 rng(rd());
		uniform_int_distribution<int> uni(min,max);
		return uni(rng);
	}

	static void pau(){
		system("pause");
	}
	
	static void cls(){
		system("cls");
	}

	static void paul(){
		pau();
		cls();
	}

	static Coord strToCoord(string coord){
		Coord c = Coord();

		int aPos = 0;
		int nPos = 1;
		if(coord.at(0) >= 48 && coord.at(0) <= 57){
			aPos = 1;
			nPos = 0;
		}

		c.y = coord.at(nPos)-49;

		if(coord.at(aPos) >= 97){
			c.x = coord.at(aPos) - 97;
		}else{
			c.x = coord.at(aPos) - 65;
		}

		return c;
	}

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
