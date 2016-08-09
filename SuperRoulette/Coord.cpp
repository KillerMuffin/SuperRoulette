#include "stdafx.h"
#include "Coord.h"

using namespace std;

Coord::Coord(){
	x = y = -1;
}

Coord::Coord(int x, int y){
	this->x = x;
	this->y = y;
}