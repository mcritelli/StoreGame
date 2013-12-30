// Base State class
// Defines functions that all States must have
// Author: Matt Critelli

#ifndef STATE_H
#define STATE_H

#include <SDL.h>

class Game; // forward declaration

class State {
public:
	virtual void init() = 0;
	virtual void destroy() = 0;
	virtual void draw(Game* game) = 0;
	virtual void update(Game* game) = 0;
	virtual void handleEvents(Game* game, SDL_Event) = 0;
protected:
	State(){}
};

#endif