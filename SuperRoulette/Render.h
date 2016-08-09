#pragma once
#include "stdafx.h"
#include "Pixel.h"
#include <vector>
#include <string>
#include "Coord.h"
#include <iostream>

using namespace std;

class Render{
public:
	vector<char> savedState;
	vector<char> screen;
	int width, height;

	Render(int,int);
	Render(string);

	void saveState();
	void loadState();

	Pixel get(int,int);
	Pixel get(Coord);
	Pixel get(int);

	void set(int,int,Pixel);
	void set(Coord,Pixel);
	void set(int);

	void render(bool);
private:
	int xyToPos(int,int);
	Coord posToXy(int);
};