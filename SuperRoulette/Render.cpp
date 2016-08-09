#include "stdafx.h"
#include "Render.h"

Render::Render(int width, int height){
	this->width = width;
	this->height = height;

	screen.reserve(width * height);
	savedState.reserve(width * height);
}

Render::Render(string path){
	width = -1;
	height = 0;

	string input;
	
	ifstream file(path);

	while(getline(file, input)){
		//Set the screen width
		if(width == -1){
			width = input.size();
		}else if(input.size() != width){
			return;
		}

		//Add the line to screen
		for(int i = 0; i < input.size(); i++){
			screen.push_back(Pixel(input.at(i), WHITE));
		}

		height++;
	}

	savedState.reserve(width * height);
	file.close();
}

//Save the current screen state
void Render::saveState(){
	savedState = screen;
}
//Load the saved screen state
void Render::loadState(){
	screen = savedState;
}

//Get pixel at x,y
Pixel * Render::get(int x, int y){
	return get(Coord(x,y));
}
Pixel * Render::get(Coord coord){
	return get(xyToPos(coord));
}
Pixel * Render::get(int pos){
	return &(screen[pos]);
}

//Set pixel at x,y
void Render::set(int x, int y, Pixel p){
	set(Coord(x,y), p);
}
void Render::set(Coord coord, Pixel p){
	set(xyToPos(coord), p);
}
void Render::set(int pos, Pixel p){
	screen[pos] = p;
}

//Render the buffer
void Render::render(){
	int currentColor = -1;
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			Pixel * p = get(x,y);

			//Set the pixel color
			if(p->color != currentColor){
				color(p->color);
				currentColor = p->color;
			}

			cout << p->content;
		}
		cout << endl;
	}

	color(WHITE);
}

//Convert between x,y and pos
int Render::xyToPos(Coord c){
	return (c.y * width) + c.x;
}
Coord Render::posToXy(int pos){
	return Coord(pos/width, pos%width);
}

//Set the color of the console
void Render::color(int c){
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, c);
}