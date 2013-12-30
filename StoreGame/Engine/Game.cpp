#include "Game.h"
#include "State.h"

#define DEBUG false

void Game::init(State* initialState)
{
	if (DEBUG) std::cout << "INSIDE GAME INIT\n";
	CURRENT_STATE = initialState;
	CURRENT_STATE->init();
	NEXT_STATE = 0; // must set this to null!
	TIME_START = SDL_GetTicks();
	TIME_CURRENT = TIME_START;
	TIME_LAST = TIME_CURRENT;
	TIME_DIFF = TIME_CURRENT - TIME_LAST;
}

void Game::handleEvents(SDL_Event event)
{
	CURRENT_STATE->handleEvents(this, event);
}

void Game::update()
{
	if (DEBUG) std::cout << "INSIDE GAME UPDATE\n";
	
	// If we don't have a new state to go to, keep updating the current state
	if (NEXT_STATE == 0)
	{
		// Update the timer before we call State.update
		TIME_LAST = TIME_CURRENT;
		TIME_CURRENT = SDL_GetTicks();
		TIME_DIFF = TIME_CURRENT - TIME_LAST;

		//std::cout << "TIME_CURRENT: " << TIME_CURRENT << " | TIME_LAST: " << TIME_LAST << " | TIME_DIFF: " << TIME_DIFF << "\n";
		
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