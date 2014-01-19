/**********************************************************************************************//**
 * @file	Engine\Game.h
 *
 * @brief	Main state for the game - handles state management and any data that exists between states.
 * 			
 * @author	Mcritelli
 **************************************************************************************************/

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>
using namespace std;

class State;

/**********************************************************************************************//**
 * @struct	Time
 *
 * @brief	Describes the game's time attributes in milliseconds.
 *
 * @author	Mcritelli
 * @date	1/14/2014
 * 			
 * @member START - When the timer started
 * 		   CURRENT_TOTAL - Total time from start
 * 		   LAST_TOTAL - Total time at previous frame
 * 		   DIFF - Difference between this frame's time and last frame's time.
 **************************************************************************************************/
struct Time {
	Uint32 START = 0, CURRENT_TOTAL = 0, LAST_TOTAL = 0, DIFF = 0;
	float dt;
};

class Game {
public:
	void init(State*);

	void handleEvents(SDL_Event);
	void update();
	void draw();
	void ChangeState(State*);
	State* CurrentState() const;
	Time time;
	int FPS, LAST_FPS;
private:
	State* CURRENT_STATE;
	State* NEXT_STATE;
	int tickIndex = 0, tickSum = 0;
#define MAX_SAMPLES 100
	int tickList[MAX_SAMPLES];
};

#endif