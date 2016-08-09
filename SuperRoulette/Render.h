#pragma once
#include "stdafx.h"
#include "Pixel.h"
#include <vector>
#include <string>
#include "Coord.h"
#include <iostream>
#include <Windows.h>
#include <fstream>

using namespace std;

class Render{
public:
	vector<Pixel> savedState;
	vector<Pixel> screen;
	int width, height;

	const int WHITE = 15;

	Render(int,int);
	Render(string);

	void saveState();
	void loadState();

	Pixel * get(int,int);
	Pixel * get(Coord);
	Pixel * get(int);

	void set(int,int,Pixel);
	void set(Coord,Pixel);
	void set(int,Pixel);

	void render();
private:
	int xyToPos(Coord);
	Coord posToXy(int);

	void color(int c);
};