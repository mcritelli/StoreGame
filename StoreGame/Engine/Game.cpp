#include "Game.h"
#include "State.h"

#define DEBUG false

void Game::init(State* initialState)
{
	if (DEBUG) std::cout << "INSIDE GAME INIT\n";
	CURRENT_STATE = initialState;
	CURRENT_STATE->init();
	NEXT_STATE = 0; // must set this to null!
	FPS = 0;
	LAST_FPS = 0;
	time.START = SDL_GetTicks();
	time.CURRENT_TOTAL = time.START;
	time.LAST_TOTAL = time.CURRENT_TOTAL;
	time.DIFF = time.CURRENT_TOTAL - time.LAST_TOTAL;
	time.dt = 0.0f;
	std::fill_n(tickList, MAX_SAMPLES, 0);
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
		time.LAST_TOTAL = time.CURRENT_TOTAL;
		time.CURRENT_TOTAL = SDL_GetTicks();
		time.DIFF = time.CURRENT_TOTAL - time.LAST_TOTAL;
		time.dt = time.DIFF / 1000.0f;
		//std::cout << "TIME_CURRENT: " << TIME_CURRENT << " | TIME_LAST: " << TIME_LAST << " | TIME_DIFF: " << TIME_DIFF << "\n";
		
		CURRENT_STATE->update(this);

		// Calculate average tick
		
		tickSum -= tickList[tickIndex];
		tickSum += time.DIFF;
		tickList[tickIndex] = time.DIFF;
		if (++tickIndex == MAX_SAMPLES)
			tickIndex = 0;
		
		// Save prev fps first
		LAST_FPS = FPS;
		
		FPS = (int)(tickSum / MAX_SAMPLES);
		if (FPS != 0)
			FPS = 1000 / FPS;
		
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

State* Game::CurrentState() const
{
	return CURRENT_STATE;
}