// Main state for the game - handles state management and any data that exists between states.
// Author: Matt Critelli

#ifndef GAME_H
#define GAME_H

#include <iostream>
using namespace std;

class State;

class Game {
public:
	void init(State*);
	void update();
	void draw();
	void ChangeState(State*);
private:
	State* CURRENT_STATE;
	State* NEXT_STATE;
};

#endif