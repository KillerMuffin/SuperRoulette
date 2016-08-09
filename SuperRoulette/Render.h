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
	//Saved states
	vector<vector<Pixel>> savedStates;
	//Screen
	vector<Pixel> screen;
	//Screen width and height
	int width, height;

	//Default color
	const static int WHITE = 7;

	//Constructors
	Render();
	Render(int,int);
	Render(string);

	//State loaders
	int saveState();
	void loadState(int);

	//Getters and Setters
	Pixel * get(int,int);
	Pixel * get(Coord);
	Pixel * get(int);

	void set(int,int,Pixel);
	void set(Coord,Pixel);
	void set(int,Pixel);

	//Render the frame
	void render();
private:
	//Convert coords
	int xyToPos(Coord);
	Coord posToXy(int);

	//Int to console color
	void color(int c);
};