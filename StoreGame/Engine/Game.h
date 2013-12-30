// Main state for the game - handles state management and any data that exists between states.
// Author: Matt Critelli

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>
using namespace std;

class State;

class Game {
public:
	void init(State*);
	void update();
	void draw();
	void ChangeState(State*);
	Uint32 TIME_START = 0; // when we started the timer
	Uint32 TIME_CURRENT = 0; // total time
	Uint32 TIME_LAST = 0; // total time at previous frame
	Uint32 TIME_DIFF = 0; // time difference between this frame and last
private:
	State* CURRENT_STATE;
	State* NEXT_STATE;
};

#endif