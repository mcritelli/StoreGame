#include "Game.h"
#include "State.h"

#define DEBUG false

void Game::init(State* initialState)
{
	if (DEBUG) std::cout << "INSIDE GAME INIT\n";
	CURRENT_STATE = initialState;
	NEXT_STATE = 0; // must set this to null!
}

void Game::update()
{
	if (DEBUG) std::cout << "INSIDE GAME UPDATE\n";
	
	// If we don't have a new state to go to, keep updating the current state
	if (NEXT_STATE == 0)
	{
		CURRENT_STATE->update(this);
	}
	else // otherwise, cleanup the old state, then switch to the new one
	{
		CURRENT_STATE->destroy();
		CURRENT_STATE = NEXT_STATE;
		CURRENT_STATE->init();
		NEXT_STATE = 0;
	}
}

void Game::draw()
{
	if (DEBUG) std::cout << "INSIDE GAME DRAW\n";
	CURRENT_STATE->draw(this);
}

void Game::ChangeState(State* newState)
{
	NEXT_STATE = newState;
}